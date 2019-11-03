#include <iostream>
#include <utility>
#include <vector>
#include <queue>

typedef std::pair<int, int> ii;

const int MAX_N = 100000;
std::vector<ii> temp[MAX_N];
std::vector<ii> adj[MAX_N];

int main() {
  int N = rand() % MAX_N + 1;
  int E = rand() % ((MAX_N) * (MAX_N - 1) / 2);
  for (int i = 0; i < E; ++i) {
    int u = rand() % N;
    int v = rand() % N;
    int w = rand();
    temp[u].push_back({v, w});
    temp[v].push_back({u, w});
  }

  std::vector<bool> vis(N, false);
  std::priority_queue<ii, std::vector<ii>, std::greater<ii> > pq;
  pq.push({0, 0});
  while (!pq.empty()) {
    int w = pq.top().first;
    int u = pq.top().second;
    vis[u] = true;
    pq.pop();

    for (auto e : temp[u]) {
      if (e.first == u)   continue;
      if (vis[e.first])   continue;
      adj[u].push_back({e.first, w});
      adj[e.first].push_back({u, w});
      pq.push({e.second, e.first});
    }
  }

  return 0;
}
