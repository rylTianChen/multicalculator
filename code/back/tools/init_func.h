#ifndef MATHCALC_INIT_H
#define MATHCALC_INIT_H

// 初始化运算符优先级（只执行一次）
void init_op_lv(){
    static bool initialized = false;
    if(!initialized){
        ori_lv['+'] = ori_lv['-'] = 2;
        ori_lv['*'] = ori_lv['/'] = ori_lv['%'] = 3;
        ori_lv['^'] = 4;
        ori_lv['&'] = ori_lv['|'] = ori_lv['!'] = 1;
        initialized = true;
    }
}

#endif // INIT_FUNC_H
