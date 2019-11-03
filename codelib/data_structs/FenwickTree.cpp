#include <iostream>
#include <vector>
using namespace std;

struct fenwick {
  vector<int> ar;

  fenwick(vector<int> &_ar) {
    ar = vector<int>(_ar.size(), 0);
    for (int i = 0; i < ar.size(); ++i) {
      ar[i] += _ar[i];
      int j = i | (i+1);
      if (j < ar.size())
        ar[j] += ar[i];
    }
  }

  //  return sum[0..i]
  int sum(int i) {
    int res = 0;
    for (; i >= 0; i = (i & (i+1)) - 1)
      res += ar[i];
    return res;
  }

  //  return sum[i..j]
  int sum(int i, int j) {
    return sum(j) - sum(i-1);
  }

  //  ar[i] += val
  void add(int i, int val) {
    for (; i < ar.size(); i |= i+1)
      ar[i] += val;
  }

  //  return ar[i]
  int get(int i) {
    int res = ar[i];
    if (i) {
      int lca = (i & (i+1)) - 1;
      for (--i; i != lca; i = (i&(i+1))-1)
        res -= ar[i];
    }
    return res;
  }

  //  ar[i] = val
  void set(int i, int val) {
    add(i, -get(i) + val);
  }

  /////////////////////////////////////////
  //  interval add
  void add(int i, int j, int val) {
    add(i, val);
    add(j+1, -val);
  }

  //  point query
  int get1(int i) {
    return sum(i);
  }
  /////////////////////////////////////////
};

int main() {
  int N = 6;
  vector<int> ar(N, 0);
  for (int i = 0; i < N; ++i)
    ar[i] = i+1;

  fenwick fw(ar);

  cout<<fw.sum(0)<<endl;
  cout<<fw.sum(1)<<endl;
  cout<<fw.sum(2)<<endl;
  cout<<fw.sum(3)<<endl;
  cout<<fw.sum(4)<<endl;
  cout<<fw.sum(5)<<endl;
  cout<<fw.sum(2, 4)<<endl;
  cout<<fw.sum(3, 5)<<endl;

  return 0;
}
