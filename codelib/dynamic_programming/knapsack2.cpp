#include <iostream>
#include <cstring>

int main() {
  int N, C;   std::cin >> N >> C;

  int W[N], V[N];
  for (int i = 0; i < N; ++i)
    std::cin >> W[i] >> V[i];

  int dp[C + 1];
  memset(dp, 0, sizeof dp);
  for (int w = 0; w <= C; ++w)
    for (int i = 0; i < N; ++i)
      dp[w] = (w < W[i]) ? dp[w] : dp[w - W[i]] + V[i];

  std::cout << dp[C] << "\n";

  return 0;
}
