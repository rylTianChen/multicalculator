#ifndef NUMCH_GR
#define NUMCH_GR

char fh[] = "*/^%&|!";
//数相关函数
#include<cmath> //abs()
int max(int x, int y) {return x>y ? x : y;}
int min(int x, int y) {return x<y ? x : y;}
void swap(int &x, int &y) {int t = x; x = y, y = t;}
//字符相关函数
char posi_nega(char x) {return x=='+' ? '-' : '+';}
char sym_multi(char x, char y) {return x==y ? '+' : '-';}
char is_digit(char x) {return x>='0' && x<='9';}
char is_zf(char t) {return t=='+' || t=='-';}
char is_fh(char x){
    for(auto ch : fh)
        if(ch == x) return 1;
    return 0;
}
//数和符号转换函数
char int_zf(int x) {return x>=0 ? '+' : '-';}
int zf_int(char x) {return x=='+' ? 1 : -1; }

#endif
