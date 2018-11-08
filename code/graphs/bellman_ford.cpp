#include "graph_template_adjlist.cpp"
void bellman_ford(int s, int n, int *dist, vii *adj) {
  for (int u = 0; u < n; ++u)
    dist[u] = INF;
  dist[s] = 0;
  for (int i = 0; i < n-1; ++i)
    for (int u = 0; u < n; ++u)
      for (auto &e : adj[u])
        if (dist[u] + e.second < dist[e.first])
          dist[e.first] = dist[u] + e.second;  }
// you can call this after running bellman_ford()
bool has_neg_cycle(int n, int *dist, vii *adj) {
  for (int u = 0; u < n; ++u)
    for (auto &e : adj[u])
      if (dist[e.first] > dist[u] + e.second)
        return true;
  return false;  }
