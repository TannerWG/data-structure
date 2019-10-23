/********************************************************************************************************************************
 * PFC����ʹ�õ����ݽṹ
*********************************************************************************************************************************/
#include "BinTree.h" //��BinTreeʵ��PFC��
typedef BinTree<char> PFCTree; //PFC��
#include "Vector.h" //��Vectorʵ��PFCɭ��
typedef Vector<PFCTree*> PFCForest; //PFCɭ��
#include "Bitmap.h" //ʹ��λͼ�ṹʵ�ֶ����Ʊ��봮
#include "Skiplist.h" //����Skiplistʽ�ʵ�ṹʵ��
typedef Skiplist<char, char*> PFCTable; //PFC�����,������ʽΪ����key = �ַ���value = ���봮��
#define N_CHAR (0x80-0x20) //ֻ���ǿɴ�ӡ�ַ�
 
//���ڶ�������PFC���� 
int PFC(int argc, char* argv[]){ //PFC���롢�����㷨ͳһ������� 
	PFCForest* forest = initForest(); //��ʼ��PFCɭ��
	PFCTree* tree = generateTree(forest); release(forest); //����PFC������
	PFCTable* table = generateTable(tree); //��PFC����ת��Ϊ�����
	for(int i=0; i<argc; i++){ //���������д����ÿһ���Ĵ� 
		Bitmap codeString; //�����Ʊ��봮
		int n = encode(table, codeString, argv[i]); //�����ݱ�������ɣ�����Ϊn��
		decode(tree, codeString, n); //���ñ��������Գ���Ϊn�Ķ����Ʊ��봮���루ֱ������� 
	} 
	release(table); release(tree); return 0; //�ͷű���������� 
} 
