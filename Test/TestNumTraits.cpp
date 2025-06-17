#include "pch.h"
#include "NumTraits.h"

TEST(TestNumTraits, Test0)
{
        std::cout << "float dummy_precision:" << NumTraits<float>::dummy_precision() << std::endl;
        std::cout << "float IsInteger:" << NumTraits<float>::IsInteger << std::endl;
        std::cout << "float IsSigned:" << NumTraits<float>::IsSigned << std::endl;
        std::cout << "float IsComplex:" << NumTraits<float>::IsComplex << std::endl;
        std::cout << "float RequireInitialization:" << NumTraits<float>::RequireInitialization << std::endl;
        std::cout << "float ReadCost:" << NumTraits<float>::ReadCost << std::endl;
        std::cout << "float AddCost:" << NumTraits<float>::AddCost << std::endl;
        std::cout << "float MulCost:" << NumTraits<float>::MulCost << std::endl;
        std::cout << "float Real:" << typeid(NumTraits<float>::Real).name() << std::endl;
        std::cout << "float NonInteger:" << typeid(NumTraits<float>::NonInteger).name() << std::endl;
        std::cout << "float Nested:" << typeid(NumTraits<float>::Nested).name() << std::endl;
        std::cout << "float Literal:" << typeid(NumTraits<float>::Literal).name() << std::endl;
        std::cout << "float digits10:" << NumTraits<float>::epsilon() << std::endl;
        std::cout << "float digits10:" << NumTraits<float>::digits10() << std::endl;
        std::cout << "float digits:" << NumTraits<float>::digits() << std::endl;
        std::cout << "float min_exponent:" << NumTraits<float>::min_exponent() << std::endl;
        std::cout << "float max_exponent:" << NumTraits<float>::max_exponent() << std::endl;
        std::cout << "float highest:" << NumTraits<float>::highest() << std::endl;
        std::cout << "float lowest:" << NumTraits<float>::lowest() << std::endl;
        std::cout << "float infinity:" << NumTraits<float>::infinity() << std::endl;
        std::cout << "float quiet_NaN:" << NumTraits<float>::quiet_NaN() << std::endl;
}