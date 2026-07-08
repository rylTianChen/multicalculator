#ifndef MATHCALC_CALC_H
#define MATHCALC_CALC_H

#include<string>
typedef std::string str;
#include"expr_func.h"
#include"tools\init_func.h"
#include"tools/hpcalc.h"

constexpr int NT_LEN_LIMIT = 20;

double StdCalcFunc(str ori_input_str){
    init_op_lv();
    //head、tail均不存值
    Token<double>* head = new Token<double>;
    Token<double>* tail = new Token<double>;
    head->type = HEADTYPE;
    tail->type = TAILTYPE;
    head->prev = head, head->next = tail;
    tail->prev = head, tail->next = tail;

    try{
        double_expr_read(head, ori_input_str);
    }catch(Err err_info){
        clear_tk(head);
        throw err_info;
        return 0;
    }

    double res;
    try{
        res = calculate<double>(head);
    }catch(Err err_info){
        clear_tk(head);
        throw err_info;
        return 0;
    }
    clear_tk(head);
    return res;
}

HP HpCalcFunc(str ori_input_str){
    init_op_lv();
    //head、tail均不存值
    Token<HP>* head = new Token<HP>;
    Token<HP>* tail = new Token<HP>;
    head->type = HEADTYPE;
    tail->type = TAILTYPE;
    head->prev = head, head->next = tail;
    tail->prev = head, tail->next = tail;

    try{
        hp_expr_read(head, ori_input_str);
    }catch(Err err_info){
        clear_tk(head);
        throw err_info;
        return 0;
    }

    HP res;
    try{
        res = calculate<HP>(head);
    }catch(Err err_info){
        clear_tk(head);
        throw err_info;
        return 0;
    }
    clear_tk(head);
    return res;
}

str NtSqrtFunc(str ori_input_str){
    HP ori_num(ori_input_str);
    if(ori_num.isEMPTY() || ori_num.sign()<=0){
        throw Err(NOT_POSI_INT, -1, -1);
        return "";
    }
    if(ori_num.size() > NT_LEN_LIMIT){
        throw Err(LARGE_NUM, -1, -1);
        return "";
    }
    if(ori_num == 1) return "1";
    HP coef = 1, sqrt_num =ori_num, i;
    for(i=2; i*i<=sqrt_num; i++){
        while(!(sqrt_num % (i*i))){
            coef *= i;
            sqrt_num /= i*i;
        }
    }
    str res = "";
    if(coef > 1) res += str(coef);
    if(sqrt_num > 1){
        res += "√" + str(sqrt_num);
    }
    return res;
}
str NtFactorFunc(str ori_input_str){
    HP ori_num(ori_input_str);
    if(ori_num.isEMPTY() || ori_num.sign()<=0){
        throw Err(NOT_POSI_INT, -1, -1);
        return "";
    }
    if(ori_num.size() > NT_LEN_LIMIT){
        throw Err(LARGE_NUM, -1, -1);
        return "";
    }
    if(ori_num == 1) return "1";
    char is_first_factor = true;
    HP i, n = ori_num; int exp = 0;
    str res = "";
    for(i=2; i*i<=n; ){
        while(n%i == 0){
            n /= i;
            exp++;
        }
        if(exp > 0){
            if(is_first_factor) is_first_factor = false;
            else res += " * ";
            res += str(i);
            if(exp > 1) res += "^"+str(HP(exp));
        }

        if(i == 2) i++;
        else i += 2; // 优化循环次数
        exp = 0;
    }
    if (n > 1) {
        if (!is_first_factor) res += " * ";
        res += str(n);
    }
    return res;
}
HP hp_gcd(HP a, HP b){
    HP t;
    while(b != 0){
        t = a;
        a = b, b = t%b;
    }
    return a;
    // if(b == 0) return a;
    // else return hp_gcd(b, a%b);
}
str NtGcdFunc(str ori_str1, str ori_str2){
    HP a(ori_str1), b(ori_str2);
    if(a.isEMPTY() || a.sign()<=0){
        throw Err(NOT_POSI_INT, -1, -1);
        return "";
    }
    if(b.isEMPTY() || b.sign()<=0){
        throw Err(NOT_POSI_INT, -1, -1);
        return "";
    }
    if(a.size() > NT_LEN_LIMIT){
        throw Err(LARGE_NUM, -1, -1);
        return "";
    }
    if(b.size() > NT_LEN_LIMIT){
        throw Err(LARGE_NUM, -1, -1);
        return "";
    }

    if(a==1 || b==1) return "1";
    HP gcd_num = hp_gcd(a, b);
    return str(gcd_num);
}
HP hp_lcm(HP a, HP b){
    return a*b/hp_gcd(a, b);
}
str NtLcmFunc(str ori_str1, str ori_str2){
    HP a(ori_str1), b(ori_str2);
    if(a.isEMPTY() || a.sign()<=0){
        throw Err(NOT_POSI_INT, -1, -1);
        return "";
    }
    if(b.isEMPTY() || b.sign()<=0){
        throw Err(NOT_POSI_INT, -1, -1);
        return "";
    }
    if(a.size() > NT_LEN_LIMIT){
        throw Err(LARGE_NUM, -1, -1);
        return "";
    }
    if(b.size() > NT_LEN_LIMIT){
        throw Err(LARGE_NUM, -1, -1);
        return "";
    }

    if(a==1 || b==1) return "1";
    HP lcm_num = hp_lcm(a, b);
    return str(lcm_num);
}

#endif