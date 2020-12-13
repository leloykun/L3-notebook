//#pragma GCC optimize("Ofast","unroll-loops")
//#pragma GCC target("avx2,fma")
#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <ctime>
#define rep(i,a,b) for (__typeof(a) i=(a); i<(b); ++i)
#define iter(it,c) for (__typeof((c).begin()) \
  it = (c).begin(); it != (c).end(); ++it)
typedef std::pair<int, int> ii;
typedef std::vector<int> vi;
typedef std::vector<ii> vii;
typedef long long ll;
const int INF = ~(1<<31);
const int MAXN = 1e5+1;

const double EPS = 1e-9;
const double pi = acos(-1);
typedef unsigned long long ull;
typedef std::vector<vi> vvi;
typedef std::vector<vii> vvii;
template <class T> T smod(T a, T b) {
  return (a % b + b) % b; }
// vim: cc=60 ts=2 sts=2 sw=2:
