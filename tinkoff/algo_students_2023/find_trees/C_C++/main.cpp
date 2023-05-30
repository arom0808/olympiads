#include <iostream>
#include <random>
#include <limits>

std::random_device dev;
std::uint32_t seed = dev();
std::mt19937 rng(seed);

std::uniform_int_distribution<std::int32_t> dist_priority(std::numeric_limits<std::int32_t>::min(),
                                                          std::numeric_limits<std::int32_t>::max());

enum class RequestType {
    add,
    find,
    del
};

struct Node {
    std::int32_t value, priority;
    Node *left = nullptr, *right = nullptr;
    std::uint32_t full_childs_count = 0;

    explicit Node(std::int32_t value = 0, std::int32_t priority = dist_priority(rng)) : value(value),
                                                                                        priority(priority) {}
};

Node *merge(Node *left, Node *right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;
    if (left->priority > right->priority) {
        left->full_childs_count += right->full_childs_count;
        left->right = merge(left->right, right);
        return left;
    }
    right->full_childs_count += left->full_childs_count;
    right->left = merge(left, right->left);
    return right;
}

std::uint32_t CountChilds(Node *node) {
    std::uint32_t result = 0;
    if (node->left != nullptr) result += node->left->full_childs_count + 1;
    if (node->right != nullptr) result += node->right->full_childs_count + 1;
    return result;
}

std::pair<Node *, Node *> split(Node *tree, std::int32_t value) {
    if (tree == nullptr) return {nullptr, nullptr};
    if (tree->value <= value) {
        auto sp = split(tree->right, value);
        tree->right = sp.first;
        tree->full_childs_count = CountChilds(tree);
        return {tree, sp.second};
    }
    auto sp = split(tree->left, value);
    tree->left = sp.second;
    tree->full_childs_count = CountChilds(tree);
    return {sp.first, tree};
}

bool is_exists(Node *tree, std::uint32_t value) {
    if (tree == nullptr) return false;
    if (tree->value == value) return true;
    if (tree->value < value) return is_exists(tree->right, value);
    return is_exists(tree->left, value);
}

void insert(Node *&tree, std::int32_t value) {
    if (is_exists(tree, value)) return;
    auto sp = split(tree, value);
    tree = merge(sp.first, merge(new Node(value), sp.second));
}

Node *erase(Node *tree, std::uint32_t value) {
    if (tree == nullptr) nullptr;
    if (tree->value == value) {
        auto a = tree->left, b = tree->right;
        delete tree;
        return merge(a, b);
    }
}
//
//void erase(Node *tree, std::uint32_t value) {
//
//    if (tree->value == value) {
//        auto temp = merge(tree->left, tree->right);
//        delete tree;
//        tree = temp;
//    } else erase(value < tree->value ? tree->left : tree->right, value);
//}



//void GoodSolution(const std::vector<std::pair<bool, std::uint32_t>> &requests, std::vector<std::int32_t> &ans) {
//    std::set<std::uint32_t> nums;
//    ans.clear();
//    ans.reserve(requests.size());
//    bool is_last_question = false;
//    for (const auto &req: requests) {
//        if (req.first) {
//            auto it = nums.lower_bound(req.second);
//            ans.push_back(it == nums.end() ? -1 : static_cast<std::int32_t>(*it));
//            is_last_question = true;
//        } else {
//            if (is_last_question) {
//                nums.insert(static_cast<std::int32_t>((req.second % mod_num + ans.back() % mod_num) % mod_num));
//            } else {
//                nums.insert(req.second);
//            }
//            is_last_question = false;
//        }
//    }
//}

void DeleteTree(Node *tree) {
    if (tree == nullptr) return;
    DeleteTree(tree->left);
    DeleteTree(tree->right);
    delete tree;
}

void MySolution(const std::vector<std::pair<RequestType, std::int32_t>> &requests, std::vector<std::int32_t> &ans) {
    Node *tree = nullptr;
    ans.clear();
    ans.reserve(requests.size());
    bool is_last_question = false;
    for (const auto &req: requests) {
        if (req.first) {
            ans.push_back(find_next(tree, req.second));
            is_last_question = true;
        } else {
            if (is_last_question)
                insert(tree, (req.second % mod_num + ans.back() % mod_num) % mod_num);
            else insert(tree, req.second);
            is_last_question = false;
        }
    }
    DeleteTree(tree);
}

//void Test() {
//    std::uniform_int_distribution<std::uint32_t> dist_n(2, 10), dist_req_value(0, 20);
//    std::bernoulli_distribution dist_req_type(0.2);
//    while (true) {
//        std::uint32_t n = dist_n(rng);
//        std::vector<std::pair<bool, std::uint32_t>> requests(n);
//        for (auto &&req: requests) {
//            req.first = dist_req_type(rng);
//            req.second = dist_req_value(rng);
//        }
//        std::vector<std::int32_t> good_ans, my_ans;
//        GoodSolution(requests, good_ans);
//        MySolution(requests, my_ans);
//        if (good_ans != my_ans) {
//            std::cout << "Inputs:\n";
//            for (const auto &req: requests)
//                std::cout << (req.first ? '?' : '+') << " " << req.second << std::endl;
//            std::cout << "\nor:\n{";
//            for (const auto &req: requests)
//                std::cout << "{" << (req.first ? "true" : "false") << ", " << req.second << "}, ";
//            std::cout << "}\n";
//            std::cout << "\nGood ans:\n";
//            for (const auto &ans: good_ans) std::cout << ans << std::endl;
//            std::cout << "\nMy ans:\n";
//            for (const auto &ans: my_ans) std::cout << ans << std::endl;
//            break;
//        }
//    }
//}

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::pair<RequestType, std::int32_t>> requests(n);
    std::string str_temp;
    for (auto &&req: requests) {
        std::cin >> str_temp >> req.second;
        if (str_temp == "+1" || str_temp == "1") req.first = RequestType::add;
        else if (str_temp == "0") req.first = RequestType::find;
        else req.first = RequestType::del;
    }
    std::vector<std::int32_t> answers;
    MySolution(requests, answers);
    for (const auto &ans: answers) std::cout << ans << "\n";
    return 0;
}