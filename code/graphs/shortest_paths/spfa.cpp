struct edge {
  int v; long long cost;
  edge(int v, long long cost): v(v), cost(cost) {}
};
long long dist[N]; int vis[N]; bool inq[N];
void spfa(vector<edge*> adj[], int n, int s) {
  fill(dist, dist + n, LLONG_MAX);
  fill(vis, vis + n, 0);
  fill(inq, inq + n, false);
  queue<int> q; q.push(s);
  for (dist[s] = 0; !q.empty(); q.pop()) {
    int u = q.front(); inq[u] = false;
    if (++vis[u] >= n) dist[u] = LLONG_MIN;
    for (int i = 0; i < adj[u].size(); ++i) {
      edge& e = *adj[u][i];
      // uncomment below for min cost max flow
      // if (e.cap <= e.flow) continue;
      int v = e.v;
      long long w = vis[u] >= n ? 0LL : e.cost;
      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        if (!inq[v]) {
          inq[v] = true;
          q.push(v);
        }}}}}
