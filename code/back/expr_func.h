#ifndef MATHCALC_EXPR_H
#define MATHCALC_EXPR_H

#include<string>
typedef std::string str;
#include<cmath>
#include<type_traits>

#include"tools\hpcalc.h"
typedef grnum::HP HP;
#include"tools\numch_func.h"
#include"tools\convert_func.h"


constexpr int NUMTYPE = 1;
constexpr int OPTYPE = 2;
constexpr int HEADTYPE = -1;//头指针,不存值
constexpr int TAILTYPE = -2;//尾指针,不存值
int ori_lv[130], MAX_ORI_LV = 4;
constexpr int POW_LIMIT = 7;

template<typename T>
struct Token{
    //Token类型
    int type;

    //如果这个Token是数
    T num;

    //如果这个Token是运算符
    char op;
    int op_lv;

    //链表指针
    Token* prev;
    Token* next;

    Token(){
        type = 0;
        num = 0;
        op = 0;
        op_lv = 0;
        prev = nullptr;
        next = nullptr;
    }
};

template<typename T>
void new_num_tk(Token<T>*& prev, T num){
    Token<T>* item = new Token<T>;
    Token<T>* next = prev->next;
    item->type = NUMTYPE;
    item->num = num;

    item->next = next;
    next->prev = item;
    item->prev = prev;
    prev->next = item;

    prev = item;
}
template<typename T>
void new_op_tk(Token<T>*& prev, char op, int lv){
    Token<T>* item = new Token<T>;
    Token<T>* next = prev->next;
    item->type= OPTYPE;
    item->op = op, item->op_lv = lv;

    item->next = next;
    next->prev = item;
    item->prev = prev;
    prev->next = item;

    prev = item;
}

template<typename T>
void clear_tk(Token<T>* head){
    Token<T>* tmp = head->next;
    Token<T>* del;
    while(tmp->type != TAILTYPE){
        del = tmp, tmp = tmp->next;
        delete del;
    }
    delete head;
    delete tmp;
}

// void hp_print_tk(Token* head){
//     Token* temp = head;
//     while(temp->type != TAILTYPE){
//         putchar('[');
//         if(temp->type == NUMTYPE){
//             printf(" ");
//             grnum::putHP(temp->num);
//             printf(" ");
//         }
//         if(temp->type == OPTYPE){
//             printf(" %c(%d) ", temp->op, temp->op_lv);
//         }
//         temp = temp->next;
//         putchar(']');
//     }
//     puts("");
// }

void double_expr_read(Token<double>* head, str ori_input_str){
    char lst_ch = 0;
    int par_lv = 0;//括号等级
    int pos_cnt = 0; // 计数
    str temp_num = "";
    double num;
    Token<double>* lst_tk = head;

    for(auto t : ori_input_str){
        //    	putchar(t);
        //    	putchar(':');
        //    	print_tk(head);
        //    	std::cout << "temp_num:" << temp_num << std::endl;
        // in_log(t);
        //        putchar(t);
        // if(t < 20) break;//换行符
        if(t<33 || t==',' || t=='_') continue;//忽略空格逗号下划线
        if(is_digit(t) || t == '.'){
            if(lst_ch == ')'){
                throw Err(INPUT_ERR, pos_cnt, pos_cnt);
                return;
            }
            else temp_num += t;
        }else{
            if(temp_num!="" && temp_num!="+" && temp_num!="-"){
                //把数存起来
                try{
                    num = strTOdouble(temp_num, pos_cnt);
                }catch(Err err_info){
                    throw err_info;
                    return;
                }
                new_num_tk<double>(lst_tk, num);
                temp_num = "";
            }
            if(is_zf(t)){
                if(is_digit(lst_ch) || lst_ch==')'){
                    //这个字符当运算符存起来
                    new_op_tk(lst_tk, t, ori_lv[int(t)]+par_lv);
                }else{
                    //这个字符当正负号
                    if(temp_num == "") temp_num += t;
                    else{
                        throw Err(INPUT_ERR, pos_cnt, pos_cnt);
                        return;
                    }
                }
            }
            else if(is_fh(t)){
                if(is_digit(lst_ch) || lst_ch==')'){
                    new_op_tk(lst_tk, t, ori_lv[int(t)]+par_lv);
                }
                else{
                    throw Err(INPUT_ERR, pos_cnt, pos_cnt);
                    return;
                }
            }
            else if(t == '('){
                if(temp_num == "-"){
                    new_num_tk(lst_tk, -1.0);
                    new_op_tk(lst_tk, '*', par_lv+ori_lv['*']);
                    temp_num = "";
                }
                if(is_zf(lst_ch) || is_fh(lst_ch) || lst_ch=='('){
                    //括号内运算符等级提高
                    par_lv += MAX_ORI_LV;
                }
                else{
                    throw Err(INPUT_ERR, pos_cnt, pos_cnt);
                }
            }
            else if(t == ')'){
                if(is_digit(lst_ch) || lst_ch==')'){
                    par_lv -= MAX_ORI_LV;
                    if(par_lv < 0){
                        throw Err(REDUNDANT_RPAR, pos_cnt, pos_cnt);
                        return;
                    }
                }
                else{
                    throw Err(INPUT_ERR, pos_cnt, pos_cnt);
                    return;
                }
            }
            else{
                throw Err(UNKNOWN_CHAR, pos_cnt, pos_cnt);
                return;
            }
        }
        lst_ch = t;
        pos_cnt++;
    }
    pos_cnt--; // 最后一个字符
    if(par_lv > 0){
        throw Err(REDUNDANT_LPAR, -1, -1);
        return;
    }
    if(is_digit(lst_ch)){
        //把数存起来
        try{
            num = strTOdouble(temp_num, pos_cnt);
        }catch(Err err_info){
            throw err_info;
            return;
        }
        new_num_tk<double>(lst_tk, num);
        temp_num = "";
    }else if(lst_ch != ')'){
        throw Err(INPUT_ERR, pos_cnt, pos_cnt);
        return;
    }
}
void hp_expr_read(Token<HP>* head, str ori_input_str){
    char lst_ch = 0;
    int par_lv = 0;//括号等级
    int pos_cnt = 0; // 计数
    str temp_num = "";
    HP num;
    Token<HP>* lst_tk = head;

    for(auto t : ori_input_str){
        if(t<33 || t==',' || t=='_') continue;//忽略空格逗号下划线
        if(is_digit(t)){
            if(lst_ch == ')'){
                throw Err(INPUT_ERR, pos_cnt, pos_cnt);
                return;
            }
            else temp_num += t;
        }else{
            if(temp_num!="" && temp_num!="+" && temp_num!="-"){
                //把数存起来
                num = HP(temp_num);
                if(num.isEMPTY()){
                    throw Err(INPUT_ERR, pos_cnt, pos_cnt);
                    return;
                }
                new_num_tk<HP>(lst_tk, num);
                temp_num = "";
            }
            if(is_zf(t)){
                if(is_digit(lst_ch) || lst_ch==')'){
                    //这个字符当运算符存起来
                    new_op_tk(lst_tk, t, ori_lv[int(t)]+par_lv);
                }else{
                    //这个字符当正负号
                    if(temp_num == "") temp_num += t;
                    else{
                        throw Err(INPUT_ERR, pos_cnt, pos_cnt);
                        return;
                    }
                }
            }
            else if(is_fh(t)){
                if(is_digit(lst_ch) || lst_ch==')'){
                    new_op_tk(lst_tk, t, ori_lv[int(t)]+par_lv);
                }
                else{
                    throw Err(INPUT_ERR, pos_cnt, pos_cnt);
                    return;
                }
            }
            else if(t == '('){
                if(temp_num == "-"){
                    new_num_tk(lst_tk, HP(-1));
                    new_op_tk(lst_tk, '*', par_lv+ori_lv['*']);
                    temp_num = "";
                }
                if(is_zf(lst_ch) || is_fh(lst_ch) || lst_ch=='('){
                    //括号内运算符等级提高
                    par_lv += MAX_ORI_LV;
                }
                else{
                    throw Err(INPUT_ERR, pos_cnt, pos_cnt);
                }
            }
            else if(t == ')'){
                if(is_digit(lst_ch) || lst_ch==')'){
                    par_lv -= MAX_ORI_LV;
                    if(par_lv < 0){
                        throw Err(REDUNDANT_RPAR, pos_cnt, pos_cnt);
                        return;
                    }
                }
                else{
                    throw Err(INPUT_ERR, pos_cnt, pos_cnt);
                    return;
                }
            }
            else{
                throw Err(UNKNOWN_CHAR, pos_cnt, pos_cnt);
                return;
            }
        }
        lst_ch = t;
        pos_cnt++;
    }
    pos_cnt--; // 最后一个字符
    if(par_lv > 0){
        throw Err(REDUNDANT_LPAR, -1, -1);
        return;
    }
    if(is_digit(lst_ch)){
        //把数存起来
        num = HP(temp_num);
        if(num.isEMPTY()){
            throw Err(INPUT_ERR, pos_cnt, pos_cnt);
            return;
        }
        new_num_tk<HP>(lst_tk, num);
        temp_num = "";
    }else if(lst_ch != ')'){
        throw Err(INPUT_ERR, pos_cnt, pos_cnt);
        return;
    }
}

template<typename T>
void math_check(T a, char op, T b){
    if(op=='+' || op=='-') return;
    if(op == '*') return;
    if(op == '/'){
        if(b == 0){
            throw Err(DIV_BY_ZERO, -1, -1);
            return;
        }
    }
    if(op == '%'){
        if(b == 0){
            throw Err(MOD_BY_ZERO, -1, -1);
            return;
        }
    }
    if(op == '^'){
        if(b < 0){
            throw Err(NEGA_POWER, -1, -1);
            return;
        }
        if(a==0 && b==0){
            throw Err(ZERO_POW_ZERO, -1, -1);
        }
        if constexpr (std::is_same_v<T, HP>){
            if(a!=0 && a!=1 && a!=-1){
                if(b.size() > POW_LIMIT){
                    throw Err(LARGE_NUM, -1, -1);
                    return;
                }
            }
        }
    }
    return;
}

template<typename T>
T calculate(Token<T>* head){
    Token<T>* tail=head;
    Token<T>* i;
    Token<T> *lop, *rop, *nop;
    Token<T> *lnum, *rnum, *nnum;
    int max_lv = 0, cur_lv;
    int num_cnt = 0, op_cnt = 0;
    char op;
    T a=0, b=0, c=0;

    while(tail->type != TAILTYPE){
        max_lv = max(max_lv, tail->op_lv);
        num_cnt += (tail->type) == NUMTYPE;
        op_cnt += (tail->type) == OPTYPE;
        tail = tail->next;
    }
    if(num_cnt != op_cnt+1){
        throw Err(EXPR_ERR, -1, -1);
        return 0;
    }

    for(cur_lv=max_lv; cur_lv; cur_lv--){
        for(i=head; i!=tail; ){
            if(i->type == OPTYPE && i->op_lv == cur_lv){
                op = i->op;
                lnum = i->prev, lop = lnum->prev;
                rnum = i->next, rop = rnum->next;
                a = lnum->num, b = rnum->num;
                try{
                    math_check<T>(a, op, b);
                }catch(Err err_info){
                    throw err_info;
                    return 0;
                }

                if(op == '+') c = a+b;
                if(op == '-') c = a-b;
                if(op == '*') c = a*b;
                if(op == '/') c = a/b;
                if(op == '%') {
                    if constexpr (std::is_same_v<T, HP>){
                        c = a % b;
                    }else{
                        throw Err(FLOAT_MOD, -1, -1);
                        return 0;
                    }
                }
                if(op == '^'){
                    if constexpr (std::is_same_v<T, double>) c = pow(a, b);
                    if constexpr (std::is_same_v<T, HP>) c = HP_pow(a, b);
                }
                if constexpr (std::is_same_v<T, HP>){
                    if(op == '&') c = a&b;
                    if(op == '|') c = a|b;
                    if(op == '!') c = a^b;
                }
                nnum = new Token<T>;
                nnum->type = NUMTYPE;
                nnum->num = c;
                
                nop = i, i = rop;
                lop->next = nnum, nnum->prev = lop;
                rop->prev = nnum, nnum->next = rop;
                delete lnum;
                delete rnum;
                delete nop;
            }
            else{
            	i = i->next;
			}
        }
    }
    
    if(!(head->next->next == tail)){
    	return EXPR_ERR;
	}
    c = head->next->num;
    return c;
}

#endif
