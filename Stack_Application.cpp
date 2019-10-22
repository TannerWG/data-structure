#define _int64 long long
#include "Stack.h"
#include<cctype>

//����ת���㷨���ݹ�棩 
void convert_recursive(Stack<char>& S, _int64 n, int base){ //ʮ����������n��base���Ƶ�ת�����ݹ�棩
    static char digit[] //n < n, 1 < base <= 16���½����µ���λ���ţ�����baseȡֵ��Χ�ʵ�����
	= {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	if(0<n){ //����������֮ǰ�������� 
	    S.push(digit[n % base]); //�����¼��ǰ���λ
        convert_recursive(S, n/base, base); //ͨ���ݹ�õ����и�λ 
	} 
} //�½������ɸ�λ����λ�ĸ���λ���ɶ����±�����ջS��

//����ת���㷨�������棩
void convert_iteration(Stack<char>& S, _int64 n, int base){ //ʮ����������n��base���Ƶ�ת���������棩
	static char digit[] //n < n, 1 < base <= 16���½����µ���λ���ţ�����baseȡֵ��Χ�ʵ�����
	= {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	while(n>0){ //�ɵ͵��ߣ���һ������½����µĸ���λ 
		int remainder = (int)(n%base); S.push(digit[remainder]); //��������ǰλ����ջ
		n/=base; //n����Ϊ���base�ĳ��� 
	} 
} //�½������ɸ�λ����λ�ĸ���λ���ɶ����±�����ջS��

//����ƥ���㷨
void trim(const char exp[], int& lo, int& hi){ //ɾ��exp[lo, hi]���������ŵ��ǰ׺����׺ 
	while((lo <= hi) && (exp[lo] != '(') && (exp[lo] != ')')) lo++; //���ҵ�һ���� 
	while((lo <= hi) && (exp[hi] != '(') && (exp[hi] != ')')) hi--; //���һ������ 
} 

int divide(const char exp[], int lo, int hi){ //�з�exp[lo, hi]��ʹexpƥ������ӱ��ʽƥ�� 
	int mi = lo; int crc = 1; //crcδ[lo, mi]��Χ����������Ŀ֮��
	while((0<crc) && (++mi<hi)){
		if(exp[mi]==')') crc--; if(exp[mi]=='(') crc++; //�������ŷֱ���� 
	} 
	return mi;
} //��mi<=hi����Ϊ�Ϸ��зֵ㣻������ζ�žֲ�������ƥ�� 

bool paren(const char exp[], int lo, int hi){ //�����ʽexp[lo, hi]�Ƿ�����ƥ�䣨�ݹ�棩 
	trim(exp, lo, hi); if(lo > hi) return true; //������������ŵ�ǰ׺����׺ 
	if(exp[lo] != '(') return false; //���ַ��������ţ���ƥ�� 
	if(exp[hi] != ')') return false; //ĩ�ַ��������ţ���ƥ��
	int mi = divide(exp, lo, hi); //ȷ���ʵ����зֵ� 
	if(mi>hi) return false; //�зֵ㲻�Ϸ�����ζ�žֲ��������岻ƥ��
	return paren(exp, lo+1, hi-1) && paren(exp, mi+1, hi); //�ֱ������ұ��ʽ 
}

//����ƥ���㷨�������棩
bool paren_iteration(const char exp[],int lo, int hi){ //���ʽ����ƥ���飬�ɼ���������� 
	Stack<char> S; //ʹ��ջ��¼�ѷ��ֵ���δƥ���������
	for(int i=lo; i<hi; i++){
		switch(exp[i]){ //������ֱ�ӽ�ջ������������ջ��ʧ�䣬����ʽ��ƥ�� 
			case '(': case '[': case '{': S.push(exp[i]); break;
			case ')': if((S.empty()) || ('(' != S.pop())) return false; break;
			case ']': if((S.empty()) || ('[' != S.pop())) return false; break;
			case '}': if((S.empty()) || ('{' != S.pop())) return false; break;
			default: break; //�������ַ�һ�ɺ��� 
		}
	} 
	return S.empty(); //�������ʽɨ�����ջ�����Բ����������ţ���ƥ�䣻����ջ�գ�ƥ�� 
} 

//��������ȼ���ϵ���� 
#define N_OPTR 9
typedef enum{ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE} Operator; //���������(+ - * / ^ ! ( ) \0 )
//�ӣ������ˣ������ˣ��׳ˣ������ţ������ţ���ʼ������ֹ�� 
const char pri[N_OPTR][N_OPTR] = { //��������ȵȼ�[ջ��][��ǰ] 
/*              |--------------------��ǰ�����-------------------|    */
/*              +    -    *    /    ^    !    (    )    \0             */
/* --  + */    '>', '>', '<', '<', '<', '<', '<', '>', '>', 
/*  |  - */    '>', '>', '<', '<', '<', '<', '<', '>', '>',
/* ջ  * */    '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* ��  / */    '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* ��  ^ */    '>', '>', '>', '>', '>', '<', '<', '>', '>',
/* ��  ! */    '>', '>', '>', '>', '>', '>', ' ', '>', '>',
/* ��  ( */    '<', '<', '<', '<', '<', '<', '<', '=', ' ',
/*  |  ) */    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
/* -- \0 */    '<', '<', '<', '<', '<', '<', '<', ' ', '='
};

//���ʽ����ֵ��RPNת��
float evaluate(char* S, char*& RPN){ //�ԣ����޳��հ׸�ģ����ʽS��ֵ����ת��Ϊ�沨��ʽRPN 
	Stack<float> opnd; Stack<char> optr; //������ջ�������ջ
	optr.push('\0'); //β�ڱ�'\0'Ҳ��Ϊͷ�ڱ�������ջ
	while(!optr.empty()){ //��������ǿ�֮ǰ�����������ʽ�и��ַ� 
		if(isdigit(*S)){  //����ǰ�ַ�Ϊ����������
			readNumber(S, opnd); append(RPN, opnd.top()); //������������������RPNĩβ 
		} 
		else{ //����ǰ�ַ�Ϊ��������� 
			switch(orderBetween(optr.top(), *S)){ //������ջ�������֮�����ȼ��ߵͷֱ��� 
				case '<': //ջ����������ȼ�����ʱ
				    optr.push(*S); S++; //�����Ƴ٣���ǰ�������ջ
					break;
				case '=': //���ȼ���ȣ���ǰ�����Ϊ�����Ż���β���ڱ�'\0'ʱ��
				    optr.pop(); S++; //�����Ų�������һ���ַ�
					break;
				case '>':{ //ջ����������ȼ�����ʱ����ʵʩ��Ӧ���㣬�������������ջ
				    char op = optr.pop(); append(RPN, op); //ջ���������ջ������RPNĩβ
					if('!'==op){ //������һԪ����� 
						float pOpnd = opnd.pop(); //ֻ��ȡ��һ������������
						opnd.push(calcu(op, pOpnd)); //ʵʩ��Ԫ���㣬�����ջ 
					}else{ //������������Ԫ������� 
						float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop(); //ȡ����/ǰ������
						opnd.push(calcu(pOpnd1, op, pOpnd2)); //ʵʩ��Ԫ���㣬�����ջ 
					}
					break;
				} 
				default: exit(-1); //���﷨���󣬲�������ֱ���˳� 
			}//switch
		}//while 
	} 
	return opnd.pop(); //������������������ 
} 

//���ֽ��� 
void readNumber(char* S, stack<float>& opnd){ //��һ�������ַ���ʼ������һ�����������֣�����'2.33'�����ַ�'2'��ʼ������2.33) 
    float num = 0; //������������ֵ
    int c = 0; //��¼λ��(������С����
    bool bDecimal = false; //С��ָʾ�� 
	while(*S){ //���ֵ�ASCII�����47-58֮�䣬'.'��ASCII��Ϊ46
		if(int(*S) == 46){ //����С���㣬�� 
			bDecimal = true; //����С��ָʾ��
			c = 1; //С��λ��
			S++; //���ַ� 
		}
		else if(isdigit(*S)){ //��С���� 
			if(!bDecimal){ //������������ 
	    	    num = num * pow(10, c) + (int(*S)-int('0'));
		        c++;
		    }
			else{ //����С������  
				num = num + pow(10, -c) * (int(*S)-int('0'));
		    	c++;
			}
			S++; //���ַ� 
		}
		else break;
	}
	opnd.push(num);
}


//�ʺ󹲴�����
struct Queen{ //�ʺ��� 
	int x, y; //�ʺ��������ϵ�λ������
	Queen(int xx=0, int yy=0): x(xx), y(yy){}; //���캯��
	bool operator== (Queen const& q) const{ //�����еȲ��������Լ�ⲻͬ�ʺ�֮����ܵĳ�ͻ
	    return(x==q.x) //�г�ͻ����һ�����ʵ�����ᷢ������ʡ��
		||(y == q.y) //�г�ͻ
		||(x + y == q.x + q.y) //�����Խ��߳�ͻ
		||(x - y == q.x - q.y); //�ظ��Խ��߳�ͻ 
	} 
	bool operator!=(Queen const& q){return !(*this == q);} //���ز��Ȳ����� 
};

void placeQueens(int N){ //N�ʺ��㷨�������棩��������̽/���ݵĲ��ԣ�����ջ��¼���ҽ�� 
	Stack<Queen> solu; //��ţ����֣����ջ
	Queen q(0, 0); //��ԭ����� 
	do{ //������̽������ 
		if(N <= solu.size() || N <= q.y){ //���ѳ��磬�� 
			q = solu.pop(); q.y++; //����һ�У���������̽��һ�� 
		}else{ //������̽��һ�� 
			while((q.y < N) && (0 <= solu.find(q))) //ͨ�������лʺ�ĶԱ�
			{q.y++; nCheck++;} //�����ҵ��ɰڷ���һ�ʺ����
			if(N > q.y){ //�����ڿɰݷõ��У��� 
				solu.push(q); //���ϵ�ǰ�ʺ󣬲�
				if(N <= solu.size()) nSolu++; //�����ֽ��ѳ�Ϊȫ�ֽ⣬��ͨ��ȫ�ֱ���nSolu����
				q.x++; q.y = 0; //ת����һ�У��ӵ�0�п�ʼ����̽��һ�ʺ� 
			} 
		}
	}while((0 < q.x) || (q.y < N)); //���з�֧���ѻ���ٻ��֦֮���㷨���� 
}


//�Թ�Ѱַ
typedef enum{AVAILABLE, ROUTE, BACKTRACKED, WALL} Status; //�Թ���Ԫ״̬ 
//ԭʼ���õģ��ڵ�ǰ·���ϵģ����з��������ʧ�ܺ���ݹ��ģ�����ʹ�õģ�ǽ��

typedef enum{UNKNOWN, EAST, SOUTH, WEST, NORTH, NO_WAY} ESWN; //��Ԫ������ڽӷ���
//δ���������ϡ�����������·��ͨ

inline ESWN nextESWN(ESWN eswn){return ESWN(eswn + 1);} //����ת����һ�ڽӷ���

struct Cell{ //�Թ���� 
	int x, y; Status status; //x���꣬y���꣬����
	ESWN incoming, outgoing; //���롢�߳����� 
}; 

#define LABY_MAX 24; //����Թ��ߴ� 
Cell laby[LABY_MAX][LABY_MAX]; //�Թ� 

//�ڸ��ѯ
inline Cell* neighbor(Cell* cell){ //��ѯ��ǰλ�õ����ڸ�� 
	switch(cell->outgoing){
		case EAST: return cell + LABY_MAX; //��
		case SOUTH: return cell + 1; //����
		case WEST: return cell - LABY_MAX; //����
		case NORTH: return cell - 1; //�� 
		default: exit(-1);
	}
} 

//���ת��
inline Cell* advance(Cell* cell){
	Cell* next;
	switch(cell->outgoing){
		case EAST:  next = cell + LABY_MAX;  next->incoming = WEST; break; //��
		case SOUTH: next = cell + 1;         next->incoming = NORTH; break; //����
		case WEST:  next = cell - LABY_MAX;  next->incoming = EAST; break; //����
		case NORTH: next = cell - 1;         next->incoming = SOUTH; break; //��
		default: exit(-1); 
	}
	return next;
} 

//�Թ�Ѱ���㷨���ڸ�Ԫs��t֮��滮һ��ͨ·�������ȷ���ڣ�
bool labyrith(Cell Laby[LABY_MAX][LABY_MAX], Cell* s, Cell* t){
	if((AVAILABLE != s->status) || (AVAILABLE != t->status)) return false; //�˻����
	Stack<Cell*> path; //��ջ��¼ͨ·��Theseus��������
	s->incoming = UNKNOWN; s->status = ROUTE; path.push(s); //���
	do{ //��������������̽�����ݣ�ֱ���ִ��յ㣬��������п��� 
		Cell* c = path.top(); //��鵱ǰλ�ã�ջ����
		if(c==t) return true; //���ѵִ��յ㣬���ҵ�һ��ͨ·����������δ̽��ķ��������̽
		while(NO_WAY > (c->outgoing = nextESWN(c->outgoing))) //��һ������з���
		    if(AVAILABLE == neighbor(c)->status) break; //��ͼ�ҵ���δ̽��ķ���
		if(NO_WAY <= c->outgoing) //�����з����ѳ��Թ�
		{c->status = BACKTRACKED; c = path.pop();} //��������һ��
		else //������ǰ��̽һ��
		{path.push(c=advance(c)); c->outgoing = UNKNOWN; c->status = ROUTE;} 
	}while(!path.empty());
	return false;
} 

 

