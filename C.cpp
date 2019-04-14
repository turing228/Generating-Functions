// Copyright (c) Nikita Lisovetin. All rights reserved.
// Licensed under the MIT License.

// Nikita Lisovetin, github.com/turing228
// Please let me know if you have any questions. It's easy to find me in google/yandex

/**********************************************************************************************************************
 * Лабораторная работа по производящим функциям. Дискретная математика, университет ИТМО, кафедра КТ                  *
 * Задача C. Подсчет деревьев                                                                                         *
 * Условие и решения других задач из лабораторной можно найти здесь: github.com/turing228                             *
 *                                                                                                                    *
 * Тесты в конце файла                                                                                                *
 *                                                                                                                    *
 * Алгоритм за O(n^2) динамикой. Количество деревьев заданного веса weight легко выражается через более лёгкие        *
 * деревья. Дабы не считать для одного веса кучу раз количество пар различных сыновей этого веса, которую мы подвесим *
 * на корень, будем запоминать эти количества в two_sons                                                              *
 * GNU C++ 14                                                                                                         *
 **********************************************************************************************************************/

#include <iostream>
#include <vector>

using namespace std;


const int64_t MOD = 1000000007;     // модуль, по которому производим все вычисления

vector<int64_t> tree, two_sons, weights;


int64_t ask_tree(int64_t weight);

int64_t ask_two_sons(int64_t weight) {
    if (weight < 0) {
        return 0;
    }
    if (two_sons[weight] > 0)
        return two_sons[weight];

    two_sons[weight] = 0;
    for (int i = 0; i <= weight; ++i) {
        two_sons[weight] += ask_tree(i) * ask_tree(weight - i);
        two_sons[weight] %= MOD;
    }

    return two_sons[weight];
}

int64_t ask_tree(int64_t weight) {
    if (weight < 0) {
        return 0;
    }
    if (tree[weight] > 0)
        return tree[weight];

    tree[weight] = 0;
    for (int i = 0; i < weights.size(); ++i) {
        tree[weight] += ask_two_sons(weight - weights[i]);
        tree[weight] %= MOD;
    }

    return tree[weight];
}

int main() {
    int n, m;
    cin >> n >> m;

    weights.resize(n, -1);
    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
    }

    tree.resize(m + 1, -1);
    two_sons.resize(m + 1, -1);

    tree[0] = 1;
    two_sons[0] = 1;

    for (int i = 1; i <= m; ++i) {
        cout << ask_tree(i) << ' ';
    }

    return 0;
}

/*
Tests:
input:
2 5
1 3
output:
1 2 6 18 57

input:
1 10
2
output:
0 1 0 2 0 5 0 14 0 42

input:
5 20
1 3 4 5 6
output:
1 2 6 19 62 210 733 2623 9569 35450 133011 504435 1930547 7446709 28921085 112997558 443841748 751624302 942171887 619156221

input:
2 12
2 4
output:
0 1 0 3 0 9 0 31 0 113 0 431

input:
2 6
1 2
output:
1 3 9 31 113 431

input:
1 10
1
output:
1 2 5 14 42 132 429 1430 4862 16796

input:
3 25
3 4 5
output:
0 0 1 1 1 2 4 6 9 17 30 49 86 155 271 476 854 1532 2738 4928 8919 16143 29274 53285 97183
*/