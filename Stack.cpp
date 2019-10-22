#define _int64 long long
/*
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
*/
 
