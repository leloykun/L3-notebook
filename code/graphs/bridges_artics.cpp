struct graph {
  int n, *disc, *low, TIME;
  vi *adj, stk, articulation_points;
  vii bridges;
  vvi comps;
  graph (int n) {
    this->n = n;
    adj = new vi[n];
    disc = new int[n];
    low = new int[n];
  }
  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void _bridges_artics(int u, int p) {
    disc[u] = low[u] = TIME++;
    stk.push_back(u);
    int children = 0;
    bool has_low_child = false;
    for (int v : adj[u]) {
      if (disc[v] == -1) {
        _bridges_artics(v, u);
        children++;
        if (disc[u] < low[v])
          bridges.push_back({u, v});
        if (disc[u] <= low[v]) {
          has_low_child = true;
          comps.push_back({u});
          while (comps.back().back() != v and !stk.empty()) {
            comps.back().push_back(stk.back());
            stk.pop_back();
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
  void bridges_artics(int root) {
    for (int u = 0; u < n; ++u)
      disc[u] = -1;
    stk.clear();
    articulation_points.clear();
    bridges.clear();
    comps.clear();
    TIME = 0;
    _bridges_artics(root, -1);
  }
  graph generate_block_cut_tree() {
    int bct_n = articulation_points.size() + comps.size();
    std::vector<int> block_id(n), is_art(n, 0);
    graph tree(bct_n);
    for (int i = 0; i < articulation_points.size(); ++i) {
      block_id[articulation_points[i]] = i;
      is_art[articulation_points[i]] = 1;
    }
    for (int i = 0; i < comps.size(); ++i) {
      int id = i + articulation_points.size();
      for (int u : comps[i])
        if (is_art[u])
          tree.add_edge(block_id[u], id);
        else
          block_id[u] = id;
    }
    return tree;
  }
};
