// Copyright (c) Nikita Lisovetin. All rights reserved.
// Licensed under the MIT License.

// Nikita Lisovetin, github.com/turing228
// Please let me know if you have any questions. It's easy to find me in google/yandex.

/**********************************************************************************************************************
 * Лабораторная работа по производящим функциям. Дискретная математика, университет ИТМО, кафедра КТ                  *
 * Задача F. Генератор случайных чисел (линейной реккурентой)                                                         *
 * Условие и решения других задач из лабораторной можно найти здесь: github.com/turing228                             *
 *                                                                                                                    *
 * Тесты в конце файла                                                                                                *
 *                                                                                                                    *
 * Алгоритм за O(k^2*log(n)):                                                                                         *
 * http://neerc.ifmo.ru/wiki/index.php?title=Быстрое_вычисление_членов_линейной_рекуррентной_последовательности       *
 * GNU C++ 14                                                                                                         *
 **********************************************************************************************************************/

#include <iostream>
#include <vector>

using namespace std;


const int64_t MOD = 104857601;  // модуль, по которому производим все вычисления


int64_t get_mod(int64_t number) {
    return number % MOD >= 0 ? number % MOD : (number % MOD + MOD);
}

int64_t get_number(vector<int64_t> const &v, size_t i) {
    return i >= v.size() ? 0 : v[i];
}

vector<int64_t> product(vector<int64_t> const &p, vector<int64_t> const &q) {
    vector<int64_t> res;

    int64_t temp;
    for (size_t i = 0; i <= static_cast<const int &>(p.size() + q.size() - 2); ++i) {
        temp = 0;
        for (size_t j = 0; j <= i; ++j) {
            temp = get_mod(temp + get_number(p, j) * get_number(q, i - j));
        }
        res.push_back(temp);
    }

    return res;
}

vector<int64_t> smart_negation(vector<int64_t> const &p) {
    vector<int64_t> res;

    for (size_t i = 0; i < p.size(); ++i) {
        res.push_back(i % 2 == 0 ? p[i] : -p[i]);
    }

    return res;
}

vector<int64_t> smart_squart(vector<int64_t> const &p) {
    vector<int64_t> res;

    for (size_t i = 0; i <= p.size() / 2; ++i) {
        res.push_back(p[2 * i]);
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);

    int64_t k, n;
    cin >> k >> n;
    n = n - 1;

    vector<int64_t> a(2 * k, 0);
    for (int i = 0; i < k; ++i) {
        cin >> a[i];
    }

    vector<int64_t> c(k + 1);
    for (int i = 1; i <= k; ++i) {
        cin >> c[i];
    }

    vector<int64_t> q(k + 1);
    q[0] = 1;
    for (int i = 1; i <= k; ++i) {
        q[i] = -c[i];
    }

    while (n >= k) {

        for (int i = k; i < 2 * k; ++i) {
            for (int j = 1; j <= k; ++j) {
                a[i] = get_mod(a[i] - q[j] * a[i - j]);
            }
        }

        int64_t mod2 = n % 2;
        for (size_t j = 0; j < a.size() / 2; ++j) {
            a[j] = a[2 * j + mod2];
        }
        for (size_t j = a.size() / 2; j < a.size(); ++j) {
            a[j] = 0;
        }

        q = smart_squart(product(q, smart_negation(q)));
        n = n / 2;

    }
    cout << a[n];
}

/*
Tests:
input:
3 5
1 2 3
4 5 6
output:
139

input:
3 10000000000000000
1 2 3
4 5 6
output:
87703062

input:
1 1000000000000001
1
-1
output:
1

input:
1 10000000000000000
1
-1
output:
104857600

input:
2 4
1 1
3 1
output:
13

input:
2 5
1 1
3 1
output:
43
 */