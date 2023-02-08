/***************************************
     �ļ�����MathOperatorMap.h
     ���ߣ�������
     ������������ѧ�����ӳ����
     �������ڣ�2023-02-08
     �汾��v1.0
     ����޸����ڣ�2022-02-08
***************************************/

#ifndef _MATHOPERATORMAP_H_
#define _MATHOPERATORMAP_H_

#include "MathOperator.h"
#include<unordered_map>
#include <string>

//ע����ѧ�����
#define REGISTER_MATH_OPERATOR(key, T) MathOperatorMap::GetInstance() -> Register<T>(key)

//��ȡ��ѧ����������
#define GET_MATH_OPERATOR(key) MathOperatorMap::GetInstance() -> GetMathOperator(key)

//������ѧ�����
#define DESTROY_MATH_OPERATOR(key) MathOperatorMap::GetInstance() -> Destroy(key)

namespace SqyMathLibrary {

    //��ѧ�����ӳ���࣬ʵ��������������������ַ�����ӳ��
    //����Ϊ����ģʽ��ֻ����һ��ʵ������
    class MathOperatorMap {

    public: //��Ĭ�Ϸ���
        static MathOperatorMap* GetInstance(); //��ȡ�����ʵ��
        ~MathOperatorMap();

    public:  //�����ӿ�
        bool Register(std::string key, MathOperator* val);  //ע���������ʵ��key-value��ӳ�䣬������Ѵ���-����false
        void Destroy(std::string key); //���������
        MathOperator* GetMathOperator(std::string key);  //��ȡ�����

        template<typename T>  //ע��������ĺ���ģ�壬�����ⲿ����
        bool Register(std::string key) {
            return Register(key, new T);
        }
        
    private:  //����ģʽ�²�����ʽ����
        MathOperatorMap();
        MathOperatorMap(const MathOperatorMap&) {};
        MathOperatorMap& operator=(const MathOperatorMap&) {};
        
    private:
        static MathOperatorMap* m_Instance;  //����ʵ��
        std::unordered_map< std::string, MathOperator* > m_Map; //������������������ַ�����ӳ��

    };

    //�������������ӳ���࣬����������
    class DestroyMathOperatorMap {
    public:
        ~DestroyMathOperatorMap() {
            delete MathOperatorMap::GetInstance();  //�ö�������ʱ���ͷ������ӳ�������
        }
    };
}

#endif
