// Copyright (c) Nikita Lisovetin. All rights reserved.
// Licensed under the MIT License.

// Nikita Lisovetin, github.com/turing228
// Please let me know if you have any questions. It's easy to find me in google/yandex

/**********************************************************************************************************************
 * Лабораторная работа по производящим функциям. Дискретная математика, университет ИТМО, кафедра КТ                  *
 * Задача D. Конструируемые комбинаторные классы                                                                      *
 * Условие и решения других задач из лабораторной можно найти здесь: github.com/turing228                             *
 *                                                                                                                    *
 * Тесты в конце файла                                                                                                *
 *                                                                                                                    *
 * Алгоритм за O(|input| * point^3). Аккуратно считаем, что нас просят. Парсер реализован двумя стеками.              *
 * Подсчёт числа комбинаторных объектов производящими функциями (Метод производящих функций):                         *
 * https://neerc.ifmo.ru/wiki/index.php?title=Конструирование_комбинаторных_объектов_и_их_подсчёт                     *
 * GNU C++ 14                                                                                                         *
 **********************************************************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;


const int point = 6;   // количество искомых первых членов производящей функции, заданной входящей строкой


double get_number(vector<double> const &v, size_t i) {
    return i >= v.size() ? 0 : v[i];
}

vector<double> negation(vector<double> const &p) {
    vector<double> res;

    for (const double &i : p) {
        res.push_back(-i);
    }

    return res;
}

vector<double> sum(vector<double> const &p, vector<double> const &q) {
    vector<double> res;

    double temp;
    for (size_t i = 0; i < max(p.size(), q.size()); ++i) {
        temp = get_number(p, i) + get_number(q, i);
        res.push_back(temp);
    }

    return res;
}

vector<double> product(vector<double> const &p, vector<double> const &q) {
    vector<double> res;

    double temp;
    for (int i = 0; i <= min(point, static_cast<const int &>(p.size() + q.size() - 2)); ++i) {
        temp = 0;
        for (int j = max(0, i - int(q.size())); j <= i, j < p.size(); ++j) {
            temp = (temp + get_number(p, j) * get_number(q, i - j));
        }
        res.push_back(temp);
    }

    return res;
}

vector<double> division(vector<double> const &p, vector<double> const &q) {
    vector<double> res;

    vector<double> r = p;

    int cur_pos = 0;
    while (res.size() < 25) {
        if (r.size() <= cur_pos) {
            r.push_back(0);
        }

        double next_res = r[cur_pos];   // 'cause q[0] = 1 (that is why ans is vector<double> isn't the vector<double>)

        res.push_back(next_res);

        for (int i = cur_pos; i < cur_pos + q.size(); ++i) {
            if (r.size() <= i) {
                r.push_back(0);
            }
            r[i] -= (q[i - cur_pos] * next_res);
        }

        cur_pos++;
    }

    return res;
}

double division_double(double x, double D) {
    return x / D;
}

vector<double> exp(vector<double> const &p, int point) {
    vector<double> res;
    res.push_back(1);
    vector<double> powered_p;
    powered_p.push_back(1);

    for (size_t i = 1; i < point; ++i) {
        powered_p = product(vector<double>(1, division_double(1, i)), powered_p);
        powered_p = product(powered_p, p);
        res = sum(res, powered_p);
    }

    return res;
}

vector<double> degree_msets(vector<double> const &p, int point) {
    vector<double> res(point);

    for (int i = 0; i < point; ++i) {
        for (int j = 1; j <= i; ++j) {
            if (i % j == 0) {
                if (i / j < p.size())
                    res[i] += division_double(p[i / j], j);
            }
        }
    }

    return res;
}

vector<double> normalize(vector<double> const &p) {
    vector<double> res(p.size());

    for (int i = 0; i < p.size(); ++i) {
        res[i] = llround(p[i]);
    }

    return res;
}

void out_vector(vector<double> const &v, int point) {
    for (size_t i = 0; i < point; ++i) {
        if (i >= v.size()) {
            cout << 0 << ' ';
        } else {
            cout << llround(v[i]) << ' ';
        }
    }
    cout << std::endl;
}

int main() {
    ios::sync_with_stdio(false);

    string str;

    cin >> str;

    vector<char> operations;
    vector<vector<double>> values;
    for (size_t i = 0; i < str.length(); ++i) {

        if (str[i] == 'L') {
            operations.push_back(str[i]);
        }
        if (str[i] == 'S') {
            operations.push_back(str[i]);
        }
        if (str[i] == 'P') {
            operations.push_back(str[i]);
        }

        if (str[i] == '(') {
        }
        if (str[i] == ')') {
            char operation = operations.back();
            vector<double> value = values.back();
            if (operation == 'L') {
                value[0] = 0;
                values.back() = normalize(division(vector<double>(1, 1), sum(vector<double>(1, 1), negation(value))));
                operations.pop_back();
            }
            if (operation == 'S') {
                values.back() = normalize(exp(degree_msets(value, 25), 25));
                operations.pop_back();
            }
            if (operation == 'P') {
                values.pop_back();
                vector<double> value2 = values.back();
                values.back() = normalize(product(value, value2));
                operations.pop_back();
            }
        }

        if (str[i] == 'B') {
            values.push_back(vector<double>{0, 1});
        }

    }

    out_vector(values.front(), 7);

    return 0;
}

/*
Tests:
input:
P(S(B),L(B))
output:
1 2 3 4 5 6 7

input:
S(L(B))
output:
1 1 2 3 5 7 11

input:
L(P(L(L(L(P(P(P(B,L(B)),L(B)),P(B,L(B)))))),P(B,L(B))))
output:
1 1 2 5 14 42 132

input:
P(L(B),B)
output:
0 1 1 1 1 1 1

input:
L(B)
output:
1 1 1 1 1 1 1

input:
L(L(L(B)))
output:
1 1 3 9 27 81 243
*/