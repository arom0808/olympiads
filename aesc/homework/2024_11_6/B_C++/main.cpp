#include <iostream>

using namespace std;

int mod = 1e9;

struct HV {
    int val = 0;

    HV(int val = 0): val(val) {
    }

    HV &force_mod() {
        val %= mod;
        return *this;
    }

    HV &operator+=(const HV &rhs) {
        val += rhs.val;
        if (val >= mod) val -= mod;
        return *this;
    }

    HV operator+(const HV &rhs) const {
        HV res = *this;
        return res += rhs;
    }

    HV &operator-=(const HV &rhs) {
        if (val < rhs.val) val = val + mod - rhs.val;
        else val -= rhs.val;
        return *this;
    }

    HV operator-(const HV &rhs) const {
        HV res = *this;
        return res -= rhs;
    }

    HV &operator*=(const HV &rhs) {
        if (mod) val = 1ll * val * rhs.val % mod;
        else val *= rhs.val;
        return *this;
    }

    HV operator*(const HV &rhs) const {
        HV res = *this;
        return res *= rhs;
    }

    bool operator==(const HV &rhs) const {
        return val == rhs.val;
    }

    friend istream &operator>>(istream &is, HV &rhs) {
        is >> rhs.val;
        rhs.force_mod();
        return is;
    }

    friend ostream &operator<<(ostream &os, HV &rhs) {
        os << rhs.val;
        return os;
    }
};

struct DPVal {
    HV lt, rt, cc, ct; // left triangle, right triangle, center column, center triangle

    DPVal &operator=(HV val) {
        lt = rt = cc = ct = val;
        return *this;
    }

    friend istream &operator>>(istream &is, DPVal &d) {
        is >> d.lt;
        d.rt = d.cc = d.ct = d.lt;
        return is;
    }
};

constexpr int maxn = 2000;
DPVal dp[2][maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n, m;
    cin >> n >> m >> mod;
    for (int j = 0; j < m; ++j) cin >> dp[0][j];
    for (int j = 0; j < m; ++j) {
        dp[1][j].lt = dp[0][j].cc + (j > 0 ? dp[0][j - 1].cc : 0);
        dp[1][j].rt = dp[0][j].cc + (j + 1 < m ? dp[0][j + 1].cc : 0);
        dp[1][j].cc = dp[0][j].cc;
        dp[1][j].ct = dp[1][j].lt + dp[1][j].rt - dp[1][j].cc;
    }
    auto pre_dp = dp[1], cur_dp = dp[0];
    for (int i = 2; i < n; ++i) {
        for (int j = 0; j < m; ++j) cur_dp[j] = 0;
        for (int j = 0; j < m; ++j) {
            if (j > 0) cur_dp[j].lt += pre_dp[j - 1].lt + pre_dp[j - 1].ct;
            if (j + 1 < m) cur_dp[j].rt += pre_dp[j + 1].rt + pre_dp[j + 1].ct;
            cur_dp[j].cc = pre_dp[j].cc + pre_dp[j].ct;
            cur_dp[j].lt += cur_dp[j].cc;
            cur_dp[j].rt += cur_dp[j].cc;
            cur_dp[j].ct = cur_dp[j].lt + cur_dp[j].rt - cur_dp[j].cc;
        }
        swap(pre_dp, cur_dp);
    }
    for (int j = 0; j < m; ++j) cout << pre_dp[j].ct << " ";
    cout << "\n";
    return 0;
}
