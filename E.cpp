// Copyright (c) Nikita Lisovetin. All rights reserved.
// Licensed under the MIT License.

// Nikita Lisovetin, github.com/turing228
// Please let me know if you have any questions. It's easy to find me in google/yandex.

/**********************************************************************************************************************
 * Лабораторная работа по производящим функциям. Дискретная математика, университет ИТМО, кафедра КТ                  *
 * Задача E. Деревья, избегающие левых расчёсок                                                                       *
 * Условие и решения других задач из лабораторной можно найти здесь: github.com/turing228                             *
 *                                                                                                                    *
 * Тесты в конце файла                                                                                                *
 *                                                                                                                    *
 * Алгоритм за O(k*n) динамикой снизу. Производящая функция для левой расчески порядка k легко выражается через       *
 * производящую функцию порядка k-1. Для оптимизации считаем отдельно числитель и знаменатель соответствующей дроби   *
 * для нашей функции, затем один раз делим                                                                            *
 * GNU C++ 14                                                                                                         *
 **********************************************************************************************************************/

#include <iostream>
#include <vector>


const int64_t MOD = 998244353;  // модуль, по которому производим все вычисления

int point;  // количество первых членов производящих функций во время вычислений


using namespace std;

int64_t get_number(vector<int64_t> const &v, size_t i) {
    return i >= v.size() ? 0 : v[i];
}

vector<int64_t> smart_difference(vector<int64_t> const &p, vector<int64_t> const &q) {
    vector<int64_t> res;

    int64_t temp;
    for (size_t i = 0; i < max(p.size(), q.size() + 1); ++i) {
        if (i == 0) {
            temp = get_number(p, i);
        } else {
            temp = get_number(p, i) - get_number(q, i - 1);     // that is why it's smart. result(z) = p(z) - z*q(z)
        }
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
    for (size_t i = 0; i <= min(point, static_cast<const int &>(p.size() + q.size() - 2)); ++i) {
        temp = 0;
        for (size_t j = 0; j <= i; ++j) {
            temp = (temp + get_number(p, j) * get_number(q, i - j)) % MOD;
            if (temp < 0) {
                temp += MOD;
            }
        }
        res.push_back(temp);
    }

    return res;
}

vector<int64_t> division(vector<int64_t> const &p, vector<int64_t> const &q) {
    vector<int64_t> res;

    vector<int64_t> r = p;

    int cur_pos = 0;
    while (res.size() <= point) {
        if (r.size() <= cur_pos) {
            r.push_back(0);
        }
        int64_t next_res =
                r[cur_pos] % MOD;    // 'cause q[0] = 1 (that is why ans is vector<int64_t> isn't the vector<double>)
        if (next_res < 0) {
            next_res += MOD;
        }
        res.push_back(next_res);

        for (int i = cur_pos; i < min(point, static_cast<const int &>(cur_pos + q.size())); ++i) {
            if (r.size() <= i) {
                r.push_back(0);
            }
            r[i] -= (q[i - cur_pos] * next_res) % MOD;
            r[i] %= MOD;
            if (r[i] < 0) {
                r[i] += MOD;
            }
        }

        cur_pos++;
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);

    int k, n;
    cin >> k >> n;

    point = n + 5;

    vector<int64_t> ans(2);
    ans[0] = 0;
    ans[1] = 1;

    vector<int64_t> p{1};
    vector<int64_t> q{1};
    vector<int64_t> p_new, q_new;

    for (int i = 3; i <= k; ++i) {
        p_new = q;
        q_new = smart_difference(q, p);
        p = p_new;
        q = q_new;
    }

    if (k >= 3)
        ans = division(product(vector<int64_t>{0, 1}, p), q);

    for (int i = 1; i <= n; ++i) {
        if (i >= ans.size()) {
            cout << 0 << std::endl;
        } else {
            cout << ans[i] << std::endl;
        }
    }
}

/*
Tests:
input:
4 5
output:
1
1
2
4
8

input:
7 6
output:
1
1
2
5
14
42

input:
5 10
output:
1
1
2
5
13
34
89
233
610
1597

input:
10 20
output:
1
1
2
5
14
42
132
429
1430
4861
16778
58598
206516
732825
2613834
9358677
33602822
120902914
435668420
573404868
*/