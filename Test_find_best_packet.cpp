#include "pch.h"
#include "find_best_packet.h"

TEST(Test_find_best_packet, Test0)
{
        std::cout << typeid(find_best_packet<float, 10>::type).name() << std::endl;
}