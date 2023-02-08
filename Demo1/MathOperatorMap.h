/***************************************
     文件名：MathOperatorMap.h
     作者：苏青羽
     功能描述：数学运算符映射类
     创建日期：2023-02-08
     版本：v1.0
     最后修改日期：2022-02-08
***************************************/

#ifndef _MATHOPERATORMAP_H_
#define _MATHOPERATORMAP_H_

#include "MathOperator.h"
#include<unordered_map>
#include <string>

//注册数学运算符
#define REGISTER_MATH_OPERATOR(key, T) MathOperatorMap::GetInstance() -> Register<T>(key)

//获取数学运算符类对象
#define GET_MATH_OPERATOR(key) MathOperatorMap::GetInstance() -> GetMathOperator(key)

//销毁数学运算符
#define DESTROY_MATH_OPERATOR(key) MathOperatorMap::GetInstance() -> Destroy(key)

namespace SqyMathLibrary {

    //数学运算符映射类，实现运算符类对象与运算符字符串的映射
    //该类为单例模式，只存在一个实例对象
    class MathOperatorMap {

    public: //类默认方法
        static MathOperatorMap* GetInstance(); //获取类对象实例
        ~MathOperatorMap();

    public:  //基本接口
        bool Register(std::string key, MathOperator* val);  //注册运算符，实现key-value的映射，运算符已存在-返回false
        void Destroy(std::string key); //销毁运算符
        MathOperator* GetMathOperator(std::string key);  //获取运算符

        template<typename T>  //注册运算符的函数模板，方便外部调用
        bool Register(std::string key) {
            return Register(key, new T);
        }
        
    private:  //单例模式下不可显式构造
        MathOperatorMap();
        MathOperatorMap(const MathOperatorMap&) {};
        MathOperatorMap& operator=(const MathOperatorMap&) {};
        
    private:
        static MathOperatorMap* m_Instance;  //对象实例
        std::unordered_map< std::string, MathOperator* > m_Map; //运算符类对象与运算符字符串的映射

    };

    //仅作销毁运算符映射类，无其他功能
    class DestroyMathOperatorMap {
    public:
        ~DestroyMathOperatorMap() {
            delete MathOperatorMap::GetInstance();  //该对象析构时会释放运算符映射类对象
        }
    };
}

#endif
