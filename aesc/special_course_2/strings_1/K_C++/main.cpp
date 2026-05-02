#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <list>

using namespace std;

int32_t eq_pref(const string &a, const string &b) {
    int32_t i = 0, n = min<int32_t>(a.size(), b.size());
    for (; i < n; ++i) if (a[i] != b[i]) break;
    return i;
}

int main() {
    freopen("printer.in", "r", stdin), freopen("printer.out", "w", stdout);
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n;
    cin >> n;
    vector<string> vec_strs(n);
    for (auto &s: vec_strs) cin >> s;
//    sort(vec_strs.begin(), vec_strs.end(), [](const string &a, const string &b) {
//        if (a.size() != b.size()) return a.size() < b.size();
//        return a < b;
//    });
    string best_res;
    string res;
    res.reserve(5e5);
    for (int32_t _ = 0; _ < n; ++_) {
        res.clear();
        list<string> strs(vec_strs.begin(), vec_strs.end());
        string now_word = vec_strs[_];
        strs.erase(next(strs.begin(), _));
        for (auto c: now_word) res += c, res += "\n";
        res += "P\n";
        while (!strs.empty()) {
            auto best_it = strs.begin();
            int32_t best_eq = eq_pref(now_word, *best_it);
            for (auto it = strs.begin(); it != strs.end(); ++it) {
                int32_t tr = eq_pref(now_word, *it);
                if (tr > best_eq || (tr == best_eq && it->size() < best_it->size()) ||
                    (tr == best_eq && it->size() == best_it->size() && (*it) > (*best_it))) {
                    best_eq = tr;
                    best_it = it;
                }
            }
            for (int32_t i = best_eq, sz = now_word.size(); i < sz; ++i) {
                now_word.pop_back();
                res += "-\n";
            }
            for (int32_t i = best_eq; i < best_it->size(); ++i) {
                now_word += best_it->at(i);
                res += best_it->at(i);
                res += "\n";
            }
            strs.erase(best_it);
            res += "P\n";
        }
        if (best_res.empty() || res.size() < best_res.size()) best_res = res;
    }
    cout << best_res.size() / 2 << "\n" << best_res;
    return 0;
}

//    for (const auto &s: vec_strs) {
//        while (now_word != s) {
//            if (now_word.size() > s.size()) {
//                res += "-\n";
//                now_word.pop_back();
//            } else if (s.substr(0, now_word.size()) == now_word) {
//                if (now_word.size() < s.size()) {
//                    res += s[now_word.size()];
//                    res += "\n";
//                    now_word += s[now_word.size()];
//                }
//            } else {
//                res += "-\n";
//                now_word.pop_back();
//            }
//        }
//        res += "P\n";
//    }