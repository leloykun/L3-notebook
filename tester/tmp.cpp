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

#include "C:/Users/admin/Github/admu-progvar-notebook/code/data-structures/union_find.cpp"
bool ANY_FAILED = false;

template <class T>
void assert_equal(T expected, T actual, bool kill = false) {
    if (!(expected == actual)) {
        ANY_FAILED = true;
        std::cout << "Assertion failed:" << std::endl;
        std::cout << "Expected: " << expected << std::endl;
        std::cout << "  Actual: " << actual << std::endl;
        if (kill) assert(false);
    }
}

template <class T>
void assert_not_equal(T not_expected, T actual, bool kill = false) {
    if (not_expected == actual) {
        ANY_FAILED = true;
        std::cout << "Assertion failed:" << std::endl;
        std::cout << "Not expected: " << not_expected << std::endl;
        std::cout << "      Actual: " << actual << std::endl;
        if (kill) assert(false);
    }
}

void assert_true(bool actual, bool kill = false) {
    if (true != actual) {
        ANY_FAILED = true;
        std::cout << "Assertion failed:" << std::endl;
        std::cout << "Expected: " << "true" << std::endl;
        std::cout << "  Actual: " << "false" << std::endl;
        if (kill) assert(false);
    }
}

void assert_false(bool actual, bool kill = false) {
    if (false != actual) {
        ANY_FAILED = true;
        std::cout << "Assertion failed:" << std::endl;
        std::cout << "Expected: " << "false" << std::endl;
        std::cout << "  Actual: " << "true" << std::endl;
        assert(false);
        if (kill) assert(false);
    }
}

void assert_almost_equal(double a, double b, double eps = 1e-9, bool kill = false) {
    assert_true(abs(a - b) < eps, kill);
}

double randdouble(double a, double b) {
    return static_cast<double>(rand()) / RAND_MAX * (b - a) + a;
}

int randint(int a, int b) {
    return static_cast<int>(randdouble(a, b) + 0.5);
}

#line 1 "C:/Users/admin/Github/admu-progvar-notebook/code/data-structures/union_find.test.cpp"
void test() {
  const int n = 20;
  union_find uf(n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) {
        assert_equal(uf.find(i), uf.find(j));
      } else {
        assert_not_equal(uf.find(i), uf.find(j));
      }
    }
  }

  assert_true(uf.unite(3, 5));
  assert_equal(uf.find(3), uf.find(5));
  assert_not_equal(uf.find(3), uf.find(4));
  assert_not_equal(uf.find(3), uf.find(6));
  assert_not_equal(uf.find(3), uf.find(2));
  assert_not_equal(uf.find(5), uf.find(4));
  assert_not_equal(uf.find(5), uf.find(6));
  assert_not_equal(uf.find(5), uf.find(2));

  assert_true(uf.unite(11, 5));
  assert_equal(uf.find(3), uf.find(11));
  assert_equal(uf.find(5), uf.find(11));
  assert_equal(uf.find(3), uf.find(5));
  assert_not_equal(uf.find(3), uf.find(4));
  assert_not_equal(uf.find(3), uf.find(6));
  assert_not_equal(uf.find(3), uf.find(2));
  assert_not_equal(uf.find(5), uf.find(4));
  assert_not_equal(uf.find(5), uf.find(6));
  assert_not_equal(uf.find(5), uf.find(2));
  assert_not_equal(uf.find(11), uf.find(4));
  assert_not_equal(uf.find(11), uf.find(6));
  assert_not_equal(uf.find(11), uf.find(2));

  assert_false(uf.unite(11, 5));
  assert_equal(uf.find(3), uf.find(11));
  assert_equal(uf.find(5), uf.find(11));
  assert_equal(uf.find(3), uf.find(5));
  assert_not_equal(uf.find(3), uf.find(4));
  assert_not_equal(uf.find(3), uf.find(6));
  assert_not_equal(uf.find(3), uf.find(2));
  assert_not_equal(uf.find(5), uf.find(4));
  assert_not_equal(uf.find(5), uf.find(6));
  assert_not_equal(uf.find(5), uf.find(2));
  assert_not_equal(uf.find(11), uf.find(4));
  assert_not_equal(uf.find(11), uf.find(6));
  assert_not_equal(uf.find(11), uf.find(2));

  assert_false(uf.unite(5, 3));
  assert_false(uf.unite(3, 5));
  assert_false(uf.unite(5, 11));
  assert_false(uf.unite(3, 11));
}

int main() {
    srand(time(NULL));
    test();
    assert(!ANY_FAILED);
    return 0;
}
