#include <iostream>
#include <cstdlib>
#include <cassert>
#include <ctime>
using namespace std;

const int MAX_N = 100001;
int N;

long long ar[MAX_N], vals[4*MAX_N], temp_vals[4*MAX_N];

void build(int idx, int lo, int hi) {
  temp_vals[idx] = 0;
  if (lo == hi) {
    vals[idx] = ar[lo];
  } else {
    int k = (lo + hi) / 2;
    build(2*idx, lo, k);
    build(2*idx+1, k+1, hi);
    vals[idx] = vals[2*idx] + vals[2*idx+1];
  }
}

void build() {
  build(1, 0, N-1);
}

void visit(int idx, int left, int right) {
  if (temp_vals[idx]) {
    vals[idx] += (right - left + 1) * temp_vals[idx];
    if (2*idx < 4*MAX_N) {
      temp_vals[2*idx]   += temp_vals[idx];
      temp_vals[2*idx+1] += temp_vals[idx];
    }
    temp_vals[idx] = 0;
  }
}

void increase(int idx, int left, int right, int lo, int hi, long long val) {
  visit(idx, left, right);
  if (lo <= left && right <= hi) {
    temp_vals[idx] += val;
    visit(idx, left, right);
  } else if (hi < left || right < lo) {
    // do nothing
  } else {
    int k = (left + right) / 2;
    increase(2*idx, left, k, lo, hi, val);
    increase(2*idx+1, k+1, right, lo, hi, val);
    vals[idx] = vals[2*idx] + vals[2*idx+1];
  }
}

void increase(int lo, int hi, long long val) {
  increase(1, 0, N-1, lo, hi, val);
}

long long sum(int idx, int left, int right, int lo, int hi) {
  visit(idx, left, right);
  if (lo <= left && right <= hi) {
    return vals[idx];
  } else if (hi < left || right < lo) {
    return 0;
  } else {
    int k = (left + right) / 2;
    return sum(2*idx, left, k, lo, hi) + sum(2*idx+1, k+1, right, lo, hi);
  }
}

long long sum(int lo, int hi) {
  sum(1, 0, N-1, lo, hi);
}

int main() {
  srand((unsigned)time(0));

  N = 100000;
  int Q = 100000;
  bool TEST = false;

  long long br[N];
  for (int i = 0; i < N; ++i)
  ar[i] = br[i] = rand();

  build();

  while (Q--) {
    int type = rand()%2;
    if (type == 0) {
      int lo = rand()%N;
      int hi = rand()%N;
      if (lo > hi)  swap(lo, hi);
      int val = rand();

      increase(lo, hi, val);

      if (TEST) {
        for (int i = lo; i <= hi; ++i)
          br[i] += val;

        for (int i = lo; i <= hi; ++i)
          assert(br[i] == sum(i, i));
      }
    } else if (type == 1) {
      int lo = rand()%N;
      int hi = rand()%N;
      if (lo > hi)  swap(lo, hi);

      long long res1 = sum(lo, hi);

      if (TEST) {
        long long res2 = 0;
        for (int i = lo; i <= hi; ++i)
          res2 += br[i];

        assert(res1 == res2);
      }
    } else {
      assert(type == 0 || type == 1);
    }
  }

  return 0;
}
