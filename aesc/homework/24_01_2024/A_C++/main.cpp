#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>

using namespace std;
#define ll long long
#define ld long double
typedef vector<ll> vl;

int main() {
    ll a, b, c, d, x0, x1;
    cin >> a >> b >> c >> d >> x0 >> x1;
    ll p1 = x0, p2 = x1, e1 = x1, e2 = (a * x1 + b * x0 + c) % d, t;
    while (p1 != p2 or e1 != e2) {
        p2 = (a * e2 + b * p2 + c) % d;
        e2 = (a * p2 + b * e2 + c) % d;
        t = (a * e1 + b * p1 + c) % d;
        p1 = e1;
        e1 = t;
    }
    ll n = 0;
    do {
        ll x = (a * e1 + b * p1 + c) % d;
        p1 = e1;
        e1 = x;
        ++n;
    } while (p1 != p2 or e1 != e2);
    p1 = x0, e1 = x1, p2 = x0, e2 = x1;
    for (ll i = 0; i < n; i++) {
        t = (a * e2 + b * p2 + c) % d;
        p2 = e2;
        e2 = t;
    }
    ll p = 0;
    while (p1 != p2 or e1 != e2) {
        p++;
        t = (a * e2 + b * p2 + c) % d;
        p2 = e2;
        e2 = t;
        t = (a * e1 + b * p1 + c) % d;
        p1 = e1;
        e1 = t;
    }
    vl r(20, 0);
    for (ll i = 0; i < 200; i++) {
        r[x0 * 20 / d]++;
        r[x1 * 20 / d]++;
        x0 = (a * x1 + b * x0 + c) % d;
        x1 = (a * x0 + b * x1 + c) % d;
    }
    ld s = 0;
    for (auto e: r) s += (e - 20) * (e - 20);
    cout << fixed << setprecision(2) << n << " " << p << s / 400;
}
