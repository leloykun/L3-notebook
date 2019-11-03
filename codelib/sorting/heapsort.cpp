#include <iostream>
#include <vector>

void sink(std::vector<int> &ar, int k, int N) {
  while (2*k + 1 < N) {
    int j = 2*k + 1;
    if (j + 1 < N and ar[j] < ar[j+1])
      j++;
    if (ar[k] > ar[j])
      break;
    std::swap(ar[k], ar[j]);
    k = j;
  }
}

void heapsort(std::vector<int> &ar, int N) {
  for (int k = (N-1) / 2; k >= 0; --k)
    sink(ar, k, N-1);

  while (N) {
    std::swap(ar[0], ar[--N]);
    sink(ar, 0, N);
  }
}

int main() {
  std::vector<int> ar = {5, 2, 6, 1, 7, 4, 3};
  heapsort(ar, 7);
  for (int x : ar)
    std::cout<<x<<" ";
  std::cout<<"\n";

  return 0;
}
