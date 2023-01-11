/*
 * @Author: chamip
 * @Date: 2023-01-11 09:47:32
 * @LastEditTime: 2023-01-11 10:55:23
 * @LastEditors: chamip
 * @FilePath: /github/shiqiyuCPP/week04/examples/union.cpp
 */
#include <iostream>
using namespace std;

union ipv4address{
    std::uint32_t address32;
    std::uint8_t address8[4];
};

union type_data {
    int id1;
    float id2;
    char id3;
    double id4;
    long long id5;
};

int main()
{
    union ipv4address ip;

    cout << "sizeof(ip) = " << sizeof(ip) << endl;
    cout << "----------------" << endl;
    union type_data td;
    cout << "sizeof(std::uint32_t) = " << sizeof(std::uint32_t) << endl;
    cout << "sizeof(std::uint8_t) = " << sizeof(std::uint8_t) << endl;
    cout << "sizeof(int) = " << sizeof(int) \
         << ", sizeof(double) = " << sizeof(double) \
         << ", sizeof(float) = " << sizeof(float) \
         << ", sizeof(long long) = " << sizeof(long long) << endl;
    cout << "sizeof(td) = " << sizeof(td) << endl;
    cout << "----------------" << endl;
    ip.address8[3] = 127;
    ip.address8[2] = 0;
    ip.address8[1] = 0;
    ip.address8[0] = 1;

    cout << "The address is " ;
    cout << +ip.address8[3] << ".";
    cout << +ip.address8[2] << ".";
    cout << +ip.address8[1] << ".";
    cout << +ip.address8[0] << endl;

    cout << std::hex;
    cout << "in hex " << ip.address32 << endl;

    return 0;
}
