#include <iostream>
#include <set>
#include <random>

using namespace std;

random_device dev;
mt19937 rng(dev());
const string alphabet = "0123456789abcdef";

void gen_strs(int32_t id, int32_t k, string &str, set<string> &strs) {
    if (id == k) {
        strs.insert(str);
        return;
    }
    for (auto c: alphabet) {
        str[id] = c;
        gen_strs(id + 1, k, str, strs);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int32_t n, k;
    cin >> n >> k;
    uint32_t max_val = 1;
    for (uint32_t i = 0; i < k; ++i) max_val *= 16;
    vector<bool> nums(max_val, false);
    uniform_int_distribution rand_pass(0u, max_val - 1);
    uint32_t now_size = 0;
    while (now_size < n) {
        uint32_t new_num = rand_pass(rng);
        bool ok = true;
        for (uint32_t i = 0; i < k && ok; ++i)
            for (uint32_t c = 0; c < 16 && ok; ++c)
                if (nums[(new_num & (~(((1 << 4) - 1) << (4 * i)))) | (c << (4 * i))])
                    ok = false;
        if (ok) nums[new_num] = true, ++now_size;
    }
    for (uint32_t i = 0; i < max_val; ++i) {
        if (!nums[i]) continue;
        for (uint32_t j = 0; j < k; ++j) {
            auto c = (i >> (j * 4)) & ((1 << 4) - 1);
            if (c < 10) cout << static_cast<char>('0' + c);
            else cout << static_cast<char>('a' + (c - 10));
        }
        cout << '\n';
    }
//    set<string> strs;
//    string str(k, '0');
//    gen_strs(0, k, str, strs);
//    bool deleted = true;
//    string temp_str;
//    while (deleted) {
//        deleted = false;
//        for (auto it = strs.begin(); it != strs.end() && !deleted; ++it) {
//            temp_str = *it;
//            for (int32_t i = 0; i < k && !deleted; ++i) {
//                char sc = temp_str[i];
//                for (auto c: alphabet) {
//                    if (sc == c) continue;
//                    temp_str[i] = c;
//                    auto it2 = strs.find(temp_str);
//                    if (it2 != strs.end()) {
//                        strs.erase(it2);
//                        deleted = true;
//                    }
//                }
//                temp_str[i] = sc;
//            }
//        }
//    }
//    for (const auto &s: strs) {
//        cout << s << "\n";
//    }
    return 0;
}
