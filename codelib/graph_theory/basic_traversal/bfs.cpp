#include <iostream>
#include <vector>
#include <queue>

#define INF 1e9

struct graph {
  int n;
  std::vector<int> *adj;
  int *dist;
  graph(int n) {
    this->n = n;
    adj = new std::vector<int>[n];
    dist = new int[n];
  }

  void add_edge(int u, int v) {
    adj[u].push_back(v);
    //adj[v].push_back(u);
  }

  void bfs(int s) {
    for (int u = 0; u < n; ++u)
      dist[u] = INF;
    dist[s] = 0;
    std::queue<int> q;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v : adj[u]) {
        if (dist[v] == INF) {
          dist[v] = dist[u] + 1;
          q.push(v);
        }
      }
    }
  }
};

int main() {
  int N, M;  std::cin>>N>>M;
  graph g(N);
  for (int i = 0; i < M; ++i) {
    int u, v; std::cin>>u>>v;
    g.add_edge(u, v);
  }
  int s;  std::cin>>s;
  g.bfs(s);
  for (int u = 0; u < N; ++u)
    std::cout<<g.dist[u]<<" ";
  std::cout<<"\n";

  return 0;
}
