#ifndef MATHCALC_CONVERT_H
#define MATHCALC_CONVERT_H

#include<string>
typedef std::string str;
#include<cstdio>
#include<cmath>
#include"err.h"

str doubleTOstr(double ori_num){
    str res = "";
    bool is_nega = false; 
    if(ori_num < 0){
        is_nega = true;
        ori_num = -ori_num;
    }
    if(ori_num == 0.0){
        return "0";
    }
    
    int int_part = (int)ori_num;
    int frac_part = int((ori_num - int_part) * 1e3 + 1e-9);
    
    // 转换整数部分
    if(int_part == 0){
        res = "0";
    }else{
        while(int_part > 0){
            char digit = '0' + (int_part % 10);
            res = digit + res;
            int_part /= 10;
        }
    }
    
    // 处理小数部分
    str frac_str = "";
    int digit_cnt = 3;
    while(digit_cnt--){
    	char digit = (frac_part % 10) + '0';
    	frac_str = digit+frac_str;
    	frac_part /= 10;
    }
    return (is_nega ? "-" : "") + res + "." + frac_str;
}

double strTOdouble(str ori, int ori_pos){
    // if(ori.empty()){
    //     throw Err(INPUT_ERR, -1, -1);  // 空字符串
    // }
    bool is_nega = false;
    int i = 0, len = ori.length();

    // 处理正负号
    if(ori[i] == '+'){
        i++;
    } else if(ori[i] == '-'){
        is_nega = true;
        i++;
    }

    // 检查符号后是否还有内容
    if(i >= len){
        throw Err(INPUT_ERR, ori_pos, ori_pos);  // 只有符号
    }

    double int_part = 0;
    double frac_part = 0;
    bool has_dot = false;
    int digit_cnt = 0;

    for(; i < len; i++){
        char c = ori[i];

        if(c == '.'){
            if(has_dot){
                throw Err(MULTIPLE_DOT, i, i);  // 多个小数点
            }
            has_dot = true;
            continue;
        }
        // if(c < '0' || c > '9'){
        //     throw Err(INVALID_CHAR, i, i);  // 非法字符
        // }
        if(!has_dot){
            // 整数部分
            int_part = int_part * 10 + (c - '0');
        } else {
            // 小数部分
            frac_part = frac_part * 10 + (c - '0');
            digit_cnt++;
        }
    }

    // 计算小数部分的值
    double result = int_part + frac_part / pow(10, digit_cnt);
    return is_nega ? -result : result;
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