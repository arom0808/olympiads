#include <iostream>

class Node {
public:
    Node *parent = nullptr;
    Node *childs[3] = {nullptr, nullptr, nullptr};
    std::uint32_t keys[2] = {0, 0};
    std::uint32_t child_count = 0, key_count = 0;
    std::uint32_t max = 0;

    explicit Node(std::uint32_t key) {
        keys[0] = key;
        key_count = 1;
    }

    Node(const Node &other) : parent(other.parent), child_count(other.child_count), key_count(other.key_count),
                              max(other.max) {
        for (std::uint32_t i = 0; i < 3; ++i) childs[i] = other.childs[i];
        for (std::uint32_t i = 0; i < 2; ++i) keys[i] = other.keys[i];
    }
};

class Tree {
private:
    Node *InSearch(Node *it, std::uint32_t num) {

    }

//    Node *SeparateAndAddValue(Node *it, std::uint32_t num) {
//        Node* left
//    }
//
//    Node *InAddNewValue(Node *it, std::uint32_t num) {
//        if (it->child_count == 0) {
//            if (it->key_count == 2) return SeparateAndAddValue(it, num);
//            else {
//                if (it->key_count == 0) it->key_1 = num;
//                else it->key_2 = num;
//                ++it->key_count;
//                return it;
//            }
//        }
//        if (num < it->key_1) return InAddNewValue(it->left, num);
//        if (it->key_count == 1) return InAddNewValue(it->right, num);
//        if (num < it->key_2) return InAddNewValue(it->middle, num);
//        return InAddNewValue(it->right, num);
//    }

public:
    Node *root = nullptr;

    Node *Search(std::uint32_t num) {
        if (root == nullptr) return nullptr;
        Node *it = root;
        while (it->child_count > 0) {
            if (it->child_count == 2) {
                if (it->keys[0] < num) it = it->childs[1];
                else it = it->childs[0];
            } else if (it->keys[1] < num) it = it->childs[2];
            else if (it->keys[0] < num) it = it->childs[1];
            else it = it->childs[0];
        }
        return it;
    }

    Node *AddNewValue(std::uint32_t num) {
        if (root == nullptr) {
            root = new Node(num);
            return root;
        }
        Node *pos = Search(num);
        if (pos->parent == nullptr) {
            Node *new_child_1 = new Node(*root), *new_child_2 = new Node(num);
            Node *&min_child = (new_child_1->keys[0] < new_child_2->keys[0] ? new_child_1 : new_child_2),
                    *&max_child = (min_child == new_child_1 ? new_child_2 : new_child_1);
            root->childs[0] = min_child;
            root->childs[1] = max_child;
            root->child_count = 2;
            root->key_count = 1;
            root->keys[0] = min_child->keys[0];
            new_child_1->parent = root;
            new_child_2->parent = root;
        } else {
            Node *par = pos->parent;
            par.
        }
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
