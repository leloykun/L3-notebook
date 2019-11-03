#include <iostream>
#include <utility>
#include <vector>
#include <queue>

#define INF 1e9
typedef std::pair<int, int> ii;
typedef std::vector<ii> vii;

struct graph {
  int n;
  vii *adj;
  int *dist;
  graph(int n) {
    this->n = n;
    adj = new vii[n];
    dist = new int[n];
  }

  void add_edge(int u, int v, int w) {
    adj[u].push_back({v, w});
    // adj[v].push_back({u, w});
  }

  void dijkstra(int s) {
    for (int u = 0; u < n; ++u)
      dist[u] = INF;
    dist[s] = 0;
    std::priority_queue<ii, vii, std::greater<ii> > pq;
    pq.push({0, s});
    while (!pq.empty()) {
      int u = pq.top().second;
      int d = pq.top().first;
      pq.pop();
      if (dist[u] < d)
        continue;
      dist[u] = d;
      for (auto &e : adj[u]) {
        int v = e.first;
        int w = e.second;
        if (dist[v] > dist[u] + w) {
          dist[v] = dist[u] + w;
          pq.push({dist[v], v});
        }
      }
    }
  }
};

int main() {
  int N, M;   std::cin>>N>>M;
  int s, t;   std::cin>>s>>t;
  graph g(N);
  for (int i = 0; i < M; ++i) {
    int u, v, w;  std::cin>>u>>v>>w;
    g.add_edge(u, v, w);
  }
  g.dijkstra(s);
  std::cout << g.dist[t] << "\n";

  return 0;
}
