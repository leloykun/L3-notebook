struct graph {
  int n, logn, *ar, *dep, *first, *lg;
  ii **spt;
  vi *adj, euler;
  graph(int n, int logn=20) : n(n), logn(logn) {
    adj = new vi[n];
    ar = new int[n];
    dep = new int[n];
    first = new int[n];
  }
  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void dfs(int u, int p, int d) {
    dep[u] = d;
    first[u] = euler.size();
    euler.push_back(u);
    for (int v : adj[u]) {
      if (v != p) {
        dfs(v, u, d+1);
        euler.push_back(u);
  } } }
  void prep_lca(int root=0) {
    dfs(root, root, 0);
    int en = euler.size();
    lg = new int[en+1];
    lg[0] = lg[1] = 0;
    for (int i = 2; i <= en; ++i)
      lg[i] = lg[i >> 1] + 1;
    spt = new ii*[en];
    for (int i = 0; i < en; ++i) {
      spt[i] = new ii[lg[en]];
      spt[i][0] = {dep[euler[i]], i};
    }
    for (int k = 1; k < lg[en]; ++k)
      for (int i = 0; i + (1 << (k-1)) < en; ++i)
        spt[i][k] = std::min(spt[i][k-1],
                             spt[i + (1 << (k-1))][k-1]);
  }
  int lca(int u, int v) {
    int a = first[u], b = first[v];
    if (a > b)    std::swap(a, b);
    int k = lg[b - a], ba = b - (1 << k) + 1;
    return euler[std::min(spt[a][k], spt[ba][k]).second];
} };
