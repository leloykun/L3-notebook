#include <vector>
#include <iostream>

void quicksort(std::vector<int> &ar, int lo, int hi) {
  if (lo >= hi)
    return;

  const int pivot = ar[lo];
  int i = lo + 1;
  int j = hi;
  while (i <= j) {
    while (i <= j and ar[i] <= pivot)
      ++i;
    while (i <= j and ar[j] > pivot)
      --j;
    if (i < j)
      std::swap(ar[i], ar[j]);
  }
  std::swap(ar[i-1], ar[lo]);

  quicksort(ar, lo, i-2);
  quicksort(ar, i, hi);
}

int main() {
  std::vector<int> ar = {5, 2, 6, 1, 7, 4, 3};
  quicksort(ar, 0, 6);
  for (int x : ar)
    std::cout<<x<<" ";
  std::cout<<"\n";

  return 0;
}
