#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <ctime>
using namespace std;

struct segtree {
  int i, j;
  long long val, temp_val;
  segtree *l, *r;

  segtree(vector<long long> &ar, int _i, int _j) : i(_i), j(_j), temp_val(0) {
    if (i == j) {
      val = ar[i];
      l = r = NULL;
    } else {
      int k = (i + j) >> 1;
      l = new segtree(ar, i, k);
      r = new segtree(ar, k+1, j);
      val = l->val + r->val;
    }
  }

  void visit() {
    if (temp_val) {
      val += (j-i+1) * temp_val;
      if (l) {
        l->temp_val += temp_val;
        r->temp_val += temp_val;
      }
      temp_val = 0;
    }
  }

  void increase(int _i, int _j, long long _inc) {
    this->visit();
    if (_i <= i && j <= _j) {
      temp_val += _inc;
      this->visit();
    } else if (_j < i || j < _i) {
      // do nothing
    } else {
      this->l->increase(_i, _j, _inc);
      this->r->increase(_i, _j, _inc);
      this->val = this->l->val + this->r->val;
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
  srand((unsigned)time(0));

  int N = 100000;
  int Q = 100000;
  bool TEST = false;

  vector<long long> ar(N), br(N);
  for (int i = 0; i < N; ++i)
    ar[i] = rand();
  br = ar;

  segtree *root = new segtree(ar, 0, N-1);

  for (int q = 0; q < Q; ++q) {
    int type = rand()%2;
    if (type == 0) {
      int s = rand()%N;
      int t = rand()%N;
      if (s > t)  swap(s, t);
      long long inc = rand();

      root->increase(s, t, inc);

      if (TEST) {
        for (int i = s; i <= t; ++i)
          br[i] += inc;

        for (int i = s; i <= t; ++i)
          assert(br[i] == root->sum(i, i));
      }
    } else if (type == 1) {
      int s = rand()%N;
      int t = rand()%N;
      if (s > t)  swap(s, t);

      long long res1 = root->sum(s, t);

      if (TEST) {
        long long res2 = 0;
        for (int i = s; i <= t; ++i)
          res2 += br[i];

        assert(res1 == res2);
      }
    } else {
      assert(type == 0 || type == 1);
    }
  }

  return 0;
}
