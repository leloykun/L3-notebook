vii bridges;
vi adj[MAXN], disc(MAXN, -1), low(MAXN), articulation_points, st;
vvi comps;
int TIME;
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
