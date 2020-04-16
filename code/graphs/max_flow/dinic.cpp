struct flow_network {
  int n, s, t, *adj_ptr, *par;
  ll *dist, **c, **f;
  vi *adj;
  flow_network(int n, int s, int t) : n(n), s(s), t(t) {
    adj     = new std::vector<int>[n];
    adj_ptr = new int[n];
    par  = new int[n];
    dist = new ll[n];
    c    = new ll*[n];
    f    = new ll*[n];
    for (int u = 0; u < n; ++u) {
      c[u] = new ll[n];
      f[u] = new ll[n];
      for (int v = 0; v < n; ++v)
        c[u][v] = f[u][v] = 0;
  } }
  void add_edge(int u, int v, ll cap, bool bi=false) {
    adj[u].push_back(v);
    adj[v].push_back(u);
    c[u][v] += cap;
    if (bi)  c[v][u] += cap;
  }
  ll res(int u, int v) { return c[u][v] - f[u][v]; }
  bool make_level_graph() {
    for (int u = 0; u < n; ++u)   dist[u] = -1;
    dist[s] = 0;
    std::queue<int> q;     q.push(s);
    while (!q.empty()) {
      int u = q.front();  q.pop();
      for (int v : adj[u]) {
        if (dist[v] < 0 and res(u, v)) {
          dist[v] = dist[u] + 1;
          q.push(v);
    } } }
    return dist[t] != -1;
  }
  bool is_next(int u, int v) {
    return dist[v] == dist[u] + 1;
  }
  bool dfs(int u) {
    if (u == t)   return true;
    for (int &i = adj_ptr[u]; i < adj[u].size(); ++i) {
      int v = adj[u][i];
      if (is_next(u, v) and res(u, v) > 0 and dfs(v)) {
        par[v] = u;
        return true;
    } }
    return false;
  }
  bool aug_path() {
    for (int u = 0; u < n; ++u) par[u] = -1;
    par[s] = s;
    return dfs(s);
  }
  ll calc_max_flow() {
    ll total_flow = 0;
    while (make_level_graph()) {
      for (int u = 0; u < n; ++u)   adj_ptr[u] = 0;
      while (aug_path()) {
        ll flow = INF;
        for (int u = t; u != s; u = par[u])
          flow = std::min(flow, res(par[u], u));
        for (int u = t; u != s; u = par[u])
          f[par[u]][u] += flow, f[u][par[u]] -= flow;
        total_flow += flow;
    } }
    return total_flow;
} };
