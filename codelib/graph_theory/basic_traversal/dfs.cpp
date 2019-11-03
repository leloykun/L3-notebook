#include <iostream>
#include <vector>

struct graph {
  int n;
  std::vector<int> *adj;
  int *vis;
  graph(int n) {
    this->n = n;
    adj = new std::vector<int>[n];
    vis = new int[n];
  }

  void add_edge(int u, int v) {
    adj[u].push_back(v);
    // adj[v].push_back(u);
  }

  void dfs(int u) {
    vis[u] = 1;
    for (int v : adj[u])
      if (!vis[v])
        dfs(v);
  }
};

int main() {

}
