#include <iostream>
#include <vector>

struct fenwick {
  std::vector<int> ar;
  fenwick(int n) : ar(n, 0) { }
  fenwick(std::vector<int> &_ar) : ar(_ar.size(), 0) {
    for (int i = 0; i < _ar.size(); ++i)
      update(i, _ar[i]);
  }

  int lsb(int x) {
    return x & -x;
  }

  void update(int pos, int val) {
    while (pos < ar.size()) {
      std::cout<<pos<<" ";
      ar[pos] += val;
      pos += lsb(pos);
    }
    std::cout<<"\n";
  }

  int query(int pos) {
    int sum = 0;
    while (pos) {
      sum += ar[pos];
      pos -= lsb(pos);
    }
    return sum;
  }
};

int main() {
  std::vector<int> ar = {1, 2, 3, 4, 5};
  fenwick fw(ar);

  return 0;
}
