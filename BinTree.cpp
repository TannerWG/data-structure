#include "BinTree.h"

//二叉树节点的高度更新 
template <typename T> int BinTree<T>::updateHeight(BinNodePosi(T) x)//更新节点x高度
{return x->height = 1 + max(stature(x->lc), stature(x->rc));} //具体规则，因树而异 

template <typename T> void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) //更新高度
{while(x){updateHeight(x); x = x->parent;}} //从x出发，覆盖历代祖先。可优化

//节点插入
template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e)
{_size = 1; return _root = new BinNode<T>(e);} //将e当作根节点插入空的二叉树

template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e)
{_size++; x->insertAsLC(e); updateHeightAbove(x); return x->lc;} //e插入为x的左孩子

template<typename T> BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)
{_size++; x->insertAsRC(e); updateHeightAbove(x); return x->rc;} //e插入为x的y右孩子

//子树接入
template <typename T> //二叉树子树接入算法：将S当作节点x的左子树接入，S本身置空
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &S){
	if(x->lc = S->_root) x->lc->parent = x; //接入 
	_size += S->_size; updateHeightAbove(x); //更新全树规模与x所有祖先的高度
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x; //释放原树，返回接入位置 
} 

//子树接入
template <typename T> //二叉树子树接入算法：将S当作节点x的右子树接入，S本身置空
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &S){
	if(x->rc = S->_root) x->rc->parent = x; //接入 
	_size += S->_size; updateHeightAbove(x); //更新全树规模与x所有祖先的高度
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x; //释放原树，返回接入位置 
} 

//二叉树子树删除
template <typename T> //删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
int BinTree<T>::remove(BinNodePosi(T) x){ //assert:x为二叉树中的合法位置 
	FromParentTo(*x) = NULL; //切断来自父节点的指针
	updateHeightAbove(x->parent); //更新祖先高度
	int n = removeAt(x); _size -= n; return n; //删除子树x，更新规模，返回删除节点总数 
} 
template <typename T> //删除二叉树中位置x处的节点及其后代，返回被删除节点总数
static int removeAt(BinNodePosi(T) x){ //assert: x为二叉树中的合法位置 
	if(!x) return 0; //递归基：空树 
	int n = 1 + removeAt(x->lc) + removeAt(x->rc); //递归释放左右子树
	release(x->data); release(x); return n; //释放被摘除节点，并返回删除节点总数 
} 

//子树分离
template <typename T> //二叉树子树分离算法：将子树x从当前树中摘除，将其封装为一棵独立子树返回
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x){ //assert: x为二叉树中的合法位置 
	FromParentTo(*x) = NULL; //切断来自父节点的指针
	updateHeightAbove(x->parent); //更新原树中所有祖先的高度
	BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = NULL; //树根以x为根
	S->_size = x->size(); _size -= S->_size; return S; //更新规模，返回分离出来的子树 
} 

//先序遍历（递归版） 
template <typename T, typename VST> //元素类型，操作器
void travPre_R(BinNodePosi(T) x, VST& visit){ //二叉树先序遍历算法（递归版） 
	if(!x) return;
	visit(x->data);
	travPre_R(x->lc);
	travPre_R(x->rc);
} 

//后序遍历（递归版） 
template <typename T, typename VST> //元素类型，操作器
void travPost_R(BinNodePosi(T) x, VST& visit){ //二叉树后序遍历算法（递归版） 
	if(!x) return;
	travPost_R(x->lc, visit);
	travPost_R(x->rc, visit);
	visit(x->data);
} 

//中序遍历（递归版）
template <typename T, typename VST> //元素类型、操作器
void travIn_P(BinNodePosi(T) x, VST& visit){ //二叉树中序遍历算法（递归版） 
	if(!x) return;
	travIn_R(x->lc, visit);
	visit(x->data);
	travIn_R(x->rc, visit);
} 

//从当前节点出发，沿左右分支不断深入，直至没有左右分支的节点；沿途节点遇到后立即访问 
template <typename T, typename VST> //元素类型，操作器
static void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& S){
	while(x){
		visit(x->data); //访问当前孩子节点
		S.push(x->rc); //右孩子入栈暂存（可优化：通过判断，避免空的右孩子入栈）
		x = x->rc; //沿左分支深入一层 
	}
} 

template<typename T, typename VST> //元素类型、操作器
void travPre_I2(BinNodePosi(T) x, VST& visit){ //二叉树先序遍历算法（迭代版#2） 
	Stack<BinNodePosi(T)> S; //辅助栈 
	while(true){
		visitAlongLeftBranch(x, visit, S); //从当前节点出发，逐批访问
		if(S.empty()) break; //直到栈空
		x = S.pop(); //弹出下一批的起点 
	}
} 

template <typename T> //从当前节点出发，眼左分支不断深入，直至没有左分支的节点
static void goAlongLeftBranch(BinNodePosi(T) x, Stack<BinNodePosi(T)>& S){
	while(x){S.push(x); x=x->lc;} //当前节点入栈后随机向左侧分支深入，迭代直到无左孩子 
} 

template <typename T, typename VST> //元素类型，操作器
void travIn_I1(BinNodePosi(T) x, VST& visit){ //二叉树中序遍历算法（迭代版#1) 
	Stack<BinNodePosi(T)> S; //赋值栈  
	while(true){
		goAlongLeftBranch(x, S); //从当前节点出发，逐批入栈
		if(S.empty()) break; //直到所有节点处理完毕
		x = S.pop(); visit(x->data); //弹出栈顶节点并访问之
		x = x->rc; //转向右子树 
	}
} 

//二叉树节点直接后继定位
template <typename T> BinNodePosi(T) BinNode<T>::succ(){ //定位节点v的直接后继 
	BinNodePosi(T) s = this; //记录后继的临时变量
	if(rc){ //若有右孩子，则直接后继必在右子树中，具体地就是 
		s = rc; //右子树中 
		while(HasLChild(*s)) s = s->lc; //最靠左（最小）地节点 
	} else{ //否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”，具体地就是 
		while(IsRChild(*s)) s = s->parent; //逆向地沿右向分支，不断朝左上方移动
		s = s->parent; //最后再朝右上方移动一步，即抵达直接后继（如果存在） 
	}
	return s; 
} 

//二叉树中序遍历算法（迭代版#2) 
template<typename T, typename VST> //元素类型，操纵器
void travIn_I2(BinNodePosi(T), VST& visit){ //二叉树中序遍历算法（迭代版#2) 
	Stack<BinNodePosi(T)> S; //赋值栈 
	while(true){
		if(x){
			S.push(x); //根节点进栈
			x = x->lc; //深入遍历左子树 
		}else if{
			x = S.pop(); //尚未访问的最低祖先节点退栈
			visit(x->data); //访问祖先节点
			x = x->rc; //遍历祖先的右子树 
		}else break; //遍历完毕 
	}
}  

//二叉树中序遍历法（迭代版本#3，无需辅助栈） 
template<typename T, typename VST> //元素类型，操作器
void travIn_I3(BinNodePosi(T) x, VST& visit){ //二叉树中序遍历法（迭代版本#3，无需辅助栈） 
	bool backtrack = false; //前一步是否刚从右子树回溯——省去栈，仅o(1)辅助空间
	while(true){
		if(!backtrack && HasLChild(*x)) //若有左子树且不是刚刚回溯，则
			x = x->lc; //深入遍历左子树
		else{ //否则——无左子树或刚刚回溯（相当于无左子树） 
			visit(x->data); //访问该节点
			if(HasRChild(*x)){ //若右子树为非空，则 
				x = x->rc; //深入右子树继续遍历 
				backtrack = false; //并关闭回溯标志 
			}else{ //若右子树空，则 
				if(!(x = x->succ())) break; //回溯（含抵达末节点时的退出返回）
				backtrack = true; //并设置回溯标志 
			}
		} 
	} 
} 

template<typename T> //在以S栈顶节点为根的子树中，找到最高左侧可见叶节点
static void gotoHLVFL(Stack<BinNodePosi(T)>& S){ //沿途所遇节点依次入栈 
	while(BinNodePosi(T) x = S.top()) //自顶而下，反复检查当前节点（即栈顶）
		if(HasLChild(*x)){ //尽可能地向左 
			if(HasRChild(*x)) S.push(x->rc); //若有右孩子，优先入栈
			S.push(x->lc); //然后转至左孩子 
		}else //实不得已 
			S.push(x->rc); //才向右 
	S.pop(); //返回之前，弹出栈顶地空节点 
} 

//叉树的后续遍历（迭代版）
template<typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST& visit){ //二叉树的后续遍历（迭代版） 
	Stack<BinNodePosi(T)> S; //辅助栈
	if(x) S.push(x); //根节点入栈 
	while(!S.empty()){
		if(S.top() != x->parent) //若栈顶非当前节点之父（则必为其右兄弟），此时需
			gotoHLVFL(S); //在以其右兄为根之子树中，找到HLVFL（相当于递归深入其中） 
		x = S.top(); visit(x->data); //弹出栈顶（即前一节点之后继），并访问之 
	}
} 

//二叉树层次遍历算法
template <typename T> template <typename VST> //元素类型，操作器
void BinNode<T>::travLevel(VST& visit){ //二叉树层次遍历算法 
	Queue<BinNodePosi(T)> Q; //辅助队列
	Q.enqueue(this); //根节点入队
	while(!Q.empty()){ //在队列再次变空之前，反复迭代 
		BinNodePosi(T) x = Q.dequeue(); visit(x->data); //取出队首节点并访问之
		if(HasLChild(*x)) Q.enqueue(x->lc); //左孩子入队
		if(HasRChild(*x)) Q.enqueue(x->rc); //右孩子入队 
	} 
} 










 
