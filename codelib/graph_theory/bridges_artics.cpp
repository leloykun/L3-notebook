#include <iostream>
#include <vector>
#include <utility>

typedef std::pair<int, int> ii;
typedef std::vector<ii> vii;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

const int MAXN = 1e5;

vii bridges;
vi adj[MAXN], disc(MAXN, -1), low(MAXN), articulation_points, st;
vvi comps;
int TIME;
void add_edge(int u, int v) {
  adj[u].push_back(v);
  adj[v].push_back(u);
}
void bridges_artics (int u, int p) {
  disc[u] = low[u] = TIME++;
  st.push_back(u);
  int children = 0;
  bool has_low_child = false;
  for (int v : adj[u]) {
    if (disc[v] == -1) {
      bridges_artics(v, u);
      children++;
      if (disc[u] < low[v])
        bridges.push_back({u, v});
      if (disc[u] <= low[v]) {
        has_low_child = true;
        
        comps.push_back({u});
        while (comps.back().back() != v and !st.empty()) {
          comps.back().push_back(st.back());
          st.pop_back();
        }
      }
      low[u] = std::min(low[u], low[v]);
    } else if (v != p)
      low[u] = std::min(low[u], disc[v]);
  }
  if ((p == -1 && children >= 2) ||
      (p != -1 && has_low_child))
    articulation_points.push_back(u);
}

int main() {
  add_edge(0, 1);
  add_edge(1, 2);
  add_edge(2, 3);
  add_edge(2, 0);

  TIME = 0;
  bridges_artics(0, -1);

  std::cout << "articulation_points:\n";
  for (int u : articulation_points)
    std::cout << u << " ";
  std::cout << "\n";

  for (auto v : comps) {
    for (int u : v)
      std::cout << u << " ";
    std::cout << "\n";
  }

  return 0;
}
