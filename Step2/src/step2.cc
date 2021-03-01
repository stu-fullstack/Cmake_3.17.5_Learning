//
// Created by huiyan on 2021/2/28.
//

#include <iostream>
#include <cmath>

#include "step2_config.h"

#ifdef USE_MYMATH
    #include "MathFunction.h"
#endif

using namespace std;

int main(int argc, char *argv[])
{

    #ifdef USE_MYMATH
        std::cout<<"USE_MYMATH True! ";
        float outputValue = mySqrt(100.0f);
        std::cout<<"mySqrt:"<<fixed<<outputValue<<std::endl;
    #else
        float outputValue = sqrt(100.f);
        std::cout<<"Sqrt:"<<fixed<<outputValue<<std::endl;
    #endif

    return 0;
}