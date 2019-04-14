// Copyright (c) Nikita Lisovetin. All rights reserved.
// Licensed under the MIT License.

// Nikita Lisovetin, github.com/turing228
// Please let me know if you have any questions. It's easy to find me in google/yandex

/**********************************************************************************************************************
 * Лабораторная работа по производящим функциям. Дискретная математика, университет ИТМО, кафедра КТ                  *
 * Задача E. Деревья, избегающие левых расчёсок                                                                       *
 * Условие и решения других задач из лабораторной можно найти здесь: github.com/turing228                             *
 *                                                                                                                    *
 * Тесты в конце файла                                                                                                *
 *                                                                                                                    *
 * Алгоритм за O(k*n^2) динамикой. Это TL21. Выражаем искомый член производящей функции через члены предыдущих        *
 * производящих функций                                                                                               *
 * GNU C++ 14                                                                                                         *
 **********************************************************************************************************************/

#include <iostream>
#include <vector>

using namespace std;


const uint64_t MOD = 998244353;     // модуль, по которому производим все вычисления


vector<vector<uint64_t>> trees;

uint64_t ask(int hairbrush, int leafs) {
    if (trees[hairbrush][leafs] != -1) {
        return trees[hairbrush][leafs];
    }

    if (hairbrush == 1) {
        trees[hairbrush][leafs] = 0;
        return 0;
    }

    if (leafs == 1) {
        trees[hairbrush][leafs] = 1;
        return 1;
    }

    uint64_t ans = 0;
    for (int i = 1; i < leafs; ++i) {
        ans += ask(hairbrush - 1, i) * ask(hairbrush, leafs - i);
        ans %= MOD;
    }
    trees[hairbrush][leafs] = ans;
    return ans;
}

int main() {
    int k, n;
    cin >> k >> n;

    trees.resize(k + 1, vector<uint64_t>(n + 1, -1));
    for (int i = 1; i <= n; ++i) {
        cout << ask(k, i) << std::endl;
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