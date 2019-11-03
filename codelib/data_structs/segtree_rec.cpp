#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <ctime>
using namespace std;

struct segtree {
  int i, j;
  long long val;
  segtree *l, *r;
  segtree(vector<long long> &ar, int _i, int _j) : i(_i), j(_j) {
    if (i == j) {
      this->val = ar[i];
      this->l = this->r = NULL;
    } else {
      int k = (i+j) >> 1;
      this->l = new segtree(ar, i, k);
      this->r = new segtree(ar, k+1, j);
      this->val = this->l->val + this->r->val;
    }
  }

  void update(int _i, long long _val) {
    if (i == _i && _i == j) {
      this->val = _val;
    } else if (_i < i || j < _i) {
      // do nothing
    } else {
      this->l->update(_i, _val);
      this->r->update(_i, _val);
      this->val = this->l->val + this->r->val;
    }
  }

  long long sum(int _i, int _j) {
    if (_i <= i && j <= _j) {
      return val;
    } else if (_j < i || j < _i) {
      return 0;
    } else {
      return this->l->sum(_i, _j) + this->r->sum(_i, _j);
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
      int idx = rand()%N;
      int val = rand();

      root->update(idx, val);

      if (TEST) {
        br[idx] = val;

        assert(br[idx] == root->sum(idx, idx));
      }
    } else if (type == 1) {
      int idx_s = rand()%N;
      int idx_t = rand()%N;
      if (idx_s > idx_t)  swap(idx_s, idx_t);

      long long res1 = root->sum(idx_s, idx_t);

      if (TEST) {
        long long res2 = 0;
        for (int i = idx_s; i <= idx_t; ++i)
          res2 += br[i];

        assert(res1 == res2);
      }
    } else {
      assert(type == 0 || type == 1);
    }
  }


  return 0;
}
