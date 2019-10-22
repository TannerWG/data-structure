#define _int64 long long
/*
//进制转换算法（递归版） 
void convert_recursive(Stack<char>& S, _int64 n, int base){ //十进制正整数n到base进制的转换（递归版）
    static char digit[] //n < n, 1 < base <= 16，新进制下的数位符号，可视base取值范围适当扩充
	= {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	if(0<n){ //在尚有余数之前，反复地 
	    S.push(digit[n % base]); //逆向记录当前最低位
        convert_recursive(S, n/base, base); //通过递归得到所有高位 
	} 
} //新进制下由高位到低位的各数位，由顶向下保存于栈S中

//进制转换算法（迭代版）
void convert_iteration(Stack<char>& S, _int64 n, int base){ //十进制正整数n到base进制的转换（迭代版）
	static char digit[] //n < n, 1 < base <= 16，新进制下的数位符号，可视base取值范围适当扩充
	= {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	while(n>0){ //由低到高，逐一计算出新进制下的各数位 
		int remainder = (int)(n%base); S.push(digit[remainder]); //余数（当前位）入栈
		n/=base; //n更新为其对base的除商 
	} 
} //新进制下由高位到低位的各数位，由顶向下保存于栈S中
*/
 
