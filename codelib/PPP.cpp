#include <iostream>
#include <vector>
#include <algorithm>

bool is_prime(int x) {
  if (x <= 1)
    return false;
  for (int f = 2; f*f <= x; ++f)
    if (x % f == 0)
      return false;
  return true;
}

int dfs(int u, std::vector<int> &P, std::vector<int> &vis) {
  vis[u] = 1;
  int sum = u+1;
  if (!vis[P[u]])
    sum += dfs(P[u], P, vis);
  return sum;
}

bool check(std::vector<int> &P, int N) {
  std::vector<int> vis(N, 0);
  for (int u = 0; u < N; ++u)
    if (!vis[u] and !is_prime(dfs(u, P, vis)))
      return false;
  return true;
}

int main() {
  int MAXN; std::cin>>MAXN;
  for (int N = 2; N <= MAXN; ++N) {
    std::vector<int> P;
    for (int i = 0; i < N; ++i)
      P.push_back(i);

    do {
      if (check(P, N)) {
        for (int i = 0; i < N; ++i)
          std::cout<<P[i]+1<<" ";
        std::cout<<"\n";
        break;
      }
    } while (std::next_permutation(P.begin(), P.end()));
  }

  return 0;
}
