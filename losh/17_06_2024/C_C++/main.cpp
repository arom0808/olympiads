#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")

#include <iostream>

using namespace std;

const int32_t inf = 1e9;
const int32_t maxn = 400;
const int32_t maxs = 1501;
int32_t n, s;
int32_t nums[maxn];
int32_t pf[maxn];
int32_t _dp1[maxs][maxs], _dp2[maxs][maxs];
int32_t _used1[maxs][maxs], _used2[maxs][maxs];

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n, s = 0;
    for (int32_t i = 0; i < n; ++i) cin >> nums[i], s += nums[i], pf[i + 1] = pf[i] + nums[i];
    auto dp1 = &_dp1, dp2 = &_dp2, used1 = &_used1, used2 = &_used2;
    for (int32_t i = 0; i <= s; ++i) for (int32_t j = 0; j <= s; ++j) (*dp1)[i][j] = inf;
    for (int32_t i = 0; i <= s; ++i) for (int32_t j = 0; j <= s; ++j) (*dp2)[i][j] = inf;
    for (int32_t i = 0; i <= s; ++i) for (int32_t j = 0; j <= s; ++j) (*used1)[i][j] = 0;
    for (int32_t i = 0; i <= s; ++i) for (int32_t j = 0; j <= s; ++j) (*used2)[i][j] = 0;
    for (int32_t i = 0; i <= s; ++i) (*dp1)[i][i] = std::abs(i - pf[1]), (*used1)[i][i] = 2;
    for (int32_t i = 2; i <= n; ++i) {
        for (int32_t pmx = 0; pmx <= s; ++pmx) {
            for (int32_t x = 0; pmx + x <= s; ++x) {
                int32_t vs = ((*used1)[pmx][x] == i) ? (*dp1)[pmx][x] : inf;
                if (x > 0 && (*used1)[pmx][x - 1] == i && (*dp1)[pmx][x - 1] < vs) vs = (*dp1)[pmx][x - 1];
                if (x < s && (*used1)[pmx][x + 1] == i && (*dp1)[pmx][x + 1] < vs) vs = (*dp1)[pmx][x + 1];
                if (vs < inf) {
                    (*dp2)[pmx + x][x] = vs + std::abs(pf[i] - pmx - x);
                    (*used2)[pmx + x][x] = i + 1;
                }
            }
        }
        swap(dp1, dp2);
        swap(used1, used2);
//        for (int32_t j = 0; j <= s; ++j) for (int32_t k = 0; k <= j; ++k) (*dp2)[j][k] = inf;
    }
    int32_t mr = inf;
//    for (int32_t i = 0; i <= s; ++i) if ((*used1)[s][i] >= s && (*dp1)[s][i] < mr) mr = (*dp1)[s][i];
    for (int32_t i = 0; i <= s; ++i) if ((*used1)[s][i] == n + 1 && (*dp1)[s][i] < mr) mr = (*dp1)[s][i];
//    for (int32_t i = 0; i <= s; ++i) cout << (*used1)[s][i] << " " << (*dp1)[s][i] <<" "<< ((*used1)[s][i] >= s) << "\n";
    cout << mr;
    return 0;
}

//#include <iostream>
//#include <vector>
//#include <list>
//
//using namespace std;
//
//const int32_t maxn = 400;
//int32_t n, s;
//int32_t nums[maxn];
//list<pair<int32_t, int32_t>> where_get;
//int32_t now_res = 0, now_sum = 0;
//int32_t best_res = -1;
//vector<pair<int32_t, int32_t>> gots[maxn];
//int32_t amount_to_next[maxn];
//
//void rec_sol(int32_t layer) {
//    if (best_res != -1 && now_res > best_res) return;
//    if (layer >= n - 1) {
//        now_sum += nums[layer];
//        if (s - now_sum == 0 && std::abs(nums[layer] - nums[layer - 1]) <= 1 &&
//            (best_res == -1 || now_res < best_res))
//            best_res = now_res;
//        now_sum -= nums[layer];
//        return;
//    }
//    int32_t min_s = (2 * nums[layer - 1] + layer - n - 1) * (n - layer) / 2;
//    int32_t max_s = (2 * nums[layer - 1] + n - layer + 1) * (n - layer) / 2;
//    if (s - now_sum < min_s || s - now_sum > max_s) return;
//    if (!where_get.empty() && where_get.front().first == layer) where_get.pop_front();
//    for (int32_t val = nums[layer - 1] - 1; val <= nums[layer - 1] + 1; ++val) {
//        if (val < 0 || now_sum + val > s) continue;
//        gots[layer].clear();
//        if (nums[layer] >= val) {
//            if (layer + 1 >= n) continue;
//            amount_to_next[layer] = nums[layer] - val;
//            nums[layer + 1] += amount_to_next[layer];
//            now_res += amount_to_next[layer];
//            nums[layer] = val;
//        } else {
//            if (s - now_sum - val < 0) continue;
//            amount_to_next[layer] = 0;
//            while (nums[layer] < val) {
//                auto it = where_get.begin();
//                if (nums[layer] + it->second <= val) {
//                    nums[layer] += it->second;
//                    gots[layer].push_back(*it);
//                    now_res += it->second * (it->first - layer);
//                    where_get.pop_front();
//                } else {
//                    gots[layer].emplace_back(it->first, val - nums[layer]);
//                    now_res += (val - nums[layer]) * (it->first - layer);
//                    it->second -= val - nums[layer];
//                    nums[layer] = val;
//                }
//            }
//        }
//        now_sum += val;
//        rec_sol(layer + 1);
//        if (amount_to_next[layer] != 0) {
//            nums[layer] += amount_to_next[layer];
//            now_res -= amount_to_next[layer];
//            nums[layer + 1] -= amount_to_next[layer];
//            amount_to_next[layer] = 0;
//        } else if (!gots[layer].empty()) {
//            for (int32_t i = gots[layer].size() - 1; i >= 0; --i) {
//                auto g = gots[layer][i];
//                if (!where_get.empty() && g.first == where_get.front().first) {
//                    nums[layer] -= g.second;
//                    where_get.front().second += g.second;
//                    now_res -= g.second * (g.first - layer);
//                } else {
//                    where_get.push_front(g);
//                    now_res -= g.second * (g.first - layer);
//                    nums[layer] -= g.second;
//                }
//            }
//        }
//        now_sum -= val;
//    }
//}
//
//int main() {
//    cin >> n, s = 0;
//    for (int32_t i = 0; i < n; ++i) {
//        cin >> nums[i], s += nums[i];
//        if (i != 0 && nums[i] != 0) where_get.emplace_back(i, nums[i]);
//    }
//    int32_t orig_0_num = nums[0];
//    nums[1] += nums[0];
//    now_res += nums[0];
//    nums[0] = 0;
//    for (int32_t f_num = 0; f_num < orig_0_num; ++f_num) {
//        now_sum = nums[0];
//        rec_sol(1);
//        --nums[1];
//        --now_res;
//        ++nums[0];
//    }
//    now_sum = nums[0];
//    rec_sol(1);
//    for (int32_t f_num = orig_0_num + 1; f_num <= s; ++f_num) {
//        ++nums[0];
//        --nums[where_get.front().first];
//        --where_get.front().second;
//        now_res += where_get.front().first;
//        if (where_get.front().second == 0) where_get.pop_front();
//        now_sum = nums[0];
//        rec_sol(1);
//    }
//    cout << best_res;
//    return 0;
//}
