#include <iostream>
#include <utility>
#include <vector>
#include <queue>

typedef std::pair<int, int> ii;
typedef std::pair<int, ii> iii;

int MAX_N = 100000;
std::vector<ii> adj[100000];

struct union_find {
  std::vector<int> p;     union_find(int n) : p(n, -1) { }
  int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
  bool unite(int x, int y) {
    int xp = find(x), yp = find(y);
    if (xp == yp)       return false;
    if (p[xp] > p[yp])  std::swap(xp, yp);
    p[xp] += p[yp]; p[yp] = xp;
    return true;
  }
  int size(int x) { return -p[find(x)]; }
};


int main() {
  int N = rand() % MAX_N + 1;
  int E = rand() % ((MAX_N) * (MAX_N - 1) / 2);

  std::priority_queue<iii, std::vector<iii>, std::greater<iii> > pq;
  for (int i = 0; i < E; ++i) {
    int u = rand() % N;
    int v = rand() % N;
    int w = rand();
    pq.push({w, {u, v}});
  }

  union_find uf(N);
  while (!pq.empty()) {
    auto node = pq.top();   pq.pop();
    int w = node.first;
    int u = node.second.first;
    int v = node.second.second;
    if (uf.unite(u, v)) {
      adj[u].push_back({v, w});
      adj[v].push_back({u, w});
      std::cout<<u<<" "<<v<<" "<<w<<"\n";
    }
  }

  return 0;
}
