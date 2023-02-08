/***************************************
     文件名：Calculator.h
     作者：苏青羽
     功能描述：数学表达式计算
     创建日期：2023-02-06
     版本：v1.0
     最后修改日期：2022-02-06
***************************************/

#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include <string>

namespace SqyMathLibary {

    class Calculator {

    public:  //类默认方法

        //该类不可创建对象
        Calculator() = delete;
        ~Calculator() = delete;
        Calculator(const Calculator&) = delete;
        Calculator& operator=(const Calculator&) = delete;

    
    };

}




#endif


