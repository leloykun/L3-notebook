#include <iostream>
#include <cassert>
#include <vector>

struct heap {
  std::vector<int> ar;
  int N;

  heap() : N(0) { }
  heap(std::vector<int> &_ar) : ar(_ar), N(_ar.size()) {
    for (int k = (N-2)/2; k >= 0; --k)
      sink(k);
  }

  void sink(int k) {
    while (2*k + 1 < N) {
      int j = 2*k + 1;
      if (j + 1 < N and ar[j] < ar[j+1])
        j++;
      if (ar[j] < ar[k])
        break;
      std::swap(ar[j], ar[k]);
      k = j;
    }
  }

  void swim(int k) {
    while (k >= 0 and ar[(k-1)/2] < ar[k]) {
      std::swap(ar[(k-1)/2], ar[k]);
      k = (k-1) / 2;
    }
  }

  void push(int val) {
    ar.push_back(val);
    swim(N++);
  }

  void pop() {
    assert(N > 0);
    std::swap(ar[0], ar[--N]);
    ar.pop_back();
    sink(0);
  }

  int top() {
    assert(N > 0);
    return ar[0];
  }
};

int main() {
  std::vector<int> vr = {0, 1, 3};
  heap pq(vr);
  std::cout<<pq.top()<<"\n";
  pq.push(14);
  pq.push(3);
  std::cout<<pq.top()<<"\n";
  pq.pop();
  pq.push(1);
  pq.push(13);
  std::cout<<pq.top()<<"\n";

  return 0;
}
