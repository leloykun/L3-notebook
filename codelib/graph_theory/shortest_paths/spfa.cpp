#include <iostream>
#include <queue>
#include <utility>
#include <vector>

typedef std::pair<int, int> ii;
const int INF = 1e9;

struct graph {
  int n, *dist, *in_queue, *num_vis;
  std::vector<ii> *adj;
  graph (int n) : n(n) {
    dist = new int[n];
    in_queue = new int[n];
    num_vis = new int[n];
    adj = new std::vector<ii>[n];
  }

  void add_edge(int u, int v, int c) {
    adj[u].push_back({v, c});
  }
  bool spfa(int s) {
    for (int u = 0; u < n; ++u) {
      dist[u] = INF;
      in_queue[u] = 0;
      num_vis[u] = 0;
    }
    dist[s] = 0;
    in_queue[s] = 1;
    bool has_negative_cycle = false;
    std::queue<int> q;  q.push(s);
    while (not q.empty()) {
      int u = q.front();  q.pop();  in_queue[u] = 0;
      if (++num_vis[u] >= n)
        dist[u] = -INF, has_negative_cycle = true;
      for (auto &[v, c] : adj[u])
        if (dist[v] > dist[u] + c) {
          dist[v] = dist[u] + c;
          if (!in_queue[v]) {
            q.push(v);
            in_queue[v] = 1;
          }
        }
    }
    return has_negative_cycle;
  }
};

int main() {
  graph g(6);
  g.add_edge(0, 1, 0);
  g.add_edge(1, 2, 1);
  g.add_edge(2, 3, 1);
  g.add_edge(3, 1, -3);
  g.add_edge(0, 4, 4);
  g.add_edge(0, 5, 1);
  g.add_edge(5, 4, 1);

  g.spfa(0);

  for (int u = 0; u < 6; ++u)
    std::cout << g.dist[u] << " ";
  std::cout << "\n";

  return 0;
}
