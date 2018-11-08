#include "graph_template_adjlist.cpp"
void dijkstra(int s, int n, int *dist, vii *adj) {
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
        pq.push({dist[v], v});  }  }  }  }
