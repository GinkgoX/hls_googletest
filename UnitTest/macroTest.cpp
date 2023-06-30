#include"gtest/gtest.h"
#include"ac_int.h"
#include<istream>

using namespace std;

template<typename T>
inline T MAX_2(T x, T y) {
    return x > y ? x : y;
}

// a * b + c
template<typename Ta, typename Tb, typename Tc>
using MULT_ADD = typename Ta::template rt_T<Tb>::mult::template rt_T<Tc>::plus;

// sum_n(a)
template<int N, typename T>
using SUM_N = typename T::rt_unary::template set<N>::sum;

template<typename Ta, typename Tb, typename Tc>
MULT_ADD<Ta, Tb, Tc> mult_add(Ta a, Tb b, Tc c) {
    MULT_ADD<Ta, Tb, Tc> res = a * b +
    c;
    return res;
}

template<int N, typename T>
SUM_N<N, T> accumulate(T arr[N]) {
    SUM_N<N, T> acc = 0;
    for(int i = 0; i < N; i++) {
        acc += arr[i];
    }
    return acc;
}

TEST(macroTest, MAX_2) {
    uint11 b = 7;
    uint2 y = 1;
    int3 a = -4;
    EXPECT_EQ(MAX_2<int12>(a, b), 7);
}

TEST(macroTest, mult_add) {
    int8 a = 1, b = -1;
    uint8 c = 64;
    MULT_ADD<int8, int8, uint8> ans = mult_add<int8, int8, uint8>(a, b, c);
    EXPECT_EQ(ans, 63);
}


TEST(macroTest, accumulate) {
     int8 y[6];
    ac::init_array<AC_VAL_0>(&y[0], 6);
    y[0] = 2;
    y[1] = 4;
    y[2] = -1;
    y[3] = 20;
    auto ans = accumulate<6, int8>(y);
    EXPECT_EQ(ans, 25);
}



