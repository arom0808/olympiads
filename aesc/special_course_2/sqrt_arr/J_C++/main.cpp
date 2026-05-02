#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

const int32_t maxm = 2e5 + 20;

template<typename T>
constexpr inline T div_up(T a, T b) {
    return (a + b - 1) / b;
}

namespace sq_arr {
    const int32_t sq_block_size = 512;
    const int32_t sq_block_cnt = div_up(maxm, sq_block_size);

    inline int32_t get_block_id(int32_t i) {
        return i >> 9;
    }

    inline int32_t get_in_block_pos(int32_t i) {
        return i & ((1 << 9) - 1);
    }

    int64_t nums[maxm];
    int64_t block_sum[sq_block_cnt];

    void init(const vector<int64_t> &v) {
        for (int32_t i = 0; i < v.size(); ++i) nums[i] = v[i];
        int64_t sum = 0;
        for (int32_t i = 0; i < maxm; ++i) {
            if (get_in_block_pos(i) == 0) {
                if (i > 0) block_sum[get_block_id(i) - 1] = sum;
                sum = 0;
            }
            sum += nums[i];
        }

        block_sum[get_block_id(maxm)] = sum;
    }

    void add(int32_t k, int64_t s) {
        block_sum[get_block_id(k)] += s;
        nums[k] += s;
    }

    int32_t upper_bound(int64_t s) {
        int64_t sum = 0;
        int32_t block_id = 0;
        while (block_id < sq_block_cnt && sum + block_sum[block_id] <= s) sum += block_sum[block_id++];
        if (block_id == sq_block_cnt) return maxm;
        int32_t si = block_id * sq_block_size, ci = -1;
        while (ci < sq_block_size && sum <= s) sum += nums[si + (++ci)];
        return si + ci;
    }
}

struct Monster {
    int32_t power = 0, health = 0;
};

struct Person {
    int32_t power = 0, health = 0, id = 0;

    bool operator<(const Person &other) const {
        if (power != other.power) return power < other.power;
        return health < other.health;
    }
};

Monster monsters[maxm];
int32_t ans[maxm];
int32_t d_div_a[maxm];

namespace a_sq_arr {
    const int32_t maxa = 1e9 + 200;
    const int32_t sq_block_size = 64;
    const int32_t sq_block_cnt = div_up(maxa, sq_block_size);

    struct Act {
        int32_t a = 0, m_id = 0;

        Act(int32_t a, int32_t m_id) : a(a), m_id(m_id) {}
    };

    vector<Act> acts[sq_block_cnt];

    void add_monster(int32_t m_id) {
        int32_t a;
        if (d_div_a[m_id] > 1) {
            a = div_up(monsters[m_id].health, d_div_a[m_id] - 1);
            acts[a / sq_block_size].emplace_back(a, m_id);
        }
    }

    void erase_val(int32_t b_id, int32_t i) {
        if (i + 1 != acts[b_id].size()) swap(acts[b_id].back(), acts[b_id][i]);
        acts[b_id].pop_back();
    }

    void process_changes(int32_t pre_a, int32_t a) {
        if (pre_a == a) return;
        for (int32_t ba = a / sq_block_size, b_id = pre_a / sq_block_size; b_id <= ba; ++b_id) {
            for (int32_t i = 0; i < acts[b_id].size();) {
                auto [ta, m_id] = acts[b_id][i];
                if (pre_a < ta && ta <= a) {
                    erase_val(b_id, i);
                    int32_t ndda = div_up(monsters[m_id].health, a);
                    sq_arr::add(m_id + 1, 1ll * (ndda - d_div_a[m_id]) * monsters[m_id].power);
                    d_div_a[m_id] = ndda;
                    if (ndda > 1) {
                        int32_t na = div_up(monsters[m_id].health, ndda - 1);
                        acts[na / sq_block_size].emplace_back(na, m_id);
                    }
                } else
                    ++i;
            }
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n, m;
    cin >> n >> m;
    vector<Person> pers(n);
    for (int32_t i = 0; i < n; ++i) cin >> pers[i].power >> pers[i].health, pers[i].id = i;
    for (int32_t i = 0; i < m; ++i) cin >> monsters[i].power >> monsters[i].health;
    sort(pers.begin(), pers.end());
    vector<int64_t> shn(m + 1);
    for (int32_t i = 0; i < m; ++i) {
        d_div_a[i] = div_up(monsters[i].health, pers.front().power);
        shn[i + 1] = 1ll * (d_div_a[i] - 1) * monsters[i].power + (i == 0 ? 1 : monsters[i - 1].power);
    }
    sq_arr::init(shn);
    for (int32_t i = 0; i < m; ++i) a_sq_arr::add_monster(i);
    int32_t pre_power = pers.front().power;
    for (auto [power, health, id]: pers) {
        a_sq_arr::process_changes(pre_power, power);
        pre_power = power;
        ans[id] = sq_arr::upper_bound(health) - 1;
        if (ans[id] == maxm - 1) ans[id] = m;
    }
    for (int32_t i = 0; i < n; ++i) cout << ans[i] << "\n";
    return 0;
}