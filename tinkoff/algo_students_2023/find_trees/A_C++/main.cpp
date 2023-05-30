#include <iostream>
#include <random>
#include <limits>

std::random_device dev;
std::uint32_t seed = dev();
std::mt19937 rng(seed);

std::uniform_int_distribution<std::uint32_t> dist_priority(std::numeric_limits<std::uint32_t>::min(),
                                                           std::numeric_limits<std::uint32_t>::max());

std::uint32_t mod_num = 1000000000;


struct Node {
    std::uint32_t value, priority;
    Node *left = nullptr, *right = nullptr;

    explicit Node(std::uint32_t value = 0, std::uint32_t priority = 0) : value(value), priority(priority) {}
};

void split(Node *tree, std::uint32_t value, Node *&left, Node *&right) {
    if (tree == nullptr) left = right = nullptr;
    else if (value < tree->value) {
        split(tree->left, value, left, tree->left);
        right = tree;
    } else {
        split(tree->right, value, tree->right, right);
        left = tree;
    }
}

Node *merge(Node *left, Node *right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    }
    right->left = merge(left, right->left);
    return right;
}

void in_insert(Node *&tree, Node *item) {
    if (tree == nullptr) tree = item;
    else if (item->priority > tree->priority) {
        split(tree, item->value, item->left, item->right);
        tree = item;
    } else {
        if (item->value < tree->value) in_insert(tree->left, item);
        else in_insert(tree->right, item);
    }
}

std::int32_t find_next(Node *tree, std::uint32_t i) {
    if (tree == nullptr) return -1;
    if (i > tree->value) return find_next(tree->right, i);
    std::int32_t temp_res = -1;
    if (tree->left != nullptr) temp_res = find_next(tree->left, i);
    if (temp_res != -1) return static_cast<std::int32_t>(tree->value > temp_res ? temp_res : tree->value);
    return static_cast<std::int32_t>(tree->value);
}

void insert(Node *&tree, std::uint32_t value) {
    if (find_next(tree, value) == value) return;
    Node *temp_node = new Node(value, dist_priority(rng));
    in_insert(tree, temp_node);
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

void MySolution(const std::vector<std::pair<bool, std::uint32_t>> &requests, std::vector<std::int32_t> &ans) {
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
    std::vector<std::pair<bool, std::uint32_t>> requests(n);
    char cmd;
    std::uint32_t temp_num;
    for (auto &&req: requests) {
        std::cin >> cmd >> temp_num;
        req.first = (cmd == '?');
        req.second = temp_num;
    }
    std::vector<std::int32_t> ans;
    MySolution(requests, ans);
    for (const auto &a: ans) std::cout << a << "\n";
    return 0;
}
