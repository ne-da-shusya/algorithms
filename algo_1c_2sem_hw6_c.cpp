/*
Джон развозит пиццу в компании Кремниевой долины. Бизнес в Кремниевой долине идёт так быстро,
что к тому времени, как Джон выставляет счёт за пиццу компании А, может оказаться,
что компанию А поглотила компания B, и счёт нужно выставлять уже ей.
Джону это порядком надоело, и он просит вас написать программу, которая всегда сможет сказать,
какой компании выставлять счёт.

Формат ввода:
На вход вашей программе через пробел подаются два числа n и m (1 ≤ n, m ≤ 105),
где n – количество компаний, m – количество запросов к вашей программе.
Далее следуют m строк, каждая из которых представляет собой запрос одного из двух видов:
Символ "m", после которого через пробел идут два числа ai и bi
(где 1 ≤ ai, bi ≤ n) – этот запрос означает, компания с номером ai поглотила компанию
с номером bi (нумерация компаний начинается с 1). Гарантируется,
что до этого компании ai и bi никто не поглощал.
В ответ на этот запрос ничего выводить не требуется;
Символ "b", после которого через пробел идёт число ck.
В ответ на этот запрос выведите номер компании, частью которой является компания
с номером ck на текущий момент времени. Если компанию с номером ck никто не поглотил,
выведите ck как есть.

Формат вывода:
На каждый запрос типа "b" выведите с новой строки целое число, являющееся ответом.
*/

#include <algorithm>
#include <iostream>
#include <vector>

class Dsu {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    Dsu(int num) {
        for (int i = 0; i < num; ++i) {
            parent.push_back(i);
        }
    }

    bool check (int first, int second) {
        return find_root(first) == find_root(second);
    }

    void tie(int first, int second) {
        parent[find_root(first)] = find_root(second);
    }

    int find_root(int elem) {
        if (elem == parent[elem]) {
            return elem;
        }
        parent[elem] = find_root(parent[elem]);
        return parent[elem];
    }
};

struct Edge {
    int begin;
    int end;
    int weight;

    bool operator < (const Edge& other) const{
        return this->weight < other.weight;
    }
};

std::pair<int, int> kruskal(const std::vector<Edge>& edge, const int& num) {
    int counter = 0;
    int sum_weight = 0;
    Dsu dsu(num);

    for (size_t i = 0; i < edge.size(); ++i) {
        if (!dsu.check(edge[i].begin, edge[i].end)) {
            if (edge[i].weight != 0) {
                sum_weight += edge[i].weight;
                ++counter;
            }
            dsu.tie(edge[i].begin, edge[i].end);
        }
    }

    return {sum_weight, counter};
}

int main() {
    int n, m;

    std::cin >> n >> m;

    Dsu dsu(n);

    for (int i = 0; i < m; ++i) {
        char func;
        std::cin >> func;
        if (func == 'm') {
            int a, b;
            std::cin >> a >> b;
            dsu.tie(b - 1, a - 1);
        } else {
            int c;
            std::cin >> c;
            std::cout << dsu.find_root(c - 1) + 1 << '\n';
        }
    }
}