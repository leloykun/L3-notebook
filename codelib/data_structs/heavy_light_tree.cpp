struct heavy_light_tree {
  int n;
  std::vector<int> *adj;
  segtree *segment_tree;

  int *par;
  int *heavy;
  int *dep;
  int *path_root;
  int *pos;

  heavy_light_tree(int n) {
    this->n = n;
    this->adj = new std::vector<int>[n];
    segment_tree = new segtree(0, n-1);

    par = new int[n];
    heavy = new int[n];
    dep = new int[n];
    path_root = new int[n];
    pos = new int[n];
  }

  void add_edge(int u, int v) {
    adj[u].push_back(v);
    // adj[v].push_back(u);
  }

  void build(int root) {
    for (int u = 0; u < n; ++u)
      heavy[u] = -1;
    par[root] = root;
    dep[root] = 0;
    dfs(root);
    for (int u = 0, p = 0; u < n; ++u) {
      //std::cout<<"build: "<<u<<" ";
      if (par[u] == -1 or heavy[par[u]] != u) {
        for (int v = u; v != -1; v = heavy[v]) {
          //std::cout<<v<<" ";
          path_root[v] = u;
          pos[v] = p++;
        }
      }
      //std::cout<<"\n";
    }
  }

  int dfs(int u) {
    //std::cout<<"hld_dfs "<<u<<"\n";
    int sz = 1;
    int max_subtree_sz = 0;
    for (int v : adj[u]) {
      if (v != par[u]) {
        par[v] = u;
        dep[v] = dep[u] + 1;
        int subtree_sz = dfs(v);
        if (max_subtree_sz < subtree_sz) {
          max_subtree_sz = subtree_sz;
          heavy[u] = v;
        }
        sz += subtree_sz;
      }
    }
    return sz;
  }

  int query(int u) {
    return segment_tree->sum(pos[u], pos[u]);
  }

  void update(int u, int v, int c) {
    for (; path_root[u] != path_root[v]; v = par[path_root[v]]) {
      if (dep[path_root[u]] > dep[path_root[v]])
        std::swap(u, v);
      segment_tree->increase(pos[path_root[v]], pos[v], c);
    }

    segment_tree->increase(pos[u], pos[v], c);
  }
};
