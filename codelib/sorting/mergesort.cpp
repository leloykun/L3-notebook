#include <vector>
#include <iostream>

void merge(std::vector<int> &ar, int lo, int mid, int hi) {
  int i = lo, j = mid + 1, t = 0;
  int *temp = new int[hi-lo+1];
  while (i <= mid and j <= hi) {
    if (ar[i] < ar[j])
      temp[t++] = ar[i++];
    else
      temp[t++] = ar[j++];
  }
  while (i <= mid)
    temp[t++] = ar[i++];
  while (j <= hi)
    temp[t++] = ar[j++];

  for (t = 0; t < hi - lo + 1; ++t)
    ar[lo+t] = temp[t];
  delete [] temp;
}

void mergesort(std::vector<int> &ar, int lo,  int hi) {
  if (lo >= hi)   return;

  int mid = (lo + hi) / 2;
  mergesort(ar, lo, mid);
  mergesort(ar, mid+1, hi);
  merge(ar, lo, mid, hi);
}

int main() {
  std::vector<int> ar = {5, 2, 6, 1, 7, 4, 3};
  mergesort(ar, 0, 6);
  for (int x : ar)
    std::cout<<x<<" ";
  std::cout<<"\n";

  return 0;
}
