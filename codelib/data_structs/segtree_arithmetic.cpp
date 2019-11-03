#include <iostream>
#include <vector>
#include <utility>

typedef long long ll;
typedef std::pair<ll, ll> pll;

struct D {
  ll a;
  ll d;
  D(ll _a, ll _d) : a(_a), d(_d) {}
};

struct segtree {
  int i, j, n;
  ll val;
  D temp_val;
  segtree *l, *r;

  segtree(std::vector<ll> &ar, int _i, int _j) : i(_i), j(_j), temp_val(0LL, 0LL) {
    n = j - i + 1;
    if (i == j) {
      val = ar[i];
      l = r = NULL;
    } else {
      int k = (i + j) >> 1;
      l = new segtree(ar, i, k);
      r = new segtree(ar, k+1, j);
      pull();
    }
  }

  void pull() {
    this->val = l->val + r->val;
  }

  void visit() {
    if (temp_val.a or temp_val.d) {
      val += n * (2*temp_val.a + (n-1)*temp_val.d) / 2;
      if (l) {
        l->temp_val.a += temp_val.a;
        l->temp_val.d += temp_val.d;

        r->temp_val.a += temp_val.a + temp_val.d * l->n;
        r->temp_val.d += temp_val.d;
      }
      temp_val = D(0LL, 0LL);
    }
  }

  void increase(int _i, int _j, D inc) {
    this->visit();
    if (_i <= i && j <= _j) {
      temp_val.a += inc.a + inc.d * (i - _i);
      temp_val.d += inc.d;
      this->visit();
    } else if (_j < i || j < _i) {
      // do nothing
    } else {
      this->l->increase(_i, _j, inc);
      this->r->increase(_i, _j, inc);
      pull();
    }
  }

  long long sum(int _i, int _j) {
    this->visit();
    if (_i <= i && j <= _j) {
      return val;
    } else if (_j < i || j < _i) {
      return 0;
    } else {
      return l->sum(_i, _j) + r->sum(_i, _j);
    }
  }
};

int main() {
  int N = 10;
  std::vector<ll> a(N);
  segtree *root = new segtree(a, 0, N-1);

  root->increase(0, N-1, D(0LL, 1LL));
  for (int i = 0; i < N; ++i)
    std::cout<<root->sum(i, i)<<" ";
  std::cout<<"\n";

  root->increase(5, N-1, D(0LL, 1LL));
  for (int i = 0; i < N; ++i)
    std::cout<<root->sum(i, i)<<" ";
  std::cout<<"\n";

  return 0;
}
