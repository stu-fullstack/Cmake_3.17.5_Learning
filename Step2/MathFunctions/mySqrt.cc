//
// Created by huiyan on 2021/3/1.
//

#include "MathFunction.h"

float mySqrt(float number) {
    //来自维基百科
    //number 必须是 IEEE 754标准格式的32位浮点数
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long *) &y;                       // evil floating point bit level hacking（对浮点数的邪恶位元hack）
    i = 0x5f3759df - (i >> 1);               // what the fuck?（这他妈的是怎么回事？）
    y = *(float *) &i;
    y = y * (threehalfs - (x2 * y * y));   // 1st iteration （第一次迭代）
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed（第二次迭代，可以删除）

    return 1.0f / y;    //返回的 是 平方根
}