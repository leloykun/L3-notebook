#include <iostream>
#include <vector>
using namespace std;

struct fenwick2D {
  vector<vector<int>> ar;

  fenwick2D(int r, int c) {
    ar = vector<vector<int>>(r, vector<int>(c));
  }

  //  sum[(0, 0), (i, j)]
  int sum(int i, int j) {
    int res = 0;
    for (; i >= 0; i = (i&(i+1))-1)
      for (; j >= 0; j = (j&(j+1))-1)
        res += ar[i][j];
    return res;
  }

  //  sum[(i1, j1), (i2, j2)]
  int sum(int i1, int j1, int i2, int j2) {
    return sum(i2, j2) - sum(i1-1, j2) - sum(i2, j1-1) + sum(i1-1, j1-1);
  }

  //  ar[i][j] += val
  void add(int i, int j, int val) {
    for (; i < ar.size(); i |= i + 1)
      for (; j < ar[0].size(); j |= j + 1)
        ar[i][j] += val;
  }

  //  ar[i][j]
  int get(int i, int j) {
    return sum(i, j, i, j);
  }

  //  ar[i][j] = val;
  int set(int i, int j, int val) {
    add(i, j, -get(i, j) + val);
  }
};

int main() {



  return 0;
}
