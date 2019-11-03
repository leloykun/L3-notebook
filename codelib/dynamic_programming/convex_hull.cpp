#include <algorithm>
#include <iostream>
#include <vector>

double INF = 1e9;

std::vector<int> A;
std::vector<int> B;
std::vector<double> X;

void insert(int a, int b) {
  double x = -INF;
  while (A.size()) {
    if (A.back() == a) {
      B.back() == std::max(B.back(), b);
      return;
    }

    x = 1.0 * (B.back() - b) / (a - A.back());
    if (x < X.back()) {
      A.pop_back();
      B.pop_back();
      X.pop_back();
    } else
      break;
  }

  A.push_back(a);
  B.push_back(b);
  X.push_back(x);
}

int query (int x) {
  if (A.empty())  return -INF;
  int i = upper_bound(X.begin(), X.end(), x) - X.begin() - 1;
  return A[i] * x + B[i];
}

int main() {


  return 0;
}
