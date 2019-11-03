#include <iostream>
#include <vector>

#define INF 1e9

struct max_flow {
  int n, s, t;
  std::vector<int> *adj;
  int *par;
  int **c;
  int **f;
  max_flow(int n, int s, int t) {
    this->n = n;
    this->s = s;
    this->t = t;
    adj = new std::vector<int>[n];
    par = new int[n];
    c = new int*[n];
    f = new int*[n];
    for (int i = 0; i < n; ++i) {
      c[i] = new int[n];
      f[i] = new int[n];
      for (int j = 0; j < n; ++j)
        c[i][j] = f[i][j] = 0;
    }
  }

  void add_edge(int u, int v, int w) {
    adj[u].push_back(v);
    adj[v].push_back(u);
    c[u][v] += w;
  }

  int res(int i, int j) {
    return c[i][j] - f[i][j];
  }

  bool dfs(int u) {
    if (u == t)	return true;
    for (int v : adj[u]) {
      if (res(u, v) > 0 and par[v] == -1) {
        par[v] = u;
        if (dfs(v))
          return true;
      }
    }
    return false;
  }

  bool aug_path() {
    for (int u = 0; u < n; ++u)
      par[u] = -1;
    par[s] = s;
    return dfs(s);
  }

  int calc_max_flow() {
    int ans = 0;
    while (aug_path()) {
      int flow = INF;
      for (int u = t; u != s; u = par[u])
        flow = std::min(flow, res(par[u], u));
      for (int u = t; u != s; u = par[u])
        f[par[u]][u] += flow, f[u][par[u]] -= flow;
      ans += flow;
    }
    return ans;
  }
};

int N, M, S, T;

int main() {
  std::cin >> N >> M;
  std::cin >> S >> T;

  max_flow mf(N, S, T);

  for (int i = 0; i < M; ++i) {
    int u, v, w;		std::cin >> u >> v >> w;
    mf.add_edge(u, v, w);
  }

  std::cout << mf.calc_max_flow() << "\n";

  return 0;
}
