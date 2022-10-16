#include <iostream>
#include <vector>
#include <map>

class SpecificationNode {
public:
    std::int32_t finish_weight;
    char letter;
    SpecificationNode *parent = nullptr;
    std::map<char, SpecificationNode *> childs;

    SpecificationNode(char letter = '1', std::int32_t finish_weight = -1, SpecificationNode *parent = nullptr) :
            letter(letter), finish_weight(finish_weight), parent(parent) {}

    void AddLetterToChild(std::string::const_iterator str_begin, std::string::const_iterator str_end,
                          std::int32_t f_finish_weight) {
        if (str_begin == str_end) return;
        char cur_char = *str_begin;
        auto child_cur_char_it = childs.find(cur_char);
        bool is_next_finish = std::next(str_begin) == str_end;
        if (child_cur_char_it != childs.end()) {
            if (is_next_finish) child_cur_char_it->second->finish_weight = f_finish_weight;
            else child_cur_char_it->second->AddLetterToChild(std::next(str_begin), str_end, f_finish_weight);
        }
        auto *cur_child = new SpecificationNode(cur_char, f_finish_weight, this);
        if (!is_next_finish) cur_child->AddLetterToChild(std::next(str_begin), str_end, f_finish_weight);
        childs.emplace(cur_char, cur_child);
    }

    bool IsRoot() const { return this->parent == nullptr; }
};

class SpecificationBor {
public:
    SpecificationNode *root;

    explicit SpecificationBor(const std::vector<std::string> &string_arr) {
        root = new SpecificationNode();
        for (const auto &string: string_arr)
            root->AddLetterToChild(string.begin(), string.end());
    }
};

int main() {
    std::uint32_t nodes_count, specs_count;
    bool is_launch_list_required;
    std::cin >> nodes_count >> specs_count >> is_launch_list_required;
    std::vector<std::vector<char>> raw_nodes_graph(nodes_count, std::vector<char>(nodes_count));
    char tmp_c;
    std::uint32_t tmp_p;
    for (std::uint32_t i = 1; i < nodes_count; ++i) {
        std::cin >> tmp_p >> tmp_c;
        raw_nodes_graph[tmp_p][i] = tmp_c;
    }
    std::vector<std::string> specs(specs_count);
    for (auto &&spec: specs) std::cin >> spec;
    SpecificationBor spec_bor(specs);
    return 0;
}
