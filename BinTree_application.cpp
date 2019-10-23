/********************************************************************************************************************************
 * PFC编码使用的数据结构
*********************************************************************************************************************************/
#include "BinTree.h" //用BinTree实现PFC树
typedef BinTree<char> PFCTree; //PFC树
#include "Vector.h" //用Vector实现PFC森林
typedef Vector<PFCTree*> PFCForest; //PFC森林
#include "Bitmap.h" //使用位图结构实现二进制编码串
#include "Skiplist.h" //引入Skiplist式词典结构实现
typedef Skiplist<char, char*> PFCTable; //PFC编码表,词条格式为：（key = 字符，value = 编码串）
#define N_CHAR (0x80-0x20) //只考虑可打印字符
 
//基于二叉树的PFC编码 
int PFC(int argc, char* argv[]){ //PFC编码、解码算法统一测试入口 
	PFCForest* forest = initForest(); //初始化PFC森林
	PFCTree* tree = generateTree(forest); release(forest); //生成PFC编码树
	PFCTable* table = generateTable(tree); //将PFC编码转换为编码表
	for(int i=0; i<argc; i++){ //对于命令行传入的每一明文串 
		Bitmap codeString; //二进制编码串
		int n = encode(table, codeString, argv[i]); //将根据编码表生成（长度为n）
		decode(tree, codeString, n); //利用编码树，对长度为n的二进制编码串解码（直接输出） 
	} 
	release(table); release(tree); return 0; //释放编码表，编码树 
} 
