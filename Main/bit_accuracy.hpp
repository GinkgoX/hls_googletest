#include<ac_int.h>
#include<iostream>
#include<string>

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

using namespace std;

void test_ac() {
    ac_int<14, true> x = 0;
    std::cout << x.to_string(AC_HEX, false, false) << endl;     // 0x0
    std::cout << x.to_string(AC_HEX, false, true) << endl;      // 0x0000
    std::cout << x.to_string(AC_HEX, true, false) << endl;      // +0x0
    std::cout << x.to_string(AC_HEX, true, true) << endl;       // +0x0000
    x = -1;
    std::cout << x.to_string(AC_HEX, false, false) << endl;     // 0xf
    std::cout << x.to_string(AC_HEX, false, true) << endl;      // 0x3fff
    std::cout << x.to_string(AC_HEX, true, false) << endl;      // -0x1
    std::cout << x.to_string(AC_HEX, true, true) << endl;       // -0x0001


    // variable info
    int8 a = 16.0, b = 16.0;
    uint8 c = 64;
    MULT_ADD<int8, int8, uint8> ans = mult_add<int8, int8, uint8>(a, b, c);
    std::cout << "mult_add width: " << ans.width << std::endl;

    // init array
    int8 y[6];
    ac::init_array<AC_VAL_0>(&y[0], 6);
    y[0] = 2;
    y[1] = 4;
    y[2] = -1;
    y[3] = 20;
    std::cout << "sum n width: " << accumulate<6, int8>(y) << std::endl;
}


