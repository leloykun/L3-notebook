struct edge {
  int u, v;
  ll cost, cap, flow;
  edge(int u, int v, ll cost, ll cap, ll flow) :
    u(u), v(v), cost(cost), cap(cap), flow(flow) {}
};
struct flow_network {
  int n, s, t, *par, *in_queue, *num_vis;
  ll *dist;
  std::vector<edge> edges;
  std::vector<int> *adj;
  flow_network(int n, int s, int t) : n(n), s(s), t(t) {
    adj = new std::vector<int>[n];
    par = new int[n];
    in_queue = new int[n];
    num_vis = new int[n];
    dist = new ll[n];
  }
  void add_edge(int u, int v, ll cap, ll cost) {
    adj[u].push_back(edges.size());
    edges.push_back(edge(u, v, cost, cap, 0LL));
    adj[v].push_back(edges.size());
    edges.push_back(edge(v, u, -cost, 0LL, 0LL));
  }
  ll res(edge &e) { return e.cap - e.flow; }
  bool spfa () {
    std::queue<int> q;  q.push(s);
    while (not q.empty()) {
      int u = q.front();  q.pop();  in_queue[u] = 0;
      if (++num_vis[u] >= n)  dist[u] = -INF;
      for (int i : adj[u]) {
        edge e = edges[i];
        if (res(e) <= 0)  continue;
        if (dist[e.v] > dist[u] + e.cost) {
          dist[e.v] = dist[u] + e.cost;
          par[e.v] = i;
          if (not in_queue[e.v]) {
            q.push(e.v);
            in_queue[e.v] = 1;
    } } } }
    return dist[t] != INF;
  }
  bool aug_path() {
    for (int u = 0; u < n; ++u) {
      par[u]  = -1;
      in_queue[u] = 0;
      num_vis[u] = 0;
      dist[u] = INF;
    }
    dist[s] = 0;
    in_queue[s] = 1;
    return spfa();
  }
  ii calc_max_flow() {
    ll total_cost = 0, total_flow = 0;
    while (aug_path()) {
      ll f = INF;
      for (int i = par[t]; i != -1; i = par[edges[i].u])
        f = std::min(f, res(edges[i]));
      for (int i = par[t]; i != -1; i = par[edges[i].u]) {
        edges[i].flow   += f;
        edges[i^1].flow -= f;
      }
      total_cost += f * dist[t];
      total_flow += f;
    }
    return {total_cost, total_flow};
  }
};
