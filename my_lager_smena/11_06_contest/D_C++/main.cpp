#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <set>

struct IdAndLevel {
    std::uint32_t id;
    std::uint32_t level;

    explicit IdAndLevel(std::uint32_t id = 0, std::uint32_t level = 0) : id(id), level(level) {}
};

class SegmentsTree {
public:
    struct SegmentsNode {
        SegmentsNode *left = nullptr, *right = nullptr;
        std::int32_t max_level = 0, id_of_max_level = 0, to_add = 0;
    };

    SegmentsNode *root = nullptr;
    std::uint32_t size;

    explicit SegmentsTree(const std::vector<IdAndLevel> &ids_and_levels) : root(new SegmentsNode()),
                                                                           size(ids_and_levels.size()) {
        in_build(ids_and_levels, root, 0, size - 1);
    }

    IdAndLevel get_max_id_and_level(std::uint32_t req_left, std::uint32_t req_right) {
        return in_get_max_id_and_level(root, 0, size - 1, req_left, req_right);
    }

private:
    void in_build(const std::vector<IdAndLevel> &ids_and_levels, SegmentsNode *node, std::uint32_t left,
                  std::uint32_t right) {
        if (left == right) {
            node->max_level = static_cast<std::int32_t>(ids_and_levels[left].level);
            node->id_of_max_level = static_cast<std::int32_t>(ids_and_levels[left].id);
        } else {
            std::uint32_t middle = (left + right) / 2;
            node->left = new SegmentsNode();
            node->right = new SegmentsNode();
            in_build(ids_and_levels, node->left, left, middle);
            in_build(ids_and_levels, node->right, middle + 1, right);
            if (node->left->max_level > node->right->max_level) {
                node->max_level = node->left->max_level;
                node->id_of_max_level = node->left->id_of_max_level;
            } else {
                node->max_level = node->right->max_level;
                node->id_of_max_level = node->right->id_of_max_level;
            }
        }
    }

    void in_update(SegmentsNode *node, std::uint32_t left, std::uint32_t right, std::uint32_t req_left,
                   std::uint32_t req_right, std::int32_t add) {
        if (req_left > req_right) return;
        if (left == req_left && right == req_right) node->max_level += add;
        else {
            std::uint32_t middle = (left + right) / 2;
            in_update()
        }
    }

    IdAndLevel
    in_get_max_id_and_level(SegmentsNode *node, std::uint32_t left, std::uint32_t right, std::uint32_t req_left,
                            std::uint32_t req_right) {
        if (left == req_left && right == req_right) return IdAndLevel(node->id_of_max_level, node->max_level);
        std::uint32_t middle = (left + right) / 2;
        bool is_left_need = req_left <= std::min(req_right, middle),
                is_right_need = std::max(req_left, middle + 1) <= req_right;
        if (is_left_need && is_right_need) {
            IdAndLevel a = in_get_max_id_and_level(node->left, left, middle, req_left, std::min(req_right, middle)),
                    b = in_get_max_id_and_level(node->right, middle + 1, right, std::max(req_left, middle + 1),
                                                req_right);
            if (a.level > b.level) return a;
            else return b;
        } else if (is_left_need) {
            return in_get_max_id_and_level(node->left, left, middle, req_left, std::min(req_right, middle));
        } else {
            return in_get_max_id_and_level(node->right, middle + 1, right, std::max(req_left, middle + 1), req_right);
        }
    }
};

int main() {

}