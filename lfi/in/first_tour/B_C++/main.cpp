#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <list>


class Node {
public:
    std::set<Node *> neighbours;
    bool visited = false;
    bool is_dried = false;
};

//struct Coord {
//    std::uint32_t c1, c2;
//
//    Coord(std::uint32_t c1, std::uint32_t c2) : c1(c1), c2(c2) {}
//
//    [[nodiscard]] Coord GetLeft() const {
//        return {c1, c2 > 0 ? c2 - 1 : c2};
//    }
//
//    [[nodiscard]] Coord GetLeftTop() const {
//        if (c1 % 2 == 0) return {c1 > 0 ? c1 - 1 : c1, c2 > 0 ? c2 - 1 : c2};
//        else return {c1 > 0 ? c1 - 1 : c1, c2};
//    }
//
//    [[nodiscard]] Coord GetRightTop() const {
//        if (c1 % 2 == 0) return {c1 > 0 ? c1 - 1 : c1, c2};
//        else return {c1 > 0 ? c1 - 1 : c1, c2 + 1 < v ? c2 + 1 : c2};
//    }
//
//    [[nodiscard]] Coord GetRight() const {
//        return {c1, c2 + 1 < v ? c2 + 1 : c2};
//    }
//
//    [[nodiscard]] Coord GetRightBottom() const {
//        if (c1 % 2 == 0) return {c1 + 1 < h ? c1 + 1 : c1, c2};
//        else return {c1 + 1 < h ? c1 + 1 : c1, c2 + 1 < v ? c2 + 1 : c2};
//    }
//
//    [[nodiscard]] Coord GetLeftBottom() const {
//        if (c1 % 2 == 0) return {c1 + 1 < h ? c1 + 1 : c1, c2 > 0 ? c2 - 1 : c2};
//        else return {c1 + 1 < h ? c1 + 1 : c1, c2};
//    }
//
//    [[nodiscard]] std::vector<Coord> GetNeighbours() const {
//        return std::vector<Coord>{GetLeft(), GetLeftTop(), GetRightTop(), GetRight(), GetRightBottom(),
//                                  GetLeftBottom()};
//    }
//};

std::uint32_t full_comp_size(Node *node) {
    if (node == nullptr) return 0;
    if (node->visited || node->is_dried) return 0;
    node->visited = true;
    std::uint32_t res = 1;
    for (const auto &neighbour: node->neighbours) {
        res += full_comp_size(neighbour);
    }
    return res;
}

int main() {
    std::uint32_t N, h, v;
    std::cin >> N >> h >> v;
    char temp_char;
    std::vector<std::vector<bool>> map(h, std::vector<bool>(v, false));
    for (auto &&row: map) {
        for (auto &&value: row) {
            std::cin >> temp_char;
            if (temp_char == '#') value = true;
        }
    }
    std::vector<std::vector<Node>> nodes(h, std::vector<Node>(v));
    for (std::uint32_t i = 0; i < h; ++i) {
        for (std::uint32_t j = 0; j < v; ++j) {
            if (map[i][j]) {
                nodes[i][j].is_dried = true;
                continue;
            }
            if (j > 0 && (!map[i][j - 1])) nodes[i][j].neighbours.insert(&nodes[i][j - 1]);
            if (j + 1 < v && (!map[i][j + 1])) nodes[i][j].neighbours.insert(&nodes[i][j + 1]);
            if (i % 2 == 0) {
                if (i > 0 && j > 0 && (!map[i - 1][j - 1])) nodes[i][j].neighbours.insert(&nodes[i - 1][j - 1]);
                if (i > 0 && (!map[i - 1][j])) nodes[i][j].neighbours.insert(&nodes[i - 1][j]);
                if (i + 1 < h && (!map[i + 1][j])) nodes[i][j].neighbours.insert(&nodes[i + 1][j]);
                if (i + 1 < h && j > 0 && (!map[i + 1][j - 1])) nodes[i][j].neighbours.insert(&nodes[i + 1][j - 1]);
            } else {
                if (i > 0 && (!map[i - 1][j])) nodes[i][j].neighbours.insert(&nodes[i - 1][j]);
                if (i > 0 && j + 1 < v && (!map[i - 1][j + 1])) nodes[i][j].neighbours.insert(&nodes[i - 1][j + 1]);
                if (i + 1 < h && j + 1 < v && (!map[i + 1][j + 1])) nodes[i][j].neighbours.insert(&nodes[i + 1][j + 1]);
                if (i + 1 < h && (!map[i + 1][j])) nodes[i][j].neighbours.insert(&nodes[i + 1][j]);
            }
        }
    }
    std::vector<std::uint32_t> comp_sizes;
    comp_sizes.reserve(h * v);
    for (std::uint32_t s_i = 0; s_i < h; ++s_i) {
        for (std::uint32_t s_j = 0; s_j < v; ++s_j) {
            if (map[s_i][s_j] || nodes[s_i][s_j].visited) continue;
            comp_sizes.push_back(full_comp_size(&nodes[s_i][s_j]));
        }
    }
    std::sort(comp_sizes.rbegin(), comp_sizes.rend());
    for (std::uint32_t i = 0; i < comp_sizes.size(); ++i) {
        if (comp_sizes[i] >= N) {
            std::cout << i + 1;
            return 0;
        }
        N -= comp_sizes[i];
    }
    return 0;
}
