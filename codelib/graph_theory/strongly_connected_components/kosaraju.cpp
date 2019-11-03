#include <iostream>
#include <vector>

struct graph {
  int n;
  std::vector<int> **adj;
  int *vis;
  std::vector<std::vector<int> > sccs;
  graph(int n) {
    this->n = n;
    adj = new std::vector<int>*[2];
    for (int i = 0; i < 2; ++i)
      adj[i] = new std::vector<int>[n];
    vis = new int[n];
  }

  void add_edge(int u, int v) {
    adj[0][u].push_back(v);
    adj[1][v].push_back(u);
  }

  void dfs(int u, int p, int dir, std::vector<int> &ar) {
    vis[u] = 1;
    for (int v: adj[dir][u])
      if (!vis[v] and v != p)
        dfs(v, u, dir, ar);
    ar.push_back(u);
  }

  void kosaraju() {
    std::vector<int> topo;
    for (int u = 0; u < n; ++u)
      vis[u] = 0;
    for (int u = 0; u < n; ++u)
      if (!vis[u])
        dfs(u, -1, 0, topo);

    for (int u = 0; u < n; ++u)
      vis[u] = 0;
    for (int i = n-1; i >= 0; --i) {
      int u = topo[i];
      if (!vis[u]) {
        sccs.push_back({});
        dfs(u, -1, 1, sccs.back());
      }
    }
  }
};

int main() {
  int N, E;   std::cin >> N >> E;
  graph g(N);
  for (int i = 0; i < E; ++i) {
    int u, v;   std::cin >> u >> v;
    g.add_edge(u, v);
  }

  g.kosaraju();

  std::cout << "sccs: \n";
  for (auto &scc : g.sccs) {
    for (int u : scc)
      std::cout << u << " ";
    std::cout << "\n";
  }

  return 0;
}
