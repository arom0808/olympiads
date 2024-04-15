#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize(3)
#pragma GCC optimize("O3")
#pragma GCC optimize("inline")

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <map>
#include <filesystem>
#include <chrono>

using namespace std;
namespace fs = std::filesystem;

std::ostream &
operator<<(std::ostream &dest, __int128 value) {
    for (int i = 125; i >= 0; i -= 3) {
        dest << static_cast<int16_t>((value >> i) & 7);
    }
    dest << static_cast<int16_t>(value & 3);
    return dest;
}

istream &operator>>(istream &is, __int128 &f) {
    f = 0;
    char c;
    for (int i = 0; i < 126; i += 3) {
        is >> c;
        f <<= 1;
        if ((c - '0') & 4) f |= 1;
        f <<= 1;
        if ((c - '0') & 2) f |= 1;
        f <<= 1;
        if ((c - '0') & 1) f |= 1;
    }
    is >> c;
    f <<= 1;
    if ((c - '0') & 2) f |= 1;
    f <<= 1;
    if ((c - '0') & 1) f |= 1;
    return is;
};

//void ThreeColsProcess() {
//    ifstream if4("4out_sort.txt");
//    int n, temp;
//    if4 >> n;
//    vector<vector<pair<int, int>>> vs(n);
//    for (auto &v: vs) {
//        if4 >> temp;
//        v.resize(temp);
//        for (auto &[ost, sum]: v) if4 >> ost >> sum;
//    }
//    int max_sum = 0;
//    auto &v1 = vs[0], &v2 = vs[1], &v3 = vs[2];
//    for (auto [ost1, sum1]: v1) {
//        int i = v3.size() - 1;
//        for (auto [ost2, sum2]: v2) {
//            while (i >= 0 && ost1 + ost2 + v3[i].first > 0) --i;
//            if (i < 0) break;
//            if (ost1 + ost2 + v3[i].first == 0 && sum1 + sum2 + v3[i].second > max_sum) {
//                max_sum = sum1 + sum2 + v3[i].second;
//                cout << max_sum << "\n";
//                cout.flush();
//            }
//        }
//    }
//}

void write_out(int test_id, int out_id, const vector<map<int, __int128>> &maps) {
    string path = string("test") + to_string(test_id);
    fs::create_directory(path);
    ofstream of(path + "\\out" + to_string(out_id) + ".txt");
    of << maps.size() << "\n";
    for (const auto &a: maps) {
        of << a.size() << "\n";
        for (const auto &v: a)
            of << v.first << " " << v.second << "\n";
        of << "\n";
    }
    of.close();
}

int solve(int test_id, int n, const vector<int> &verhs, const vector<int> &cors) {
    vector<unordered_map<int, __int128>> maps1(n), maps2(n / 2 + n % 2);
    vector<map<int, __int128>> sort_maps1(n);
    for (uint32_t i = 0; i < n; ++i) {
        __int128 pos = static_cast<__int128>(1) << i;
        maps1[i].emplace(verhs[i] - cors[i], (static_cast<__int128>(cors[i]) << 96) | pos);
        auto it = maps1[i].find(0);
        if (it == maps1[i].end()) maps1[i].emplace(0, 0);
        else if ((it->second >> 96) < 0) it->second = 0;
    }
    for (int i = 0; i < n; ++i) sort_maps1[i].insert(maps1[i].begin(), maps1[i].end());
    write_out(test_id, 0, sort_maps1);
    int out_id = 0;
    for (; maps1.size() > 3;) {
        for (uint32_t i = 0; i < maps1.size(); i += 2) {
            if (i + 1 == maps1.size()) {
                maps2[i >> 1] = maps1[i];
                continue;
            }
            for (const auto &a: maps1[i]) {
                for (const auto &b: maps1[i + 1]) {
                    int ost = a.first + b.first;
                    __int128 sum_pos = (a.second >> 96) + (b.second >> 96);
                    sum_pos = (sum_pos << 96) | ((a.second << 32) >> 32) | ((b.second << 32) >> 32);
                    auto it = maps2[i >> 1].find(ost);
                    if (it == maps2[i >> 1].end()) maps2[i >> 1].emplace(ost, sum_pos);
                    else if ((it->second >> 96) < (sum_pos >> 96)) it->second = sum_pos;
                }
            }
        }
        swap(maps1, maps2);
        maps2.clear();
        maps2.resize(maps1.size() / 2 + maps1.size() % 2);
        sort_maps1.clear();
        sort_maps1.resize(maps1.size());
        for (int i = 0; i < maps1.size(); ++i) sort_maps1[i].insert(maps1[i].begin(), maps1[i].end());
        write_out(test_id, ++out_id, sort_maps1);
    }
    return out_id;
}

pair<int, vector<int>> get_ans(int test_id, int out_id) {
    ifstream inp(string("test") + to_string(test_id) + "\\out" + to_string(out_id) + ".txt");
    int nc, temp;
    __int128 temp128;
    inp >> nc;
    vector<vector<int>> osts(nc), sums(nc);
    vector<vector<__int128>> poss(nc);
    for (int i = 0; i < nc; ++i) {
        inp >> temp;
        osts[i].resize(temp), sums[i].resize(temp), poss[i].resize(temp);
        for (int j = 0; j < temp; ++j) {
            inp >> osts[i][j];
            inp >> temp128;
            sums[i][j] = temp128 >> 96;
            poss[i][j] = (temp128 << 32) >> 32;
//            if ((poss[i][j] >> 95) & 1) {
//                cout << i << " " << j << "\n";
//                cout << osts[i][j] << "\n";
//                cout << sums[i][j] << "\n";
//                cout << poss[i][j] << "\n";
//            }
        }
    }
//    return {0, vector<int>{0}};
    int max_sum = 0;
    __int128 max_pos = 0;
    if (nc == 3) {
        auto start_time = chrono::system_clock::now();
        for (int i = 0; i < osts[0].size(); ++i) {
            auto ost0 = osts[0][i], sum0 = sums[0][i];
            int k = osts[2].size() - 1;
            for (int j = 0; j < osts[1].size(); ++j) {
                auto ost1 = osts[1][j], sum1 = sums[1][j];
                while (k >= 0 && ost0 + ost1 + osts[2][k] > 0) --k;
                if (k < 0) break;
                if (ost0 + ost1 + osts[2][k] == 0 && sum0 + sum1 + sums[2][k] > max_sum) {
                    max_sum = sum0 + sum1 + sums[2][k];
                    max_pos = poss[0][i] | poss[1][j] | poss[2][k];
                }
            }
            if (chrono::duration_cast<chrono::seconds>(chrono::system_clock::now() - start_time).count() > 1800) {
                break;
            }
        }
    } else if (nc == 2) {
        int j = osts[1].size() - 1;
        for (int i = 0; i < osts[0].size(); ++i) {
            auto ost0 = osts[0][i], sum0 = sums[0][i];
            while (j >= 0 && ost0 + osts[1][j] > 0) --j;
            if (j < 0) break;
            if (ost0 + osts[1][j] == 0 && sum0 + sums[1][j] > max_sum) {
                max_sum = sum0 + sums[1][j];
                max_pos = poss[0][i] | poss[1][j];
            }
        }
    }
    vector<int> res_pos;
    for (int32_t i = 0; i < 96; ++i)
        if ((max_pos >> i) & 1)
            res_pos.push_back(i);
    return {max_sum, res_pos};
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
//    auto [sum, ids] = get_ans(0, 0);
//    cout << ids.size() << "\n";
//    for (auto id: ids) cout << id + 1 << " ";
//    cout << "\n";
//    cout.flush();
    int t;
    cin >> t;
    for (int32_t i = 0; i < t; ++i) {
        int n;
        cin >> n;
        vector<int> verhs(n), cors(n);
        for (auto &v: verhs) cin >> v;
        for (auto &v: cors) cin >> v;
        int out_id = solve(i, n, verhs, cors);
        auto [sum, ids] = get_ans(i, out_id);
        cout << ids.size() << "\n";
        for (auto id: ids) cout << id + 1 << " ";
        cout << "\n";
        cout.flush();
    }
    return 0;
}

//    ifstream if4("4out.txt");
//    int n;
//    if4 >> n;
//    vector<map<int, int>> mps(n);
//    for (auto &mp: mps) {
//        int sz;
//        if4 >> sz;
//        for (int i = 0, ost, sum; i < sz; ++i) {
//            if4 >> ost >> sum;
//            mp.emplace(ost, sum);
//        }
//    }
////    vector<map<int, int>> res_mps(n);
////    for (int32_t i = 0; i < n; ++i) {
////        int j = 0;
////        for (auto it = mps[i].rbegin(); it != mps[i].rend() && j < 20000; ++it, ++j)
////            res_mps[i].emplace(it->second, it->first);
////    }
//    ofstream of4("4out_sort.txt");
//    of4 << n << "\n";
//    for (auto &rmp: mps) {
//        of4 << rmp.size() << "\n";
//        for (auto [ost, sum]: rmp) {
//            of4 << ost << " " << sum << "\n";
//        }
//    }
//
////    ifstream if4c("4out_cut.txt");
//
//
////    freopen("input.txt", "r", stdin);
////    freopen("output.txt", "w", stdout);
////    int n;
////    cin >> n;
////    vector<int> verhs(n), cors(n);
////    for (auto &v: verhs) cin >> v;
////    for (auto &v: cors) cin >> v;
////    vector<map<int, int>> maps1(n), maps2(n / 2 + n % 2);
////    for (uint32_t i = 0; i < n; ++i) {
////        maps1[i].emplace(verhs[i] - cors[i], cors[i]);
////        auto it = maps1[i].find(0);
////        if (it == maps1[i].end()) maps1[i].emplace(0, 0);
////        else if (it->second < 0) it->second = 0;
////    }
////    for (uint32_t _ = 0; maps1.size() > 1; ++_) {
////        for (uint32_t i = 0; i < maps1.size(); i += 2) {
////            if (i + 1 == maps1.size()) {
////                maps2[i >> 1] = maps1[i];
////                continue;
////            }
////            for (const auto &a: maps1[i]) {
////                for (const auto &b: maps1[i + 1]) {
////                    auto it = maps2[i >> 1].find(a.first + b.first);
////                    if (it == maps2[i >> 1].end()) maps2[i >> 1].emplace(a.first + b.first, a.second + b.second);
////                    else if (it->second < a.second + b.second) it->second = a.second + b.second;
////                }
////            }
////            multimap<int, int> ost_by_sum;
////            for (auto [ost, sum]: maps2[i >> 1]) ost_by_sum.emplace(sum, ost);
////            maps2[i >> 1].clear();
////            int j = 0;
////            for (auto it = ost_by_sum.begin(); it != ost_by_sum.end() && j < 10000; ++it, ++j)
////                maps2[i >> 1].emplace(it->second, it->first);
////        }
////        swap(maps1, maps2);
////        maps2.clear();
////        maps2.resize(maps1.size() / 2 + maps1.size() % 2);
////        ofstream of(to_string(_) + "out.txt");
////        of << maps1.size() << "\n";
////        for (const auto &a: maps1) {
////            of << a.size() << "\n";
////            for (const auto &v: a) of << v.first << " " << v.second << "\n";
////            of << "\n";
////        }
////        of.close();
////    }
//
//
//
//
//
////    int s1 = n / 10 + (n % 10 != 0);
////    vector<unordered_map<int, int>> maps(s1);
////    for (uint32_t i = 0; i * 10 < n; ++i) {
////        for (uint32_t mask = 0; mask < (1 << 10); ++mask) {
////            int sum1 = 0, sum2 = 0;
////            for (uint32_t j = 0; j < 10; ++j)
////                if ((mask >> j) & 1)
////                    sum1 += verhs[i * 10 + j], sum2 += cors[i * 10 + j];
////            auto it = maps[i].find(sum2 - sum1);
////            if (it == maps[i].end()) maps[i].emplace(sum2 - sum1, sum1);
////            else if (it->second < sum1) it->second = sum1;
////        }
////    }
////    int s2 = maps.size() / 2 + maps.size() % 2;
////    vector<unordered_map<int, int>> maps2(s2);
////    for (uint32_t i = 0; i < s1; i += 2) {
////        for (const auto &a: maps[i]) {
////            for (const auto &b: maps[i + 1]) {
////                auto it = maps2[i / 2].find(a.first + b.first);
////                if (it == maps2[i / 2].end()) maps2[i / 2].emplace(a.first + b.first, a.second + b.second);
////                else if (it->second < a.second + b.second) it->second = a.second + b.second;
////            }
////        }
////        cout << maps2[i / 2].size() << endl;
////    }
////    cout << endl;
////    int s3 = maps2.size() / 2 + maps2.size() % 2;
////    vector<unordered_map<int, int>> maps3(s3);
////    for (uint32_t i = 0; i < s2; i += 2) {
////        if (i + 1 == s2) {
////            maps3[i / 2] = maps2[i];
////            continue;
////        }
////        for (const auto &a: maps2[i]) {
////            for (const auto &b: maps2[i + 1]) {
////                auto it = maps3[i / 2].find(a.first + b.first);
////                if (it == maps3[i / 2].end()) maps3[i / 2].emplace(a.first + b.first, a.second + b.second);
////                else if (it->second < a.second + b.second) it->second = a.second + b.second;
////            }
////        }
////        cout << maps3[i / 2].size() << endl;
////    }
////    for (const auto &m: maps3) cout << m.size() << "\n";