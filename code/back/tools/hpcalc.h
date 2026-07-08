/*
欢迎使用此高精度库!
作者:天辰
版本:1.5
使用说明:
	这是一个有符号整数高精度计算库,不支持浮点数运算。
	变量类型名称为HP。例: HP a=2;可以定义一个名为a的高精度变量,它存储的整数为2。
	可以直接使用数学运算符、位运算符、逻辑运算符进行运算。例: HP a = b+2-3;
	本库中包含乘方HP_pow()。例: HP_pow(a, b)会返回a的b次方。
    输入:
        使用std::cin进行输入。
	    或者使用getHP()输入一个高精度整数。例: a = getHP();
	    getHP()会先过滤不可见字符,然后开始输入,遇到非数字字符时结束输入。
	    如果没有输入数,高精度变量的值是EMPTY。
    输出:
    	使用std::cout进行输出。
    	或者使用putHP()或putsHP()输出一个高精度数。例: putsHP(a);
		putsHP()会额外输出一个换行符。
    错误返回值:
	    若出现已知错误,返回值都是EMPTY,即空值。
	    使用isEMPTY()获得一个HP变量是否是空值。例: if(a.isEMPTY())
    注意：
    	1.负数取模规则：余数与被除数同号(例：(-7)%3=-1、7%(-3)=1)。
    	2.由于天辰不够聪明，本库不包含位运算左移、右移。
    	3.你可以从字符串构造一个高精度整数。 例:HP a = "-3298239482049823094328";
		  若此字符串不是一个数，变量的值是EMPTY。
    	4.将HP转换为int或ll时,若HP值超过int或ll范围,返回值是0。
    	5.乘方运算限制：当指数的十进制位数超过8位时,判定结果过大,HP_pow()返回EMPTY。
    	6.若计算结果出现错误，即某些位上的值是负数，返回值是EMPTY。
    	7.若参与运算的数包含EMPTY空值，数学运算符返回EMPTY，逻辑运算符返回false。
    	8.由于存储方法，长度不得超过int的范围。
    其他内置函数:
        clear():将变量的值清空为EMPTY。
        length()、size():获取变量绝对值的位数。EMPTY返回0。
        sign():获取变量的符号。正数为1, 负数为-1, 0为0。EMPTY变量的返回值为0。
        GetDigit(int p):获取从末位开始第p位的数字。若p超出范围，返回0。若变量为EMPTY，返回0。
        AppendZero(int m):在变量末尾加入m个0。要求m为正数，且添加0后总长度不超过1e8。
        RemoveTail(int m):移除末尾的m位。要求m为正数。若m超过原长度，结果为0。
		AppendZero与RemoveTail正常执行则返回0,出现错误返回1。
		reverse():将数的绝对值反转,自动去除前导零。例:-380变为-83。
		SetDigit(int p, int y): 将原数末位开始第p位设置位y。成功返回0,出现问题返回1。
								不可设置超出原数范围的位置。
		CountDigit(int x): 统计整个数中有几个x。 EMPTY的返回值是0。
		ISPalindrome(): 功能如其名。
		RemoveDigit(int p): 删除从末位开始第p位的数码。成功返回0,出现问题返回1。

	你可以直接把HP变量赋值给int、long long、bool和string。
    祝您使用愉快!
    若发现问题,请向lyrTianChen09@outlook.com反馈。
天辰还开发了一个高精度计算器。获取方式：
	链接: https://pan.baidu.com/s/1X_E5OkSiDlJ-IigefdfurA
	提取码: b2ef
*/
/*
Welcome to this high-precision library!
Authors: TianChen
Version: 1.5
Instructions:
    This is a signed arbitrary-precision integer library.
	Floating-point operations are not supported.
    The type name is HP. Example: HP a = 2; defines a high-precision variable a with value 2.
    You can directly use arithmetic operators, bitwise operators, and comparison operators.
    Example: HP a = b + 2 - 3;
    This library provides HP_pow() for exponentiation.
    Example: HP_pow(a, b) returns a raised to the power b.
	Input:
		You can use std::cin >> a;
		Or use getHP() to read a high-precision integer. e.g.: a = getHP();
		getHP() skips whitespace, reads digits until a non-digit is encountered.
		If no number is inputed, the HP variable is set to EMPTY.
	Output:
		You can use std::cout << a;
		Or use putHP() or putsHP() to print a high-precision number. e.g.: putHP(a);
		putsHP() will print an extra line break.
	Error handling:
		Known errors return EMPTY (empty/invalid value).
		Use isEMPTY() to check: if (a.isEMPTY()) ...
	Notes:
		1.Modulo rule for negative numbers: remainder has the same sign as the dividend
		  (e.g. (-7) % 3 == -1, 7 % (-3) == 1).
		2.Since TianChen is not smart enough,
		  this library does not include bitwise leftpush and rightpush.
		3.You can construct a HP number from a string. e.g.:HP a = "-3298239482049823094328";
		  If the string is not a number, the HP value will be EMPTY.
		4.Converting HP to int or long long returns 0 if the value is out of range.
		5.Exponentiation limit: if the exponent has more than 8 decimal digits,
		  HP_pow() returns EMPTY.
		6.If a calculation error occurs (i.e., negative values in some digits),
		  the return value is EMPTY.
		7.If any operand is EMPTY:
		    - arithmetic operators return EMPTY
		    - comparison & logical operators return false
		8.Because of storage method, the length may not exceed the range of int.
	Other built-in functions:
		clear(): Clears the variable's value to EMPTY.
		length(), size(): Gets the number of digits of the variable's absolute value.
		                  The return value of EMPTY is 0.
		sign(): Gets the sign of the variable. Returns 1 for positive, -1 for negative, 0 for zero.
		        The return value of EMPTY is 0.
		GetDigit(int p): Gets the p-th digit starting from the least significant digit (rightmost).
		                 Returns 0 if p is out of range.
						 Returns 0 if the variable is EMPTY.
        AppendZero(int m): Appends m zeros to the end of the variable.
		                   Requires m to be positive,
						   and the total length after appending must not exceed 1e8.
        RemoveTail(int m): Removes m digits from the end of the variable.
		                   Requires m to be positive.
						   If m exceeds the original length, the result is 0.
		If AppendZero or RemoveTail runs correctly, the return value is 0.
		If an error occurs, the return value is 1.
		reverse(): reverse the absolute value and remove leading zeros. e.g.: -380 will become -83.
		SetDigit(int p, int y): Set the p-th digit from the rightmost to y.
								p should not exceed the length of the original number.
		CountDigit(int x): Count the number of digits which equals to x.
						   The return value of EMPTY is 0.
		isPalindrome(): The function is same as its name.
		RemoveDigit(int p): Remove the p-th digit from the rightmost.

	You can directly give the value of HP to int/long long/bool/string.
	Enjoy using it!
	Please report bugs to: lyrTianChen09@outlook.com
TianChen also developed a high-precision calculator.
	Download link:
    https://pan.baidu.com/s/1X_E5OkSiDlJ-IigefdfurA
    Extract code: b2ef
*/

//示范代码
//sample code
/*
#include<iostream>
#include"hpcalc.h"
using namespace grnum;
HP a, b, c;
char op;
int main(){
	while(1){
		std::cin >> a >> op >> b;
		c.clear();
		if(op == '+') c = a+b;
		if(op == '-') c = a-b;
		if(op == '*') c = a*b;
		if(op == '/') c = a/b;
		if(op == '^') c = HP_pow(a, b);
		if(op == '%') c = a%b;
		if(c.isEMPTY()) puts("Error");
		else putsHP(c);
	}
	return 0;
}
*/

#ifndef HPCALC_H
#define HPCALC_H 1031149997108990
//猜猜HPCALC_H有什么意思。
//Guess what does HPCALC_H means.

#include<vector>
#include<string>
#include<iostream>
#include<cmath>
#include<cstring>

namespace grnum{
	typedef std::vector<int> vi;
	typedef std::string str;
	typedef long long ll;

	static const char Ope[] = "*/^%";//运算符 operator
	static const int JW = 1000;//千进制 base-1000 storage
	static const int BIT_JW = 1024;
	//1024进制，用于位运算
	//base-1024 storage, used in bitwise calculation
	static const int KAR_LIMIT = 64;
	//使用Karatsuba算法的长度最小值
	//Mininum length for using Karatsuba
	static const int LEN_LIMIT = 1e8;
	static const int LL_LIMIT = 6;
	static const int MAX_INT = 2147483647, MIN_INT = -2147483648;
	static const ll MAX_LL =  9223372036854775807ll, MIN_LL = -9223372036854775807ll-1;
	static const int INT_LEN = 9, LL_LEN = 18;

	static const vi EMPTY = {0};//Error返回值 error indicator
	//EMPTY特征: EMPTY[0] = 0    Feature of EMPTY: EMPTY[0] = 0
	static const vi ONE = {1, 1}, M_ONE = {-1, 1}, ZERO = {1, 0};
	static const vi BI = {2, 24, 1};
	static const vi TWO = {1, 2}, TEN = {1, 10};

	//数相关函数 functions about numbers
	static inline ll max(ll x, ll y) {return x>y ? x : y;}
	static inline ll min(ll x, ll y) {return x<y ? x : y;}
	static inline ll abs(ll x) {return x>0 ? x : -x;}
	static inline void swap(int &x, int &y) {int t = x; x = y, y = t;}
	static inline int intTOone(ll x) {return x>0 ? 1 : -1;}

	//字符相关函数 functions about characters
	static inline char PosiNega(char x) {return x=='+' ? '-' : '+';}
	static inline char signINmul(char x, char y) {return x==y ? '+' : '-';}
	static inline bool IsDigit(char t) {return t>='0' && t<='9';}// 是数字
	static inline bool IsSign(char t) {return t=='+' || t=='-';}// 是正负号
	static inline bool IsOpe(char x){//是运算符
	    for(auto ch : Ope)
	        if(ch && ch==x) return 1;
	    return 0;
	}

	//数和符号转换函数 functions about converting of numbers and characters
	static inline char intTOsign(int x) {return x>=0 ? '+' : '-';}
	static inline char llTOsign(ll x) {return x>=0 ? '+' : '-';}
	static inline char signTOint(char x) {return x=='+' ? 1 : -1;}

	//vector相关函数 functions about vector
	static inline bool HP_IsZERO(const vi& a) {return abs(a[0])==1 && !a[1];}//是0 Checks if the value is 0
	static inline bool HP_IsONE(const vi& a) {return a[0]==1 && a[1]==1;}//是1 Checks if the value is 1
	static inline bool HP_IsM_ONE(const vi& a) {return a[0]==-1 && a[1]==1;}//是-1 Checks if the value is -1
	static inline void VecSwap(vi &a, vi &b) {a.swap(b);}
	static inline void HP_PopFrontZero(vi &a){
        int n = abs(a[0]);
        int f = a[0] > 0 ? 1 : -1;
        while(n>1 && a[n]==0) n--;
        a[0] = n*f;
        a.resize(n+3, 0);
	}//去除前导零 Remove leading zeros
	static inline short HP_VecCmp(const vi& a, const vi& b){
        int na=abs(a[0]), nb=abs(b[0]), i;
        if(na != nb) return na>nb ? 1 : -1;
        for(i=na; i>0; i--)
            if(a[i] != b[i]) return a[i]>b[i] ? 1 : -1;
        return 0;
	}//无符号整数比较大小 Compare unsigned integers
	static inline void HP_reverse(vi &a){
	    int n = abs(a[0]), i;
	    for(i=1; i+i<=n; i++)
	        swap(a[i], a[n-i+1]);
	}//倒序存储 Reverse the vector storage
	static inline int get(const vi& a, int i){
		if(i>0 && i<=abs(a[0])) return a[i];
		else return 0;
	}
	static inline vi HP_zip(const vi& a){//十进制压为千进制 Compress decimal to thousand-based
	    int f = a[0]>0 ? 1 : -1, n = abs(a[0]), i;
	    int nb = (n+2)/3;
	    vi b(nb+5, 0);
	    for(i=1; i<=n; i+=3)
			b[i/3+1] = get(a, i+2)*100+get(a, i+1)*10+get(a, i);
	    b[0] = f*nb;
	    HP_PopFrontZero(b);
	    return b;
	}
	static inline vi HP_unzip(vi a){
	    int f = a[0]>0 ? 1 : -1, n = abs(a[0]), i;
	    a.resize(n+5, 0);
	    int nb = (n<<1)+n;//n*3
	    vi b(nb+5, 0);
	    for(i=1; i<=n; i++){
	        b[i*3-3+1] = a[i]%10;
	        b[i*3-3+2] = a[i]/10%10;
	        b[i*3-3+3] = a[i]/100;
	    }
	    b[0] = f*nb;
	    HP_PopFrontZero(b);
	    return b;
	}//千进制解压为十进制 Decompress thousand-based to decimal
	static inline ll HP_vecTOll(const vi& b){
	    ll ans = 0; int nb = abs(b[0]);
	    ll sign = intTOone(b[0]);
		if(nb > 5) return 0;//可能溢出
	    while(nb) ans = ans*JW+b[nb--];
	    return ans*sign;
	}//高精度转为ll    Convert HP to long long
	static inline vi HP_intTOvec(int ai){
		if(!ai) return ZERO;
		vi b(1, 0);
		int nb = 0;
		int sign = intTOone(ai);
		ai = abs(ai);
		while(ai){
			b.push_back(ai%JW);
			ai /= JW, nb++;
		}
		b[0] = nb*sign;
		return b;
	}
	static inline vi HP_llTOvec(ll ai){
		if(!ai) return ZERO;
		vi b(1, 0);
		int nb = 0;
		int sign = intTOone(ai);
		ai = abs(ai);
		while(ai){
			b.push_back(ai%JW);
			ai /= JW, nb++;
		}
		b[0] = nb*sign;
		return b;
	}
	static inline bool HP_NumCheck(const vi& a){
		int na = abs(a[0]);
		for(; na; na--)
			if(a[na] < 0) return 1;
		return 0;
	}//合法:0 不合法:1    Valid:0 Invalid:1
	static inline void putvec(const vi& c){
		for(auto i : c) printf("%d ", i);
		puts("");
	}//调试用 used to debug

	//高精度计算函数声明
	//Declarations of HP calculation functions
	static vi HP_Plus(vi a, vi b);
	static vi HP_Minus(vi a, vi b);
	static vi HP_Multiply(vi a, vi b);
	static vi HP_Divide(vi a, vi b);
	static vi HP_Power(vi a, ll b);
	static vi HP_Module(vi a, vi b);

	//高精度位运算函数声明
	//Declarations of HP bitwise functions
	static vi HP_ThouTOBit(vi a);
	static vi HP_BitTOThou(vi a);
	static vi HP_BitAnd(vi a, vi b);
	static vi HP_BitOr(vi a, vi b);
	static vi HP_BitXor(vi a, vi b);
	static vi HP_BitNot(vi a);

	//高精度比较运算函数声明
	//Declarations of HP comparison functions
	static bool HP_gtr(const vi& a, const vi& b);
	static bool HP_geq(const vi& a, const vi& b);
	static bool HP_lss(const vi& a, const vi& b);
	static bool HP_leq(const vi& a, const vi& b);
	static bool HP_equ(const vi& a, const vi& b);
	static bool HP_neq(const vi& a, const vi& b);

	class HP{
		private:
			vi num;//高精度数,千进制 high-precision number, thousand-based
			//num[0]: 存储长度和符号,num[0]<0则num是负数
			//num[1~num[0]]: 存储数值

			//num[0]: storage length and sign, if num[0]<0, num is negative
			//num[1~num[0]]: storage the digits

			char BitIsLatest;
			//是否更新了1024进制形式
			//if 1024-based form has been updated
			vi bit;//1024进制 1024-based
			//bit[0]: 存储长度, bit[0]总是正数
			//bit[1~bit[0]-1]: 存储1024进制数值
			//bit[bit[0]]: 存储符号
			//bit存储的是补码

			//bit[0]: storates length, which is always positive
			//bit[1~bit[0]-1]: storage 1024-based value
			//bit[bit[0]]: storage sign
			//bit storage two's complement

		public:
    		/*
            变量命名规则:
            	以变量x为例。
            	若名称形如x,x是一个vi
            	若名称形如xi,xi是一个int或ll
            	若名称形如xbi,xbi是一个HP
			*/
			/*
			Variable naming rules:
				Take variable x as an example:
				If named x, it is a vi;
				if xi, it is an int or ll;
				if xbi, it is an HP.
   			*/

			//构造函数 Constructors
			HP(){
				num.clear();
				num.push_back(1);
				num.push_back(0);
				//num = ZERO
				BitIsLatest = 0;
			}
			HP(int xi){
				num.clear(), num.push_back(0);
				if(!xi){
					num[0] = 1;
					num.push_back(0);
					return;
				}
				num.reserve(INT_LEN+5);
				int n = 0;
				char z = intTOsign(xi);
				xi = abs(xi);
				while(xi){
					num.push_back(xi%10);
					xi /= 10, n++;
				}
				num[0] = signTOint(z)*n;
				num = HP_zip(num);
				BitIsLatest = 0;
			}
			HP(ll xi){
				num.clear(), num.push_back(0);
				if(!xi){
					num[0] = 1;
					num.push_back(0);
					return;
				}
				num.reserve(LL_LEN+5);
				int n = 0;
				char z = llTOsign(xi);
				xi = abs(xi);
				while(xi){
					num.push_back(xi%10);
					xi /= 10, n++;
				}
				num[0] = signTOint(z)*n;
				num = HP_zip(num);
				BitIsLatest = 0;
			}
			HP(const vi& v){
				num = v;
				BitIsLatest = 0;
			}
			HP(const str& s){
				num.clear(), num.push_back(0);
				num.reserve(s.size()+5);
				int n = 0, f=1;
				for(auto ch : s){
					if(IsDigit(ch)){
						n++;
						num.push_back(ch-48);
					}else if(IsSign(ch)){
						if(!n){
							if(ch == '+') f = 1;
							if(ch == '-') f = -1;
						}
						else{
							n = -1;
							break;
						}
					}else{
						n = -1;
						break;
					}
				}
				if(n > 0){
					num[0] = n*f;
					HP_reverse(num);
					num = HP_zip(num);
				}else{
					num = EMPTY;
					num.shrink_to_fit();
				}
				BitIsLatest = 0;
			}
			HP(const char *p){
				num.clear(), num.push_back(0);
				num.reserve(strlen(p)+5);
				int n = 0, f = 1;
				char ch;
				for(; (ch=*p); p++){
					if(IsDigit(ch)){
						n++;
						num.push_back(ch-48);
					}else if(IsSign(ch)){
						if(!n) f = -1;
						else{
							n = -1;
							break;
						}
					}else{
						n = -1;
						break;
					}
				}
				if(n > 0){
					num[0] = n*f;
					HP_reverse(num);
					num = HP_zip(num);
				}else{
					num = EMPTY;
					num.shrink_to_fit();
				}
				BitIsLatest = 0;
			}

			//析构函数 Destructor
			~HP(){
				num.clear(); num.shrink_to_fit();
				bit.clear(); bit.shrink_to_fit();
			}

			inline bool isEMPTY() const {return num[0] == 0;}
			//是否为错误值 Checks if it is the empty (error) value
    		inline void clear(){
				num.clear(), num.shrink_to_fit(), num.push_back(0);
				bit.clear(), bit.shrink_to_fit(), bit.push_back(0);
			}
			inline int length() const {
				int n = abs(num[0]), ret = n*3;
				if(n == 0) return 0;
				if(num[n] < 100) ret--;
				if(num[n] < 10) ret--;
				return ret;
			}
			inline int size() const {
				int n = abs(num[0]), ret = n*3;
				if(n == 0) return 0;
				if(num[n] < 100) ret--;
				if(num[n] < 10) ret--;
				return ret;
			}
			inline int sign() const {
				if(num[0]==1 && num[1]==0) return 0;
				else if(num[0] > 0) return 1;
				else if(num[0] < 0) return -1;
				else return 0;//EMPTY
			}
			inline int GetDigit(int p) const {
				int n = abs(num[0]);
				if(n == 0) return 0;
				if(p>n*3 || p<1) return 0;//越界 out of range
				int x = p/3, y = p%3;
				if(y == 0) return num[x]/100;
				else if(y == 1) return num[x+1]%10;
				else return num[x+1]/10%10;
			}
			int AppendZero(int m){
				if(m<1) return 1;
				if(size()+m>LEN_LIMIT) return 1;
				int n = abs(num[0]), i;
				if(n == 0) return 1;
				int x = m/3, y = m%3;
				num.resize(n+x+5);
				for(i=1; i<=n; i++) num[i+x] = num[i], num[i] = 0;
				n += x;
				num[0] = intTOone(num[0])*n;
				if(y) num = HP_Multiply(num, HP_Power(TEN, y));
				return 0;
			}
			int RemoveTail(int m){
				if(m < 1) return 1;
				int n = abs(num[0]), i;
				if(n == 0) return 1;
				int x = m/3, y = m%3;
				if(n <= x) num = ZERO;
				else{
					for(i=1; i<=n-x; i++) num[i] = num[i+x];
					for(i=n; i>n-x; i--) num[i] = 0;
					n -= x;
					num[0] = intTOone(num[0])*n;
					if(y) num = HP_Divide(num, HP_Power(TEN, y));
				}
				return 0;
			}
			inline void reverse(){
				if(!num[0]) return;
				num = HP_unzip(num);
				HP_reverse(num);
				HP_PopFrontZero(num);
				num = HP_zip(num);
			}
			inline int SetDigit(int p, int y){
				if(num[0] == 0) return 1;
				if(p < 0) return 1;
				int i = (p+2)/3, j = p-i*3+3;
				if(i > abs(num[0])) return 1;
				if(y<0 || y>9) return 1;
                int q = 0, x = 0;
				if(j == 1) q = 1, x = num[i]%10;
				if(j == 2) q = 10, x = num[i]/10%10;
				if(j == 3) q = 100, x = num[i]/100;
				num[i] -= x*q;
				num[i] += y*q;
				return 0;
			}
			inline int CountDigit(int x) const {
				if(num[0] == 0) return 0;
				if(x<1 || x>9) return 0;
				vi a = HP_unzip(num);
				int n = abs(a[0]), i, cnt = 0;
				for(i=1; i<=n; i++) cnt += a[i]==x;
				return cnt;
			}
			inline bool isPalindrome() const {
				if(num[0] == 0) return false;
				vi a = HP_unzip(num);
				int n = abs(a[0]), i;
				for(i=1; i+i<=n; i++){
					if(a[i] != a[n-i+1]) return false;
				}
				return true;
			}
			inline int RemoveDigit(int p){
				if(num[0] == 0) return 1;
				num = HP_unzip(num);
				int n = abs(num[0]), i;
				if(p<1 || p>n) return 1;
				for(i=p; i<n; i++) num[i] = num[i+1];
				num[n] = 0, n--;
				num[0] = n*intTOone(num[0]);
				num = HP_zip(num);
				return 0;
			}
			inline vi getvec(){
				return num;
			}

			//重载运算符 Overloaded operator
			HP operator+ (const HP& bbi) const {
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return HP(EMPTY);
				vi c = HP_Plus(a, b);
				return HP(c);
			}
			HP operator+ (const int bi) const {
				return *this + HP(bi);
			}
			HP operator+ (const ll bi) const {
				return *this + HP(bi);
			}
			friend HP operator+ (const int ai, const HP& bbi){
				return HP(ai) + bbi;
			}
			friend HP operator+ (const ll ai, const HP& bbi){
				return HP(ai) + bbi;
			}

			HP operator- (const HP& bbi) const {
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return HP(EMPTY);
				vi c = HP_Minus(a, b);
				return HP(c);
			}
			HP operator- (const int bi) const {
				return *this - HP(bi);
			}
			HP operator- (const ll bi) const {
				return *this - HP(bi);
			}
			friend HP operator- (const int ai, const HP& bbi){
				return HP(ai) - bbi;
			}
			friend HP operator- (const ll ai, const HP& bbi){
				return HP(ai) - bbi;
			}
			friend HP operator- (const HP& bbi){
				vi b = bbi.num;
				b[0] = -b[0];
				return HP(b);
			}

			HP operator* (const HP& bbi) const {
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return HP(EMPTY);
				vi c = HP_Multiply(a, b);
				return HP(c);
			}
			HP operator* (const int bi) const {
				return *this * HP(bi);
			}
			HP operator* (const ll bi) const {
				return *this * HP(bi);
			}
			friend HP operator* (const int ai, const HP& bbi){
				return HP(ai) * bbi;
			}
			friend HP operator* (const ll ai, const HP& bbi){
				return HP(ai) * bbi;
			}

			HP operator/ (const HP& bbi) const {
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return HP(EMPTY);
				if(HP_IsZERO(b)) return HP(EMPTY);
				//除以0,错误 Division by zero, Error
				else{
					vi c = HP_Divide(a, b);
					return HP(c);
				}
			}
			HP operator/ (const int bi) const {
				return *this / HP(bi);
			}
			HP operator/ (const ll bi) const {
				return *this / HP(bi);
			}
			friend HP operator/ (const int ai, const HP& bbi){
				return HP(ai) / bbi;
			}
			friend HP operator/ (const ll ai, const HP& bbi){
				return HP(ai) / bbi;
			}

			HP operator% (const HP& bbi) const {
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return HP(EMPTY);
				if(HP_IsZERO(b)) return HP(EMPTY);
				//模0,错误 Module by zero, Error
				else{
					vi c = HP_Module(a, b);
					return HP(c);
				}
			}
			HP operator% (const int bi) const {
				return *this % HP(bi);
			}
			HP operator% (const ll bi) const {
				return *this % HP(bi);
			}
			friend HP operator% (const int ai, const HP& bbi){
				return HP(ai) % bbi;
			}
			friend HP operator% (const ll ai, const HP& bbi){
				return HP(ai) % bbi;
			}

			//乘方 power
			friend HP HP_pow(const HP& abi, const HP& bbi){
				vi a = abi.num, b = bbi.num;
				if(!a[0] || !b[0]) return HP(EMPTY);
				if(b[0] < 0) return HP(EMPTY);//负次幂 negative exponent(not supported)
				if(HP_IsZERO(a) && HP_IsZERO(b)) return HP(EMPTY);//0^0无意义 0^0 is undefined
				if(HP_IsZERO(b)) return HP(ONE);//a^0 = 1 (a!=0)
				if(HP_IsZERO(a)) return HP(ZERO);//0^b = 0 (b!=0)
				if(HP_IsONE(a)) return HP(ONE);//1^a = 1
				if(HP_IsM_ONE(a)) return (b[1]&1) ? HP(M_ONE) : HP(ONE);//-1^a
				if(abs(a[0])>1 || a[1]>1){
					if(bbi.length() > 8) return HP(EMPTY);
				}//结果过大 result considered too large
				vi c = HP_Power(a, HP_vecTOll(b));
				return HP(c);
			}
			friend HP HP_pow(const HP& abi, int bi){
				return HP_pow(abi, HP(bi));
			}
			friend HP HP_pow(const HP& abi, ll bi){
				return HP_pow(abi, HP(bi));
			}
			friend HP HP_pow(int ai, const HP& bbi){
				return HP_pow(HP(ai), bbi);
			}
			friend HP HP_pow(ll ai, const HP& bbi){
				return HP_pow(HP(ai), bbi);
			}

			void BitUpdate(){
				if(!BitIsLatest){
					bit = HP_ThouTOBit(num);
					BitIsLatest = 1;
				}
			}
			HP operator& (HP& bbi){
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return HP(EMPTY);
				int na = abs(a[0]), nb = abs(b[0]);
				if(na<LL_LIMIT && nb<LL_LIMIT){
					ll aa = HP_vecTOll(a);
					ll bb = HP_vecTOll(b);
					return HP(aa&bb);
				}
				this->BitUpdate(), bbi.BitUpdate();
				a = this->bit, b = bbi.bit;
				vi c = HP_BitAnd(a, b);
				c = HP_BitTOThou(c);
				return HP(c);
			}
			HP operator& (HP&& bbi){
				return *this & bbi;
			}
			HP operator& (int bi){
				HP bbi(bi);
				return *this & bbi;
			}
			HP operator& (ll bi){
				HP bbi(bi);
				return *this & bbi;
			}
			friend HP operator& (int ai, HP& bbi){
				HP abi(ai);
				return abi & bbi;
			}
			friend HP operator& (ll ai, HP& bbi){
				HP abi(ai);
				return abi & bbi;
			}

			HP operator| (HP& bbi){
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return HP(EMPTY);
				int na = abs(a[0]), nb = abs(b[0]);
				if(na<LL_LIMIT && nb<LL_LIMIT){
					ll aa = HP_vecTOll(a);
					ll bb = HP_vecTOll(b);
					return HP(aa|bb);
				}
				this->BitUpdate(), bbi.BitUpdate();
				a = this->bit, b = bbi.bit;
				vi c = HP_BitOr(a, b);
				c = HP_BitTOThou(c);
				return HP(c);
			}
			HP operator| (HP&& bbi){
				return *this | bbi;
			}
			HP operator| (int bi){
				HP bbi(bi);
				return *this | bbi;
			}
			HP operator| (ll bi){
				HP bbi(bi);
				return *this | bbi;
			}
			friend HP operator| (int ai,HP& bbi){
				HP abi(ai);
				return abi | bbi;
			}
			friend HP operator| (ll ai,HP& bbi){
				HP abi(ai);
				return abi | bbi;
			}

			HP operator^ (HP& bbi){
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return HP(EMPTY);
				int na = abs(a[0]), nb = abs(b[0]);
				if(na<LL_LIMIT && nb<LL_LIMIT){
					ll aa = HP_vecTOll(a);
					ll bb = HP_vecTOll(b);
					return HP(aa^bb);
				}
				this->BitUpdate(), bbi.BitUpdate();
				a = this->bit, b = bbi.bit;
				vi c = HP_BitXor(a, b);
				c = HP_BitTOThou(c);
				return HP(c);
			}
			HP operator^ (HP&& bbi){
				return *this ^ bbi;
			}
			HP operator^ (int bi){
				HP bbi(bi);
				return *this ^ bbi;
			}
			HP operator^ (ll bi){
				HP bbi(bi);
				return *this ^ bbi;
			}
			friend HP operator^ (int ai, HP& bbi){
				HP abi(ai);
				return abi ^ bbi;
			}
			friend HP operator^ (ll ai, HP& bbi){
				HP abi(ai);
				return abi ^ bbi;
			}

			friend HP operator~ (HP& abi){
				if(!abi.num[0]) return HP(EMPTY);
				int na = abs(abi.num[0]);
				if(na < LL_LIMIT){
					ll aa = HP_vecTOll(abi.num);
					return HP(~aa);
				}
				abi.BitUpdate();
				vi a = abi.bit;
				vi b = HP_BitNot(a);
				b = HP_BitTOThou(b);
				return HP(b);
			}
			friend HP operator~ (HP&& abi){
				return ~abi;
			}

			bool operator> (const HP& bbi) const {
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return false;
				return HP_gtr(a, b);
			}
			bool operator> (const int bi) const {
				return *this > HP(bi);
			}
			bool operator> (const ll bi) const {
				return *this > HP(bi);
			}
			friend bool operator> (const int ai, const HP& bbi){
				return HP(ai) > bbi;
			}
			friend bool operator> (const ll ai, const HP& bbi){
				return HP(ai) > bbi;
			}

			bool operator>= (const HP& bbi) const {
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return false;
				return HP_geq(a, b);
			}
			bool operator>= (const int bi) const {
				return *this >= HP(bi);
			}
			bool operator>= (const ll bi) const {
				return *this >= HP(bi);
			}
			friend bool operator>= (const int ai, const HP& bbi){
				return HP(ai) >= bbi;
			}
			friend bool operator>= (const ll ai, const HP& bbi){
				return HP(ai) >= bbi;
			}

			bool operator< (const HP& bbi) const {
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return false;
				return HP_lss(a, b);
			}
			bool operator< (const int bi) const {
				return *this < HP(bi);
			}
			bool operator< (const ll bi) const {
				return *this < HP(bi);
			}
			friend bool operator< (const int ai, const HP& bbi){
				return HP(ai) < bbi;
			}
			friend bool operator< (const ll ai, const HP& bbi){
				return HP(ai) < bbi;
			}

			bool operator<= (const HP& bbi) const {
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return false;
				return HP_leq(a, b);
			}
			bool operator<= (const int bi) const {
				return *this <= HP(bi);
			}
			bool operator<= (const ll bi) const {
				return *this <= HP(bi);
			}
			friend bool operator<= (const int ai, const HP& bbi){
				return HP(ai) <= bbi;
			}
			friend bool operator<= (const ll ai, const HP& bbi){
				return HP(ai) <= bbi;
			}

			bool operator== (const HP& bbi) const {
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return false;
				if(a[0] != b[0]) return false;
				return HP_equ(a, b);
			}
			bool operator== (const int bi) const {
				return *this == HP(bi);
			}
			bool operator== (const ll bi) const {
				return *this == HP(bi);
			}
			friend bool operator== (const int ai, const HP& bbi){
				return HP(ai) == bbi;
			}
			friend bool operator== (const ll ai, const HP& bbi){
				return HP(ai) == bbi;
			}

			bool operator!= (const HP& bbi) const {
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return false;
				if(a[0] != b[0]) return true;
				return HP_neq(a, b);
			}
			bool operator!= (const int bi) const {
				return *this != HP(bi);
			}
			bool operator!= (const ll bi) const {
				return *this != HP(bi);
			}
			friend bool operator!= (const int ai, const HP& bbi){
				return HP(ai) != bbi;
			}
			friend bool operator!= (const ll ai, const HP& bbi){
				return HP(ai) != bbi;
			}

			friend bool operator! (const HP& bbi){
				return bbi.num[0]==1 && bbi.num[1]==0;
			}

			operator int() const {
				if(*this>MAX_INT || *this<MIN_INT) return 0;
				vi b = HP_unzip(this->num);
				if(!b[0]) return 0;
				int ai = 0, na = abs(b[0]), f = intTOone(b[0]), i;
				for(i=na; i; i--) ai = ai*10+b[i];
				ai = ai*f;
				return ai;
			}
			operator ll() const {
				if(*this>MAX_LL || *this<MIN_LL) return 0;
				vi b = HP_unzip(this->num);
				if(!b[0]) return 0;
				ll ai = 0, na = abs(b[0]), f = intTOone(b[0]), i;
				for(i=na; i; i--) ai = ai*10+b[i];
				ai = ai*f;
				return ai;
			}
			operator bool() const {
				return HP_IsZERO(num) ? false : true;
			}
			operator str() const {
				vi b = HP_unzip(num);
				str s = "";
				if(b[0] < 0) s += "-";
				for(int i=abs(b[0]); i; i--) s += b[i]+48;
				return s;
			}

			HP operator+= (const HP& bbi){
				*this = *this + bbi;
				BitIsLatest = 0;
				return *this;
			}
			HP operator+= (const int bi){
				*this = *this + HP(bi);
				BitIsLatest = 0;
				return *this;
			}
			HP operator+= (const ll bi){
				*this = *this + HP(bi);
				BitIsLatest = 0;
				return *this;
			}

			HP operator-= (const HP& bbi){
				*this = *this - bbi;
				BitIsLatest = 0;
				return *this;
			}
			HP operator-= (const int bi){
				*this = *this - HP(bi);
				BitIsLatest = 0;
				return *this;
			}
			HP operator-= (const ll bi){
				*this = *this - HP(bi);
				BitIsLatest = 0;
				return *this;
			}

			HP operator*= (const HP& bbi){
				*this = *this * bbi;
				BitIsLatest = 0;
				return *this;
			}
			HP operator*= (const int bi){
				*this = *this * HP(bi);
				BitIsLatest = 0;
				return *this;
			}
			HP operator*= (const ll bi){
				*this = *this * HP(bi);
				BitIsLatest = 0;
				return *this;
			}

			HP operator/= (const HP& bbi){
				*this = *this / bbi;
				BitIsLatest = 0;
				return *this;
			}
			HP operator/= (const int bi){
				*this = *this / HP(bi);
				BitIsLatest = 0;
				return *this;
			}
			HP operator/= (const ll bi){
				*this = *this / HP(bi);
				BitIsLatest = 0;
				return *this;
			}

			HP operator%= (const HP& bbi){
				*this = *this % bbi;
				BitIsLatest = 0;
				return *this;
			}
			HP operator%= (const int bi){
				*this = *this % HP(bi);
				BitIsLatest = 0;
				return *this;
			}
			HP operator%= (const ll bi){
				*this = *this % HP(bi);
				BitIsLatest = 0;
				return *this;
			}

			HP operator&= (HP& bbi){
				*this = *this & bbi;
				BitIsLatest = 0;
				return *this;
			}
			HP operator&= (HP&& bbi){
				return *this &= bbi;
			}
			HP operator&= (const int bi){
				HP bbi(bi);
				*this = *this & bbi;
				BitIsLatest = 0;
				return *this;
			}
			HP operator&= (const ll bi){
				HP bbi(bi);
				*this = *this & bbi;
				BitIsLatest = 0;
				return *this;
			}

			HP operator|= (HP& bbi){
				*this = *this | bbi;
				BitIsLatest = 0;
				return *this;
			}
			HP operator|= (HP&& bbi){
				return *this |= bbi;
			}
			HP operator|= (const int bi){
				HP bbi(bi);
				*this = *this | bbi;
				BitIsLatest = 0;
				return *this;
			}
			HP operator|= (const ll bi){
				HP bbi(bi);
				*this = *this | bbi;
				BitIsLatest = 0;
				return *this;
			}

			HP operator^= (HP& bbi){
				*this = *this ^ bbi;
				BitIsLatest = 0;
				return *this;
			}
			HP operator^= (HP&& bbi){
				return *this ^= bbi;
			}
			HP operator^= (const int bi){
				HP bbi(bi);
				*this = *this ^ bbi;
				BitIsLatest = 0;
				return *this;
			}
			HP operator^= (const ll bi){
				HP bbi(bi);
				*this = *this ^ bbi;
				BitIsLatest = 0;
				return *this;
			}

			HP operator++ (){
				*this = *this + HP(1);
				BitIsLatest = 0;
				return *this;
			}
			HP operator++ (int flag){
				HP temp = *this;
				*this = *this + HP(1);
				BitIsLatest = 0;
				return temp;
			}

			HP operator-- (){
				*this = *this - HP(1);
				BitIsLatest = 0;
				return *this;
			}
			HP operator-- (int flag){
				HP temp = *this;
				*this = *this - HP(1);
				BitIsLatest = 0;
				return temp;
			}

			//输入重载运算符 Overloaded input operator
			friend std::istream& operator>> (std::istream& is, HP& cbi){
				vi a(1, 0);//空值,初始值 EMPTY, the original value
				int na = 0;//数长度 length of the number
				char za = 0;//符号 sign(+/-)
				char t;//临时字符 temporary character
				while(is.get(t)){
					if(t < 33){
						//不可见字符 invisible characters
						if(na > 0) break;
						else continue;
					}
					if(!is || t==EOF) break;// 输入结束 end of input
					if(IsSign(t)){// 是正负号   the character is a sign
						if(na) break;// 已经开始输入数字了 have started to read in digits
						else if(za) break;// 已经有符号了 have a symbol already
						else za = t;
					}else if(IsOpe(t)) break;// 是其他运算符 other calculation characters
					else if(IsDigit(t)){
						a.push_back(t-48);
						na++;
					}//读入数字 read in digits
					else break;//其他字符 other characters
				}
				if(t >= 32) is.putback(t);
				if(!za) za = '+';
				a[0] = na*signTOint(za);
				if(!a[0]) cbi.num = EMPTY;
				else{
					HP_reverse(a);
					cbi.num = HP_zip(a);
				}
				return is;
			}
			//输出重载运算符 Overloaded output operator
			friend std::ostream& operator<< (std::ostream& os, const HP& cbi){
				vi c = cbi.num;
				c = HP_unzip(c);
				if(HP_IsZERO(c)) c[0] = 1;
				if(!c[0]) return os;
				int nc = abs(c[0]);
				os << (c[0]<0 ? "-" : "");
				for(; nc; nc--) os << c[nc];
				return os;
			}
			friend std::ostream& operator<< (std::ostream& os, const HP&& cbi){
				vi c = cbi.num;
				if(HP_IsZERO(c)) c[0] = 1;
				if(!c[0]) return os;
				int nc = abs(c[0]);
				os << (c[0]<0 ? "-" : "");
				for(; nc; nc--) os << c[nc];
				return os;
			}

			friend int putHP(const HP& cbi);
			friend int putsHP(const HP& cbi);
	};

	static vi HP_Plus(vi a, vi b){
	    char za=intTOsign(a[0]), zb=intTOsign(b[0]), zc;
	    int na=abs(a[0]), nb=abs(b[0]);
		if(!na || !nb) return EMPTY;
		if(na<LL_LIMIT && nb<LL_LIMIT){
			ll aa = HP_vecTOll(a);
			ll bb = HP_vecTOll(b);
			ll cc = aa+bb;
			return HP_llTOvec(cc);
		}
		if(za=='+' && zb=='-'){
			a[0] = abs(a[0]), b[0]=abs(b[0]);
			return HP_Minus(a, b);
		}//a+(-b)=a-b
		else if(za=='-' && zb=='+'){
			VecSwap(a, b);
			a[0] = abs(a[0]), b[0]=abs(b[0]);
			return HP_Minus(a, b);
		}//(-a)+b=b-a
	    else{
			if(za=='-' && zb=='-') zc = '-';//(-a)+(-b)=-(a+b)
			else zc = '+';
			int nc = max(na, nb); vi c(nc+5, 0);
			for(int i=1; i<=nc; i++){
				c[i] += get(a, i)+get(b, i);
				c[i+1] += c[i]/JW, c[i] %= JW;
			}
			if(c[nc+1]) nc++;
			c[0] = nc*signTOint(zc);
			if(HP_NumCheck(c)) c = EMPTY;
			return c;
		}
	}
	static vi HP_Minus(vi a, vi b){
	    char za=intTOsign(a[0]), zb=intTOsign(b[0]);
		int na = abs(a[0]), nb = abs(b[0]);
		if(!na || !nb) return EMPTY;
		if(na<LL_LIMIT && nb<LL_LIMIT){
			ll aa = HP_vecTOll(a);
			ll bb = HP_vecTOll(b);
			ll cc = aa-bb;
			return HP_llTOvec(cc);
		}
	    if(za=='+' && zb=='-'){
	        a[0] = abs(a[0]), b[0]=abs(b[0]);
	        return HP_Plus(a, b);
	    }//a-(-b)=a+b
	    else if(za=='-' && zb=='+'){
	        a[0]=-abs(a[0]), b[0]=-abs(b[0]);
	        return HP_Plus(a, b);
	    }//-a-b = (-a)+(-b)
	    else{
	        //a-b = a-b
	        if(za=='-' && zb=='-'){
	            VecSwap(a, b);//(-a)-(-b) = b-a
	            a[0] = -a[0], b[0]=-b[0];
	        }
	        char zc = '+';
	        if(HP_VecCmp(a, b) < 0){
	            zc = PosiNega(zc);
	            VecSwap(a, b);
	        }
	        int na=abs(a[0]), nb=abs(b[0]), i;
	        a.push_back(0);
			if(!na || !nb) return EMPTY;
	        for(i=1; i<=na; i++){
	            a[i] -= get(b, i);
	            if(a[i] < 0) a[i]+=JW, a[i+1]--;
	        }
	        a[0] = na*signTOint(zc);
	        HP_PopFrontZero(a);
			if(HP_NumCheck(a)) a = EMPTY;
	        return a;
	    }
	}
	static void HP_Karatsuba(int n, const vi& a, const vi& b, vi& c){
	    int i, j;
	    c.resize(n+n+5, 0);
	    if(n < KAR_LIMIT){
	        for(i=1; i<=n; i++)
	            for(j=1; j<=n; j++)
	                c[i+j-1] += a[i]*b[j];
	        return;
	    }

	    int m = n>>1;
	    vi aa(n-m+5, 0), bb(n-m+5, 0);
	    for(i=1; i<=n-m; i++){
	        aa[i] = a[m+i];
	        bb[i] = b[m+i];
	    }
	    vi z2; HP_Karatsuba(n-m, aa, bb, z2);
	    vi z0; HP_Karatsuba(m, a, b, z0);
	    for(i=1; i<=m; i++){
            aa[i] += a[i];
            bb[i] += b[i];
	    }
	    vi z1; HP_Karatsuba(n-m, aa, bb, z1);

	    for(i=1; i<=((n-m)<<1); i++){
	        z1[i] -= z2[i];
	        z1[i] -= z0[i];
	    }
	    //c = z2*JW^2m + z1*JW^m + z0
	    for(i=1; i<=((n-m)<<1); i++) c[i+m+m] += z2[i];
	    for(i=1; i<=((n-m)<<1); i++) c[i+m] += z1[i];
	    for(i=1; i<=(m<<1); i++) c[i] += z0[i];
	    return;
	}
	static vi HP_SimMul(vi a, vi b){
	    char za=intTOsign(a[0]), zb=intTOsign(b[0]);
	    char zc = signINmul(za, zb);
	    int na=abs(a[0]), nb=abs(b[0]);
	    int nc = na+nb, i, j;
	    // a.resize(nc+1, 0);
	    // b.resize(nc+1, 0);
	    vi c(nc+5, 0);
	    for(i=1; i<=na; i++)
	        for(j=1; j<=nb; j++)
	            c[i+j-1] += a[i]*b[j];
	    for(j=1; j<=nc; j++) c[j+1] += c[j]/JW, c[j] %= JW;
	    while(c[nc+1]) nc++;
	    c[0] = nc*signTOint(zc);
	    HP_PopFrontZero(c);
		if(HP_NumCheck(c)) c = EMPTY;
	    return c;
	}
	static vi HP_Multiply(vi a, vi b){
	    char za=intTOsign(a[0]), zb=intTOsign(b[0]);
	    char zc = signINmul(za, zb);
	    int na=abs(a[0]), nb=abs(b[0]);
		if(!na || !nb) return EMPTY;
		if(na+nb < LL_LIMIT){
			ll aa = HP_vecTOll(a);
			ll bb = HP_vecTOll(b);
			ll cc = aa*bb;
			return HP_llTOvec(cc);
		}
	    int nc = na+nb;
	    a.resize(nc+1, 0);
	    b.resize(nc+1, 0);
	    if(na<KAR_LIMIT || nb<KAR_LIMIT) return HP_SimMul(a, b);
	    if(na<sqrt(nb) || nb<sqrt(na)) return HP_SimMul(a, b);
	    vi c(1, 0); HP_Karatsuba(nc, a, b, c);
	    int limit = c.size()-1;
	    for(int i=1; i<limit; i++){
	        c[i+1] += c[i]/JW, c[i] %= JW;
	        if(c[i] < 0) c[i] += JW, c[i+1]--;
	    }
	    nc = limit;
	    while(nc>1 && !c[nc]) nc--;
	    c.resize(nc + 1);
	    c[0] = nc*signTOint(zc);
		if(HP_NumCheck(c)) c = EMPTY;
	    return c;
	}//感谢星星老师和Gemini帮忙调试乘法算法!
	 //Thanks to Teacher Stars and Gemini for helping debug the multiplication algorithm!
	static char HP_DivCmp(int r, int n, const vi &a, const vi &b){
	    if(a[r+n] > 0) return true;
	    if(a[r+n] < 0) return false;
	    for(int i=n; i>0; i--){
	        if(a[r+i-1] > b[i]) return true;
	        if(a[r+i-1] < b[i]) return false;
	    }
	    return true;
	}
	static inline int HP_DivEst(const vi& a, const vi& b, int i, int nb){
		int a0 = get(a, i+1);
		int a1 = get(a, i);
		int b1 = get(b, nb), b2 = get(b, nb-1);
		int aa = a0*JW*JW + a1*JW;
		int bb = b1*JW + b2;
        if(bb != 0) return aa / bb;
        else return 1;
	}
	static vi HP_Divide(vi a, vi b){
	    char za=intTOsign(a[0]), zb=intTOsign(b[0]);
	    char zc = signINmul(za, zb);
	    int na=abs(a[0]), nb=abs(b[0]);
		if(!na || !nb) return EMPTY;
		if(na < nb) return ZERO;
		if(na<LL_LIMIT && nb<LL_LIMIT){
			ll aa = HP_vecTOll(a);
			ll bb = HP_vecTOll(b);
			ll cc = aa/bb;
			return HP_llTOvec(cc);
		}
	    int nc = na-nb+5;
		vi c(nc+5, 0);
		a.resize(na+5, 0), b.resize(nb+5, 0);
	    int i, j, q, t;
	    for(i=na-nb+1; i>0; i--){
			q = HP_DivEst(a, b, i+nb-1, nb);
			if(q > 0){
				for(j=1; j<=nb; j++){
					a[i+j-1] -= b[j]*q;
					if(a[i+j-1] < 0){
						t = (-a[i+j-1]+JW-1) / JW;
						a[i+j-1] += t*JW;
						a[i+j] -= t;
					}
				}
				c[i] += q;
			}
			while(!HP_DivCmp(i, nb, a, b)){
	            // 估高了，加回一个除数
	            for(j=1; j<=nb; j++){
	                a[i+j-1] += b[j];
	                if(a[i+j-1] >= JW){
	                    a[i+j-1] -= JW;
	                    a[i+j]++;
	                }
	            }
	            c[i]--;
       		}
	        while(HP_DivCmp(i, nb, a, b)){
	            for(j=1; j<=nb; j++){
	                a[i+j-1] -= b[j];
	                if(a[i+j-1] < 0) a[i+j-1]+=JW, a[i+j]--;
	            }
	            c[i]++;
	        }
	    }
	    c[0] = nc*signTOint(zc);
	    HP_PopFrontZero(c);
		if(HP_NumCheck(c)) c = EMPTY;
	    return c;
	}
	static vi HP_Power(vi a, ll b){
	    vi c = ONE;
		while(b){
			if(b & 1) c = HP_Multiply(c, a), b--;
			else a = HP_Multiply(a, a), b >>= 1;
		}
		if(HP_NumCheck(c)) c = EMPTY;
		return c;
	}
	static vi HP_Module(vi a, vi b){
	    int na=abs(a[0]), nb=abs(b[0]);
		if(!na || !nb) return EMPTY;
		if(na < nb) return a;
		if(na<LL_LIMIT && nb<LL_LIMIT){
			ll aa = HP_vecTOll(a);
			ll bb = HP_vecTOll(b);
			ll cc = aa%bb;
			return HP_llTOvec(cc);
		}
	    a.resize(na+5), b.resize(nb+5);
	    int i, j, q, t;
	    for(i=na-nb+1; i>0; i--){
			q = HP_DivEst(a, b, i+nb-1, nb);
			if(q > 0){
				for(j=1; j<=nb; j++){
					a[i+j-1] -= b[j]*q;
					if(a[i+j-1] < 0){
						t = (-a[i+j-1]+JW-1) / JW;
						a[i+j-1] += t*JW;
						a[i+j] -= t;
					}
				}
			}
			while(!HP_DivCmp(i, nb, a, b)){
	            // 估高了，加回一个除数
	            for(j=1; j<=nb; j++){
	                a[i+j-1] += b[j];
	                if(a[i+j-1] >= JW){
	                    a[i+j-1] -= JW;
	                    a[i+j]++;
	                }
	            }
       		}
	        while(HP_DivCmp(i, nb, a, b)){
	            for(j=1; j<=nb; j++){
	                a[i+j-1] -= b[j];
	                if(a[i+j-1] < 0) a[i+j-1]+=JW, a[i+j]--;
	            }
	        }
	    }
	    HP_PopFrontZero(a);
		if(HP_NumCheck(a)) a = EMPTY;
	    return a;
	}

	HP HP_pow(int ai, int bi){
		return HP_pow(HP(ai), HP(bi));
	}
	HP HP_pow(int ai, ll bi){
		return HP_pow(HP(ai), HP(bi));
	}
	HP HP_pow(ll ai, int bi){
		return HP_pow(HP(ai), HP(bi));
	}
	HP HP_pow(ll ai, ll bi){
		return HP_pow(HP(ai), HP(bi));
	}

	static vi HP_ThouTOBit(vi a){
		//不要加引用!
		//do not use quoting!
		vi b(1, 0), temp;
		int nb = 0;
		if(HP_IsZERO(a)) a[0] = abs(a[0]);

		//取出符号，保留绝对值
		//get the sign, and keep the absolute value
		int sign = intTOone(a[0]);
		a[0] = abs(a[0]);
		//短除法转进制
		//Short Division Conversion
		while(!HP_IsZERO(a)){
			temp = HP_Module(a, BI);
			b.push_back(HP_vecTOll(temp));
			nb++;
			a = HP_Divide(a, BI);
		}

		//符号位
		//sign storage
		nb++;
		if(sign > 0) b.push_back(0);
		else b.push_back(BIT_JW-1);
		if(sign < 0){
			//取补码
			//Two's Complement
			int i;
			for(i=1; i<nb; i++) b[i] = b[i]^(BIT_JW-1);
			b[1]++;
			for(i=1; i<=nb; i++){
				b[i+1] += b[i]>>10;
				b[i] &= BIT_JW-1;
			}
		}
		b[0] = nb;
		return b;
	}
	static vi HP_BitTOThou(vi a){
		int na = a[0];
		int sign = a[na] ? -1 : 1;
		a[na] = 0;
		if(sign == -1){
			a[1]--;
			int i;
			for(i=1; i<=na; i++){
				if(a[i] < 0){
					a[i] += BIT_JW;
					a[i+1]--;
				}
			}
			for(i=1; i<na; i++) a[i] = a[i]^(BIT_JW-1);
		}
		while(na>1 && !a[na]) na--;

		vi b(2, 0), temp;
		b[0] = 1;
		for(; na; na--){
			temp = HP_intTOvec(a[na]);
			b = HP_Plus(HP_Multiply(b, BI), temp);
		}
		b[0] *= sign;
		return b;
	}
	static inline int bitget(const vi& a, int i){
		int n = a[0], sign = a[n] ? -1 : 1;
		if(i > n) return sign>0 ? 0 : (BIT_JW-1);
		else return a[i];
	}
	static vi HP_BitAnd(vi a, vi b){
		int na = a[0], nb = b[0];
		if(!na || !nb) return EMPTY;
		int nc = max(na, nb), i;
		vi c(nc+2, 0);
		for(i=1; i<=nc; i++){
			c[i] = bitget(a, i)&bitget(b, i);
		}
		c[0] = nc;
		if(HP_NumCheck(c)) c = EMPTY;
		return c;
	}
	static vi HP_BitOr(vi a, vi b){
		int na = a[0], nb = b[0];
		if(!na || !nb) return EMPTY;
		int nc = max(na, nb), i;
		vi c(nc+2, 0);
		for(i=1; i<=nc; i++){
			c[i] = bitget(a, i)|bitget(b, i);
		}
		c[0] = nc;
		if(HP_NumCheck(c)) c = EMPTY;
		return c;
	}
	static vi HP_BitXor(vi a, vi b){
		int na = a[0], nb = b[0];
		if(!na || !nb) return EMPTY;
		int nc = max(na, nb), i;
		vi c(nc+2, 0);
		for(i=1; i<=nc; i++){
			c[i] = bitget(a, i)^bitget(b, i);
		}
		c[0] = nc;
		if(HP_NumCheck(c)) c = EMPTY;
		return c;
	}
	static vi HP_BitNot(vi a){
		int na = a[0], i;
		if(!na) return EMPTY;
		for(i=1; i<=na; i++) a[i] = a[i]^(BIT_JW-1);
		if(HP_NumCheck(a)) a = EMPTY;
		return a;
	}


	static bool HP_gtr(const vi& a, const vi& b){
		int na = a[0], nb = b[0];
		if(abs(na)<LL_LIMIT && abs(nb)<LL_LIMIT){
			ll aa = HP_vecTOll(a);
			ll bb = HP_vecTOll(b);
			return aa > bb;
		}
		//异号 different signs
		if(na>0 && nb<0) return true;
		if(na<0 && nb>0) return false;
		//同号 the same sign
		int f = intTOone(na), i;
		na = abs(na), nb = abs(nb);
		if(na > nb) return f>0 ? true : false;
		if(na < nb) return f>0 ? false : true;
		for(i=na; i; i--){
			if(a[i] > b[i]) return f>0 ? true : false;
			if(a[i] < b[i]) return f>0 ? false : true;
		}
		return false;//相等 equal
	}
	static bool HP_geq(const vi& a, const vi& b){
		int na = a[0], nb = b[0];
		if(abs(na)<LL_LIMIT && abs(nb)<LL_LIMIT){
			ll aa = HP_vecTOll(a);
			ll bb = HP_vecTOll(b);
			return aa >= bb;
		}
		if(na>0 && nb<0) return true;
		if(na<0 && nb>0) return false;
		int f = intTOone(na), i;
		na = abs(na), nb = abs(nb);
		if(na > nb) return f>0 ? true : false;
		if(na < nb) return f>0 ? false : true;
		for(i=na; i; i--){
			if(a[i] > b[i]) return f>0 ? true : false;
			if(a[i] < b[i]) return f>0 ? false : true;
		}
		return true;//相等 equal
	}
	static bool HP_lss(const vi& a, const vi& b){
		int na = a[0], nb = b[0];
		if(abs(na)<LL_LIMIT && abs(nb)<LL_LIMIT){
			ll aa = HP_vecTOll(a);
			ll bb = HP_vecTOll(b);
			return aa < bb;
		}
		if(na>0 && nb<0) return false;
		if(na<0 && nb>0) return true;
		int f = intTOone(na), i;
		na = abs(na), nb = abs(nb);
		if(na > nb) return f>0 ? false : true;
		if(na < nb) return f>0 ? true : false;
		for(i=na; i; i--){
			if(a[i] > b[i]) return f>0 ? false : true;
			if(a[i] < b[i]) return f>0 ? true : false;
		}
		return false;//相等 equal
	}
	static bool HP_leq(const vi& a, const vi& b){
		int na = a[0], nb = b[0];
		if(abs(na)<LL_LIMIT && abs(nb)<LL_LIMIT){
			ll aa = HP_vecTOll(a);
			ll bb = HP_vecTOll(b);
			return aa <= bb;
		}
		if(na>0 && nb<0) return false;
		if(na<0 && nb>0) return true;
		int f = intTOone(na), i;
		na = abs(na), nb = abs(nb);
		if(na > nb) return f>0 ? false : true;
		if(na < nb) return f>0 ? true : false;
		for(i=na; i; i--){
			if(a[i] > b[i]) return f>0 ? false : true;
			if(a[i] < b[i]) return f>0 ? true : false;
		}
		return true;//相等 equal
	}
	static bool HP_equ(const vi& a, const vi& b){
		int n = abs(a[0]), i;
		if(n < LL_LIMIT){
			ll aa = HP_vecTOll(a);
			ll bb = HP_vecTOll(b);
			return aa == bb;
		}
		for(i=n; i; i--){
			if(a[i] != b[i]) return false;
		}
		return true;
	}
	static bool HP_neq(const vi& a, const vi& b){
		int n=abs(a[0]), i;
		if(n < LL_LIMIT){
			ll aa = HP_vecTOll(a);
			ll bb = HP_vecTOll(b);
			return aa != bb;
		}
		for(i=n; i; i--){
			if(a[i] != b[i]) return true;
		}
		return false;
	}

	HP getHP(){
		vi a(1, 0);
		int na = 0;// 长度 length
		char za = 0, t;// +-
		while((t = getchar())){
			if(t<=32 && na) break;
			// 读完之后不可见字符 invisible characters after reading in
			if(t == '\n'){//遇到换行符(ASCII < 20) line break (ASCII < 20)
				if(na) break;//已经有数字,输入结束 there have been digits, input ends
				else continue;//还没有数字,继续输入
				//there haven't been digits, continue to input
			}
			if(t == EOF) break;// 输入结束 end of input
			if(IsSign(t)){// 是正负号   the character is a sign
				if(na) break;// 已经开始输入数字了 have started to read in digits
				else if(za) break;// 已经有符号了 have a symbol already
				else za = t;
			}else if(IsOpe(t)) break;// 是其他运算符 other calculation characters
			else if(IsDigit(t)){
				a.push_back(t-48);
				na++;
			}//读入数字 read in digits
			else break;//其他字符 other characters
		}
		if(!za) za = '+';
		a[0] = na*signTOint(za);
		if(!a[0]) return HP(EMPTY);
		HP_reverse(a);
		a = HP_zip(a);
		return HP(a);
	}
	int putHP(const HP& cbi){
		vi c = cbi.num;
		if(HP_IsZERO(c)) c[0] = 1;
		char zc = intTOsign(c[0]);
		if(zc == '-') putchar('-');
		int nc = abs(c[0]);
		if(!nc) return 1;//EMPTY
		for(; nc; nc--){
			if(nc == abs(c[0])) printf("%d", c[nc]);
			else printf("%03d", c[nc]);
		}
		return 0;//无错误 nothing is wrong
	}
	int putsHP(const HP& cbi){
		int ret = putHP(cbi);
		puts("");
		return ret;
	}
}

#endif

