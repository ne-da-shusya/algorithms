/*
В городе M строятся N новых микрорайонов, между которыми
запланировано M магистральных дорог. Каждая дорога имеет
свою стоимость строительства Pij. В прошлом году из этих M дорог
муниципалитет успел построить K штук. К сожалению, в этом году
финансирование строительства решено было сократить, и теперь
из запланированных, но непостроенных M-K дорог нужно оставить такие,
чтобы из любого микрорайона в любой другой существовал хотя бы один путь,
но при этом стоимость их строительства была минимальной (гарантируется,
что такой набор существует).
Какова минимальная стоимость P завершения строительства дорожной сети
по новому плану, и сколько новых дорог по нему предстоит построить?

Формат ввода:
Первая строка содержит через пробел два числа:
N (2 ≤ N ≤ 105) - число строящихся микрорайонов,
M (1 ≤ M ≤ min(N(N-1)/2, 106)) - число запланированных дорог.
Следующие M строк описывают запланированные дороги, отсортированные по паре
номеров своих концов, и каждая содержит через пробел три целых числа:
i (1 ≤ i < N) - номер микрорайона, в котором дорога начинается,
j (i < j ≤ N) - номер микрорайона, в котором дорога заканчивается,
Pij (0 ≤ Pij ≤ 103) - стоимость строительства дороги. 0, если дорога уже построена.

Формат вывода:
Вывод должен содержать два числа через пробел: минимальную стоимость P завершения
строительства дорожной сети по новому плану и L - число дорог, которые предстоит
по нему построить.
*/

#include <algorithm>
#include <iostream>
#include <vector>

class Dsu {
private:
    std::vector<int> parent;
    std::vector<int> rank;

    int find_root(int elem) {
        if (elem == parent[elem]) {
            return elem;
        }
        parent[elem] = find_root(parent[elem]);
        return parent[elem];
    }

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
    std::vector<Edge> edge;

    std::cin >> n >> m; 

    for (int i = 0; i < m; ++i) {
        Edge elem;
        std::cin >> elem.begin >> elem.end >> elem.weight;
        --elem.begin, --elem.end;
        edge.push_back(elem);
    }

    std::sort(edge.begin(), edge.end());

    auto res = kruskal(edge, n);
    std::cout << res.first << ' ' << res.second << '\n';
}