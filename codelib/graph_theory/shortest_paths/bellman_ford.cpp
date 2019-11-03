#include <iostream>
#include <utility>
#include <vector>

#define INF 1e9

struct graph {
  int n;
  std::vector<std::pair<int, int> > *adj;
  int *dist;
  graph(int n) {
    this->n = n;
    adj = new std::vector<std::pair<int, int> >[n];
    dist = new int[n];
  }

  void add_edge(int u, int v, int w) {
    adj[u].push_back({v, w});
    // adj[v].push_back({u, w});
  }

  void bellman_ford() {
    for (int u = 0; u < n; ++u)
      dist[u] = INF;
    dist[s] = 0;
    for (int i = 0; i < n-1; ++i)
      for (int u = 0; u < n; ++u)
        for (auto &e : adj[u])
          dist[e.first] = std::min(dist[e.first], dist[u] + e.second);
  }

  bool has_neg_cycle() {
    for (int u = 0; u < n; ++u)
      for (auto &e : adj[u])
        if (dist[e.first] > dist[u] + e.second)
          return true;
    return false;
  }
};

int main() {

  return 0;
}
