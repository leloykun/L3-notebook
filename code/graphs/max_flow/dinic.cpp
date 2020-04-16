struct edge {
  int u, v;
  ll cap, flow;
  edge(int u, int v, ll cap, ll flow) :
    u(u), v(v), cap(cap), flow(flow) {}
};
struct flow_network {
  int n, s, t, *adj_ptr;
  ll *dist;
  vi *adj;
  std::vector<edge> edges;
  flow_network(int n, int s, int t) : n(n), s(s), t(t) {
    adj     = new std::vector<int>[n];
    adj_ptr = new int[n];
    dist    = new ll[n];
  }
  void add_edge(int u, int v, ll cap) {
    adj[u].push_back(edges.size());
    edges.push_back(edge(u, v, cap, 0LL));
    adj[v].push_back(edges.size());
    edges.push_back(edge(v, u, cap, 0LL));
  }
  ll res(edge &e) { return e.cap - e.flow; }
  bool make_level_graph() {
    for (int u = 0; u < n; ++u)   dist[u] = -1;
    dist[s] = 0;
    std::queue<int> q;     q.push(s);
    while (!q.empty()) {
      int u = q.front();  q.pop();
      for (int i : adj[u]) {
        edge e = edges[i];
        if (dist[e.v] < 0 and res(e)) {
          dist[e.v] = dist[u] + 1;
          q.push(e.v);
        }
      }
    }
    return dist[t] != -1;
  }
  bool is_next(int u, int v) {
    return dist[v] == dist[u] + 1;
  }
  ll dfs(int u, ll flow) {
    if (u == t)   return flow;
    for (int &i = adj_ptr[u]; i < adj[u].size(); ++i) {
      int j = adj[u][i];
      edge &e = edges[j], &er = edges[j^1];
      if (is_next(u, e.v) and res(e) > 0) {
        ll df = dfs(e.v, std::min(flow, res(e)));
        if (df > 0) {
          e.flow  += df;
          er.flow -= df;
          return df;
        }
      }
    }
    return 0;
  }
  ll calc_max_flow() {
    ll ans = 0;
    while (make_level_graph()) {
      for (int u = 0; u < n; ++u)   adj_ptr[u] = 0;
      while (ll df = dfs(s, INF))
        ans += df;
    }
    return ans;
  }
};
