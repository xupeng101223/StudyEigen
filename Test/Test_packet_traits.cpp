#include "pch.h"
#include "packet_traits.h"

TEST(Test_packet_traits, Test0) 
{
        std::cout << typeid(packet_traits<float>::type).name() << std::endl;
}