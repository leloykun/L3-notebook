struct flow_network {
  int n, s, t, *adj_ptr, *dist, *par, **c, **f;
  vi *adj;
  flow_network(int n, int s, int t) : n(n), s(s), t(t) {
    adj = new std::vector<int>[n];
    adj_ptr = new int[n];
    dist = new int[n];
    par = new int[n];
    c = new int*[n];
    f = new int*[n];
    for (int i = 0; i < n; ++i) {
      c[i] = new int[n];
      f[i] = new int[n];
      for (int j = 0; j < n; ++j)
        c[i][j] = f[i][j] = 0;
    }
  }
  void add_edge(int u, int v, int w) {
    adj[u].push_back(v);
    adj[v].push_back(u);
    c[u][v] += w;
  }
  int res(int i, int j) { return c[i][j] - f[i][j]; }
  void reset(int *ar, int val) {
    for (int i = 0; i < n; ++i)
      ar[i] = val;
  }
  bool make_level_graph() {
    reset(dist, -1);
    std::queue<int> q;
    q.push(s);
    dist[s] = 0;
    while (!q.empty()) {
      int u = q.front();  q.pop();
      for (int v : adj[u]) {
        if (res(u, v) > 0 and dist[v] == -1) {
          dist[v] = dist[u] + 1;
          q.push(v);
        }
      }
    }
    return dist[t] != -1;
  }
  bool next(int u, int v) {
    return dist[v] == dist[u] + 1;
  }
  bool dfs(int u) {
    if (u == t)   return true;
    for (int &i = adj_ptr[u]; i < adj[u].size(); ++i) {
      int v = adj[u][i];
      if (next(u, v) and res(u, v) > 0 and dfs(v)) {
        par[v] = u;
        return true;
      }
    }
    dist[u] = -1;
    return false;
  }
  bool aug_path() {
    reset(par, -1);
    par[s] = s;
    return dfs(s);  }
  int calc_max_flow() {
    int ans = 0;
    while (make_level_graph()) {
      reset(adj_ptr, 0);
      while (aug_path()) {
        int flow = INF;
        for (int u = t; u != s; u = par[u])
          flow = std::min(flow, res(par[u], u));
        for (int u = t; u != s; u = par[u])
          f[par[u]][u] += flow, f[u][par[u]] -= flow;
        ans += flow;
      }
    }
    return ans;
  }
};
