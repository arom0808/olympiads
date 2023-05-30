#include <iostream>
#include <optional>
#include <list>
#include <unordered_map>
#include <unordered_set>

struct Node;

struct Figure {
    std::uint32_t even_cnt = 0, uneven_cnt = 0;
    std::list<Node *> nodes;
};

struct Node {
    std::list<Node *> linked;
    Figure *figure;

    [[nodiscard]] bool IsEven() const {
        return linked.size() % 2 == 0;
    }
};

using Place = std::unordered_map<std::uint32_t, std::unordered_map<std::uint32_t, Node *>>;

std::optional<Node *> GetNodeByCords(std::uint32_t x, std::uint32_t y, const Place &place) {
    auto it_1 = place.find(x);
    if (it_1 == place.end()) return std::nullopt;
    auto it_2 = it_1->second.find(y);
    if (it_2 == it_1->second.end()) return std::nullopt;
    return {it_2->second};
}

void InsertNodeByCoords(std::uint32_t x, std::uint32_t y, Node *node, Place &place) {
    auto it_1 = place.find(x);
    if (it_1 == place.end()) {
        place.emplace(x, std::unordered_map<std::uint32_t, Node *>{{y, node}});
        return;
    }
    auto it_2 = it_1->second.find(y);
    if (it_2 == it_1->second.end()) it_1->second.emplace(y, node);
}

void fastscan(std::uint32_t &number) {
    int c;
    number = 0;
    c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        number = number * 10 + c - '0';
        c = getchar();
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    Place place;
    std::uint32_t n;
    fastscan(n);
//    std::cin >> n;
    std::unordered_set<Figure *> figures;
    for (std::uint32_t i = 0; i < n; ++i) {
        std::uint32_t x1, y1, x2, y2;
        fastscan(x1);
        fastscan(y1);
        fastscan(x2);
        fastscan(y2);
//        std::cin >> x1 >> y1 >> x2 >> y2;
        auto find_first_node = GetNodeByCords(x1, y1, place), find_second_node = GetNodeByCords(x2, y2, place);
        if ((!find_first_node.has_value()) && (!find_second_node.has_value())) {
            auto first_node = new Node(), second_node = new Node();
            auto this_figure = new Figure();
            first_node->linked.emplace_back(second_node);
            second_node->linked.emplace_back(first_node);
            first_node->figure = second_node->figure = this_figure;
            this_figure->uneven_cnt = 2;
            this_figure->nodes.emplace_back(first_node);
            this_figure->nodes.emplace_back(second_node);
            figures.insert(this_figure);
            InsertNodeByCoords(x1, y1, first_node, place);
            InsertNodeByCoords(x2, y2, second_node, place);
        } else if (find_first_node.has_value() && find_second_node.has_value()) {
            auto first_node = find_first_node.value(), second_node = find_second_node.value();
            auto this_figure = first_node->figure;
            if (first_node->figure != second_node->figure) {
                auto second_temp_figure = second_node->figure;
                for (auto cur_node: second_temp_figure->nodes) cur_node->figure = this_figure;
                this_figure->uneven_cnt += second_temp_figure->uneven_cnt;
                this_figure->even_cnt += second_temp_figure->even_cnt;
                this_figure->nodes.splice(this_figure->nodes.end(), second_temp_figure->nodes,
                                          second_temp_figure->nodes.begin(), second_temp_figure->nodes.end());
                figures.erase(second_temp_figure);
                delete second_temp_figure;
            }
            if (first_node->IsEven()) {
                this_figure->even_cnt -= 1;
                this_figure->uneven_cnt += 1;
            } else {
                this_figure->even_cnt += 1;
                this_figure->uneven_cnt -= 1;
            }
            if (second_node->IsEven()) {
                this_figure->even_cnt -= 1;
                this_figure->uneven_cnt += 1;
            } else {
                this_figure->even_cnt += 1;
                this_figure->uneven_cnt -= 1;
            }
            first_node->linked.emplace_back(second_node);
            second_node->linked.emplace_back(first_node);
        } else {
            auto first_node = find_first_node.value_or(nullptr), second_node = find_second_node.value_or(nullptr);
            if (first_node == nullptr) {
                std::swap(first_node, second_node);
                std::swap(x1, x2);
                std::swap(y1, y2);
            }
            auto this_figure = first_node->figure;
            second_node = new Node();
            second_node->figure = this_figure;
            this_figure->nodes.emplace_back(second_node);
            ++this_figure->uneven_cnt;
            if (first_node->IsEven()) {
                this_figure->even_cnt -= 1;
                this_figure->uneven_cnt += 1;
            } else {
                this_figure->even_cnt += 1;
                this_figure->uneven_cnt -= 1;
            }
            first_node->linked.emplace_back(second_node);
            second_node->linked.emplace_back(first_node);
            InsertNodeByCoords(x2, y2, second_node, place);
        }
        std::uint32_t cur_res = 0;
        for (const auto &fig: figures) if (fig->uneven_cnt <= 2) ++cur_res;
        std::cout << cur_res << "\n";
    }
    return 0;
}
