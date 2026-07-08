#ifndef MATHCALC_ERR_H
#define MATHCALC_ERR_H

#include<string>
typedef std::string str;

constexpr int INPUT_ERR = 101;
constexpr int MULTIPLE_DOT = 102;
constexpr int REDUNDANT_LPAR = 103;
constexpr int REDUNDANT_RPAR = 104;
constexpr int UNKNOWN_CHAR = 105;
constexpr int EXPR_ERR = 106;

constexpr int DIV_BY_ZERO = 201;
constexpr int MOD_BY_ZERO = 202;
constexpr int NEGA_POWER = 203;
constexpr int ZERO_POW_ZERO = 204;
constexpr int FLOAT_MOD = 205;
constexpr int LARGE_NUM = 206;

constexpr int CALC_ERR = 301;

constexpr int NOT_POSI_INT = 401;

struct Err{
	int stp, enp;
    int err_code;

    Err(int error_code, int st, int en){
        err_code = error_code;
        stp = st, enp = en;
    }
};

inline bool isDouble(str res_str) {
    if (res_str.empty()) return false;
    int i = 0, len = res_str.length();
    bool has_dot = false;
    bool has_digit = false;

    // 处理正负号
    if (res_str[i] == '+' || res_str[i] == '-') {
        i++;
        if(i >= len) return false;  // 只有符号
    }

    // 遍历剩余字符
    for (; i < len; i++) {
        char c = res_str[i];
        if (c == '.') {
            if (has_dot) return false;  // 多个小数点
            has_dot = true;
        }
        else if (c >= '0' && c <= '9') {
            has_digit = true;
        }
        else {
            return false;  // 非法字符
        }
    }

    // 至少有一个数字
    if (!has_digit) return false;

    return true; // 没有问题
}

#endif // MATHCALC_ERR_H