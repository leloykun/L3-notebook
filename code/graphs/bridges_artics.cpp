vii bridges;
vi adj[MAXN], disc, low, articulation_points;
int TIME;
void bridges_artics (int u, int p) {
  disc[u] = low[u] = TIME++;
  int children = 0;
  bool has_low_child = false;
  for (int v : adj[u]) {
    if (disc[v] == -1) {
      bridges_artics(v, u);
      children++;
      if (disc[u] < low[v])
        bridges.push_back({u, v});
      if (disc[u] <= low[v])
        has_low_child = true;
      low[u] = min(low[u], low[v]);
    } else if (v != p)
      low[u] = min(low[u], disc[v]);
  }
  if ((p == -1 && children >= 2) ||
      (p != -1 && has_low_child))
    articulation_points.push_back(u);
}
