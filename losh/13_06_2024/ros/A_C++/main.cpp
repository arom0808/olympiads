#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <list>

using namespace std;

//template<typename T>
//class SegmentTree {
//public:
//    struct Node {
//        T max_val;
//    };
//
//    int64_t size;
//    vector<Node> tree;
//
//    void _set(int64_t id, int64_t l, int64_t r, int64_t pos, T val) {
//        if (l >= r || pos < l || pos >= r) return;
//        if (r - l == 1) tree[id].max_val = val;
//        else {
//            _set(id * 2, l, (l + r) / 2, pos, val);
//            _set(id * 2 + 1, (l + r) / 2, r, pos, val);
//            tree[id].max_val = max(tree[id * 2].max_val, tree[id * 2 + 1].max_val);
//        }
//    }
//
//    T _get(int64_t id, int64_t l, int64_t r, int64_t pos) {
//        if (l >= r || pos < l || pos >= r) return 0;
//        if (r - l == 1) return tree[id].max_val;
//        return max(_get(id * 2, l, (l + r) / 2, pos), _get(id * 2 + 1, (l + r) / 2, r, pos));
//    }
//
//    int64_t _get_leftest_ge(int64_t id, int64_t l, int64_t r, T val) {
//        if (tree[id].max_val < val) return -1;
//        if (r - l == 1) return l;
//        auto res = _get_leftest_ge(id * 2, l, (l + r) / 2, val);
//        if (res == -1) res = _get_leftest_ge(id * 2 + 1, (l + r) / 2, r, val);
//        return res;
//    }
//
//    explicit SegmentTree(int64_t size) : size(size), tree(size * 4) {}
//
//    void set(int64_t pos, T val) {
//        _set(1, 0, size, pos, val);
//    }
//
//    T get(int64_t pos) {
//        return _get(1, 0, size, pos);
//    }
//
//    int64_t get_leftest_ge(T val) {
//        return _get_leftest_ge(1, 0, size, val);
//    }
//};
//
//template<typename T>
//class StupidSegmentTree {
//public:
//    vector<T> nums;
//
//    explicit StupidSegmentTree(int64_t size) : nums(size) {}
//
//    void set(int64_t pos, T val) {
//        nums[pos] = val;
//    }
//
//    T get(int64_t pos) {
//        return nums[pos];
//    }
//
//    int64_t get_leftest_ge(T val) {
//        for (int64_t i = 0; i < static_cast<int64_t>(nums.size()); ++i) if (nums[i] >= val) return i;
//        return -1;
//    }
//};

pair<string, int64_t> get_first_var_name(const string &str) {
    string r1;
    int64_t r2 = 0;
    r1 = str.substr(0, 4);
    int64_t i = 12;
    for (; i < static_cast<int64_t>(str.size()) && str[i] >= '0' && str[i] <= '9'; ++i) r2 = r2 * 10 + (str[i] - '0');
    return {r1, r2};
}

pair<bool, string> get_second_var_name(const string &str) {
    bool r1 = false;
    string r2;
    if (str.substr(0, 5) == "print") r1 = true;
    if (!r1) r2 = str.substr(5, 4);
    else r2 = str.substr(6, 4);
    return {r1, r2};
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    list<pair<int32_t, int32_t>> busy;
    busy.emplace_back(0, 1), busy.emplace_back(100001, 100002);
    map<string, list<pair<int32_t, int32_t>>::iterator> vars;
    int64_t n;
    cin >> n;
    string temp;
    for (int64_t _ = 0; _ < n; ++_) {
        cin >> temp;
        auto eq_s_pos = temp.find('=');
        if (eq_s_pos != string::npos) {
            auto [var_name, var_size] = get_first_var_name(temp);
            auto it = busy.begin();
            bool found = false;
            for (; next(it) != busy.end(); ++it) {
                if (next(it)->first - it->second >= var_size) {
                    found = true;
                    break;
                }
            }
            if (!found) it = busy.begin();
            else it = busy.emplace(next(it), it->second, it->second + var_size);
            auto vit = vars.emplace(var_name, it);
            if (!vit.second) vit.first->second = it;
        } else {
            auto [type, var_name] = get_second_var_name(temp);
            if (type) {
                auto it = vars.find(var_name);
                if (it == vars.end()) cout << "0\n";
                else cout << it->second->first << "\n";
            } else {
                auto vit = vars.find(var_name);
                if (vit != vars.end() && vit->second != busy.begin()) {
                    busy.erase(vit->second);
                    vit->second = busy.begin();
                }
            }
        }
    }
    return 0;
}
