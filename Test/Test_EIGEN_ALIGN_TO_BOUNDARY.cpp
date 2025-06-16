#include <iostream>
#include <cstdint>
#include <type_traits>
#include "pch.h"

alignas(64) int arr1[4];

int arr2[4];

struct alignas(32) S {
        char a[7];
        int b;
};

struct U {
        alignas(16) char a;
        char b;
};

struct U2 {
        char a;
        alignas(16) char b;
};

TEST(Test_EIGEN_ALIGN_TO_BOUNDARY, Test0)
{
        // µÿ÷∑¥Ú”°≤‚ ‘
        std::cout << "arr1: " << std::uintptr_t(&arr1) << "  aligned 64 ? " << ((uintptr_t(&arr1) % 64) == 0) << '\n';
        std::cout << "arr2: " << std::uintptr_t(&arr2) << "  aligned 4 ? " << ((uintptr_t(&arr2) % 4) == 0) << '\n';

        S s;
        std::cout << "S:    " << std::uintptr_t(&s) << "  aligned 32 ? " << ((uintptr_t(&s) % 32) == 0) << '\n';
        std::cout << "S.a:    " << std::uintptr_t(&s.a) << "  aligned 32 ? " << ((uintptr_t(&s.a) % 32) == 0) << '\n';
        std::cout << "S.b:    " << std::uintptr_t(&s.b) << "  aligned 32 ? " << ((uintptr_t(&s.b) % 32) == 0) << '\n';
        std::cout << "S.b:    " << std::uintptr_t(&s.b) << "  aligned 4 ? " << ((uintptr_t(&s.b) % 4) == 0) << '\n';

        U u;
        std::cout << "U:    " << std::uintptr_t(&u) << "  aligned 16 ? " << ((uintptr_t(&u) % 16) == 0) << '\n';
        std::cout << "U.a:    " << std::uintptr_t(&u.a) << "  aligned 16 ? " << ((uintptr_t(&u.a) % 16) == 0) << '\n';
        std::cout << "U.b:    " << std::uintptr_t(&u.b) << "  aligned 16 ? " << ((uintptr_t(&u.b) % 16) == 0) << '\n';

        U2 u2;
        std::cout << "U2:    " << std::uintptr_t(&u2) << "  aligned 16 ? " << ((uintptr_t(&u2) % 16) == 0) << '\n';
        std::cout << "U2.a:    " << std::uintptr_t(&u2.a) << "  aligned 16 ? " << ((uintptr_t(&u2.a) % 16) == 0) << '\n';
        std::cout << "U2.b:    " << std::uintptr_t(&u2.b) << "  aligned 16 ? " << ((uintptr_t(&u2.b) % 16) == 0) << '\n';

        std::cout << "alignof(int)=" << alignof(int) << '\n';
        std::cout << "alignof(char)=" << alignof(char) << '\n';
        std::cout << "alignof(S)=" << alignof(S) << '\n';
        std::cout << "alignof(U)=" << alignof(U) << '\n';
}