// Copyright (c) Nikita Lisovetin. All rights reserved.
// Licensed under the MIT License.

// Nikita Lisovetin, github.com/turing228
// Please let me know if you have any questions. It's easy to find me in google/yandex

/********************************************************************************************************************************
 * Лабораторная работа по производящим функциям. Дискретная математика, университет ИТМО, кафедра КТ                            *
 * Задача B. Операции с многочленами - 2                                                                                        *
 * Условие и решения других задач из лабораторной можно найти здесь: github.com/turing228                                       *
 *                                                                                                                              *
 * Тесты в конце файла                                                                                                          *
 *                                                                                                                              *
 * Аккуратная реализация функций.                                                                                               *
 * Как брать корень из формального степенного ряда:                                                                             *
 * https://www.coursera.org/lecture/modern-combinatorics/7-10-izvliechieniie-kornia-iz-formal-nogho-stiepiennogho-riada-Yjp4D   *
 * GNU C++ 14                                                                                                                   *
 ********************************************************************************************************************************/

#include <iostream>
#include <vector>

using namespace std;


const int64_t MOD = 998244353;      // модуль, по которому производим все вычисления
int point;      // количество первых членов производящих функций во время вычислений


int64_t get_number(vector<int64_t> const &v, size_t i) {
    return i >= v.size() ? 0 : v[i];
}

vector<int64_t> sum(vector<int64_t> const &p, vector<int64_t> const &q) {
    vector<int64_t> res;

    int64_t temp;
    for (size_t i = 0; i < max(p.size(), q.size()); ++i) {
        temp = get_number(p, i) + get_number(q, i);
        temp %= MOD;
        if (temp < 0) {
            temp += MOD;
        }
        res.push_back(temp);
    }

    return res;
}

vector<int64_t> product(vector<int64_t> const &p, vector<int64_t> const &q) {
    vector<int64_t> res;

    int64_t temp;
    for (int i = 0; i <= min(point, static_cast<const int &>(p.size() + q.size() - 2)); ++i) {
        temp = 0;
        for (int j = max(0, i - int(q.size())); j <= i, j < p.size(); ++j) {
            temp = (temp + get_number(p, j) * get_number(q, i - j)) % MOD;
            if (temp < 0) {
                temp += MOD;
            }
        }
        res.push_back(temp);
    }

    return res;
}

int64_t divDmod(int64_t x, int64_t D) {
    if (x < 0) {
        x = x % MOD + MOD;
    }

    while (x % D != 0) {
        x += MOD;
    }
    return x / D;
}

vector<int64_t> squart(vector<int64_t> const &p) {
    vector<int64_t> res;
    res.push_back(1);
    vector<int64_t> powered_p;
    powered_p.push_back(1);

    for (size_t i = 1; i < point; ++i) {
        powered_p = product(vector<int64_t>(1, divDmod(3 - 2 * i, 2 * i)), powered_p);
        powered_p = product(powered_p, p);
        res = sum(res, powered_p);
    }

    return res;
}

vector<int64_t> exp(vector<int64_t> const &p) {
    vector<int64_t> res;
    res.push_back(1);
    vector<int64_t> powered_p;
    powered_p.push_back(1);

    for (size_t i = 1; i < point; ++i) {
        powered_p = product(vector<int64_t>(1, divDmod(1, i)), powered_p);
        powered_p = product(powered_p, p);
        res = sum(res, powered_p);
    }

    return res;
}

vector<int64_t> ln(vector<int64_t> const &p) {
    vector<int64_t> res;
    res.push_back(0);
    vector<int64_t> powered_p;
    powered_p.push_back(1);

    for (size_t i = 1; i < point; ++i) {
        powered_p = product(powered_p, p);
        res = sum(res, product(vector<int64_t>(1, divDmod(i % 2 == 1 ? 1 : -1, i)), powered_p));
    }

    return res;
}

void out_vector(vector<int64_t> const &v) {
    for (size_t i = 0; i < point; ++i) {
        cout << v[i] << ' ';
    }
    cout << std::endl;
}

int main() {
    ios::sync_with_stdio(false);

    size_t n;
    int m;
    cin >> n >> m;
    point = m;

    vector<int64_t> p(n + 1);
    for (size_t i = 0; i < n + 1; ++i) {
        cin >> p[i];
    }

    out_vector(squart(p));
    out_vector(exp(p));
    out_vector(ln(p));

    return 0;
}

/*
Tests:
input:
1 4
0 1
output:
1 499122177 124780544 935854081
1 1 499122177 166374059
0 1 499122176 332748118

input:
1 10
0 1
output:
1 499122177 124780544 935854081 38993920 970948609 20471808 982159361 13069056 987353473
1 1 499122177 166374059 291154603 856826403 641926577 376916469 421456191 712324701
0 1 499122176 332748118 249561088 598946612 831870294 855638017 124780544 443664157

input:
1 10
0 -1
output:
1 499122176 124780544 62390272 38993920 27295744 20471808 16084992 13069056 10890880
1 998244352 499122177 831870294 291154603 141417950 641926577 621327884 421456191 285919652
0 998244352 499122176 665496235 249561088 399297741 831870294 142606336 124780544 554580196

input:
1 10
0 2
output:
1 1 499122176 499122177 623902720 124780545 311951359 935854083 350945277 413335558
1 2 2 332748119 665496236 465847365 155282455 329579088 82394772 351058067
0 2 998244351 665496238 998244349 199648877 332748107 713031699 998244321 554580253

input:
2 10
0 1 1
output:
1 499122177 623902721 187170816 974848001 939753473 55566336 988008449 971832065 28834176
1 1 499122178 166374060 291154604 524078286 849894151 984181784 585057349 172797396
0 1 499122177 332748117 748683265 598946612 665496235 855638017 873463809 110916039

input:
10 10
0 1 -1 2 -2 3 -3 4 -4 5 -5
output:
1 499122177 623902720 686292994 850067455 752582660 141352955 968511498 701799153 245737885
1 1 499122176 166374060 291154603 191330168 267584946 684708477 931669974 223105741
0 1 499122175 332748121 748683259 598946623 998244332 855638058 873463728 443664319

input:
10 10
0 -1 1 -2 2 -3 3 -4 4 -5 5
output:
1 499122176 623902721 811073536 475725825 931954688 492298241 969486336 570194689 20883071
1 998244352 499122178 831870291 291154608 474166059 184397929 596371753 219034454 32397223
0 998244352 499122177 665496234 748683265 399297740 665496235 142606335 873463808 221832077
*/