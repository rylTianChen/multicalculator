#ifndef MATHCALC_CONVERT_H
#define MATHCALC_CONVERT_H

#include<string>
typedef std::string str;
#include<cstdio>
#include<cmath>
#include<cstring>
#include<QString>
#include"err.h"
#include"numch_func.h"
#include"../log.h"

constexpr int DB_MAXN_LEN = 105;
str doubleTOstr(double ori_num){
    addLogLine(DEBUG, "Got into doubleTOstr()");
    char *s = new char[DB_MAXN_LEN]();
    sprintf(s, "%.10lf", ori_num);
    int i = strlen(s);
    addLogLine(DEBUG, "Original length of char[]: "+QString::fromStdString(str(HP(i))));
    //去除小数点后多余的0
    for(i--; i; i--){
        if(s[i-1] == '.') break;
        if(s[i] == '0') s[i] = 0;
    }
    str str_num(s);
    addLogLine(DEBUG, "String form of result: "+QString::fromStdString(str_num));
    delete[] s;
    addLogLine(DEBUG, "Exiting from doubleTOstr()");
    return str_num;
}

double strTOdouble(str ori, int ori_pos){
    //字符串合法性检查
    int i = 0, len = ori.length();
    char ch, lst_ch = 0;
    bool has_dot = false;
    if(!len) throw Err(INPUT_ERR, ori_pos, ori_pos);
    for(; i<len; i++){
        ch = ori[i];
        if(is_zf(ch)){
            if(i != 0) throw Err(INPUT_ERR, ori_pos, ori_pos);
        }
        else if(is_digit(ch)){
            // nothing
        }
        else if(ch == '.'){
            if(i == 0) throw Err(INPUT_ERR, ori_pos, ori_pos);
            if(!is_digit(lst_ch)) throw Err(INPUT_ERR, ori_pos, ori_pos);
            if(has_dot) throw Err(MULTIPLE_DOT, ori_pos+i, ori_pos+i);
            has_dot = true;
        }
        else{
            throw Err(INPUT_ERR, ori_pos, ori_pos);
        }
        lst_ch = ch;
    }

    const char *s = ori.c_str();
    double res;
    sscanf(s, "%lf", &res);
    return res;

}

str numTOsci(str num_str) {
    bool is_nega = false;
    int len = num_str.length();
    int start = 0;

    // 处理负号
    if (num_str[0] == '-') {
        is_nega = true;
        start = 1;
        len--;
    }
    if(num_str[0] == '+'){
        is_nega = false;
        start = 1;
        len--;
    }

    // 构建结果
    str result;
    if (is_nega) result = "-";

    // 第一位有效数字
    result += num_str[start];

    // 小数部分（最多保留10位）
    result += ".";
    int decimal_cnt = 0;
    for (int i = start + 1; i < len && decimal_cnt < 10; i++) {
        result += num_str[i];
        decimal_cnt++;
    }

    // 添加指数部分
    int exponent = len-start-1;
    result += "e" + std::to_string(exponent);

    return result;
}



#endif