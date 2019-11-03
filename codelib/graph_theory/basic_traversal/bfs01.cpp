#include <iostream>
#include <utility>
#include <vector>
#include <deque>

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

  void bfs01(int s) {
    for (int i = 0; i < n; ++i)
      dist[i] = INF;
    dist[s] = 0;

    std::deque<int> d;
    d.push_front(s);
    while (!d.empty()) {
      int u = d.front();
      d.pop_front();
      for (auto &e : adj[u]) {
        int v = e.first;
        int w = e.second;
        if (dist[v] > dist[u] + w) {
          dist[v] = dist[u] + w;
          if (w)
            d.push_back(v);
          else
            d.push_front(v);
        }
      }
    }
  }
}

int main() {

}
