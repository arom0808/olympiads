#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <deque>
#include <string>
#include <cmath>
#include <iomanip>
#define endl '\n'
#define ALL(v) begin(v),end(v)

using namespace std;
using ld = long double;

constexpr int MOD = 998244353, MAXN = 3E5, sq = 548, INF = 1E9 + 1;

template <typename T>
bool rmin(T& a, const T& b)
{
	if (b < a)
	{
		a = b;
		return true;
	}
	return false;
}
template <typename T>
bool rmax(T& a, const T& b)
{
	if (a < b)
	{
		a = b;
		return true;
	}
	return false;
}

struct Zap
{
	int st, ch, ind;
	Zap(int st = 0, int ch = 0, int ind = 0) :st(st), ch(ch), ind(ind) {}
	bool operator< (const Zap& z) const
	{
		return ch > z.ch;
	}
};

struct Otr
{
	int l, r;
	Otr(int l = 0, int r = 0) :l(l), r(r) {}
	bool operator< (const Otr& o) const
	{
		return r < o.r;
	}
};

int main()
{
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
#endif // _DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(0);
}