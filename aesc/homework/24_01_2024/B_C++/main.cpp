//#include<iostream>
//#include<vector>
//#include<set>
//#include<map>
//#include<cmath>
//#include<algorithm>
//#include<iomanip>
//using namespace std;
//#define ll long long
//#define ld long double
//#define FRO(i,a,b) for(ll i=a;i<b;i++)
//#define fast_cin() iostream::sync_with_stdio(false);cin.tie(0); cout.tie(0)
//typedef vector<ll>  vl;
//ll a,b,c,d,x0,x1,x2;
//void step(ll& q,ll& w, ll& e) {
//    ll t = (a*e+b*w+c*q)%d;
//    q=w;
//    w=e;
//    e=t;
//}
//int main() {
//    fast_cin();
//    cin >> a >> b >> c >> d >> x0 >> x1 >> x2;
//    ll p1 = x0, p2 = x1, p3 = x2, e1 = x1, e2 = x2, e3=  (a*x2+b*x1+c*x0)%d;
//
//    while(p1!=e1 or p2!=e2 or p3!=e3) {
//        step(e1,e2,e3);
//        step(e1,e2,e3);
//        step(p1,p2,p3);
//    }
//
//    ll periodic=0;
//    do {
//        step(p1,p2,p3);
//        periodic++;
//    } while(e1!=p1 or e2!=p2 or e3!=p3);
//
//    p1=x0, p2 =x1,p3=x2, e1=x0,e2=x1,e3=x2;
//    for(ll i=0;i<periodic;i++) step(e1,e2,e3);
//    ll nonperiodic = 0;
//    while(p1!=e1 or p2 != e2 or p3!=e3) {
//        step(p1,p2,p3);
//        step(e1,e2,e3);
//        nonperiodic++;
//    }
//    cout << periodic << " " << nonperiodic;
//}
//

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class RandGen {
public:
    uint32_t a, b, c, d;

    inline uint32_t operator()(uint32_t x1, uint32_t x2, uint32_t x3) const {
        return (a * x3 + b * x2 + c * x1) % d;
    }

    inline void step(uint32_t &x1, uint32_t &x2, uint32_t &x3) const {
        uint32_t temp = (*this)(x1, x2, x3);
        x1 = x2, x2 = x3, x3 = temp;
    }

//    inline void step3(uint32_t &x1, uint32_t &x2, uint32_t &x3) const {
//        x1 = (*this)(x1, x2, x3), x2 = (*this)(x2, x3, x1), x3 = (*this)(x3, x1, x2);
//    }

    RandGen(uint32_t a, uint32_t b, uint32_t c, uint32_t d) : a(a), b(b), c(c), d(d) {}
};

int main() {
    uint32_t a, b, c, d, x0, x1, x2;
    cin >> a >> b >> c >> d >> x0 >> x1 >> x2;
    RandGen rg(a, b, c, d);
    uint32_t nx0 = x0, nx1 = x1, nx2 = x2, ny0 = x1, ny1 = x2, ny2 = rg(x0, x1, x2), lp = 0, lnp = 0;
    while (nx0 != ny0 || nx1 != ny1 || nx2 != ny2)
        rg.step(nx0, nx1, nx2), rg.step(ny0, ny1, ny2), rg.step(ny0, ny1, ny2);
    ny0 = nx0, ny1 = nx1, ny2 = nx2;
    do { rg.step(ny0, ny1, ny2), ++lp; } while (nx0 != ny0 || nx1 != ny1 || nx2 != ny2);
    nx0 = ny0 = x0, nx1 = ny1 = x1, nx2 = ny2 = x2;
    for (uint32_t i = 0; i < lp; ++i) rg.step(ny0, ny1, ny2);
    while (nx0 != ny0 || nx1 != ny1 || nx2 != ny2) rg.step(nx0, nx1, nx2), rg.step(ny0, ny1, ny2), ++lnp;
    vector<int32_t> cnts(20, 0);
    nx0 = x0, nx1 = x1, nx2 = x2;
    for (uint32_t i = 0; i < 400; ++i) {
        ++cnts[nx0 * 20 / d];
        rg.step(nx0, nx1, nx2);
    }
    uint32_t q = 0;
    for (auto cnt: cnts) q += (cnt - 20) * (cnt - 20);
    cout << fixed << setprecision(10) << lp << " " << lnp << " " << static_cast<long double>(q) / 400;
//    cout << lp << " " << lnp;
    return 0;
}
