struct edge {
  int u, v, w;
  edge(int u, int v, int w) : u(u), v(v), w(w) {}
  const bool operator <(const edge &other) const {
    return w < other.w;  }  };
struct graph {
  int n;
  std::vector<edge> edges;
  graph(int n) : n(n) {}
  void add_edge(int u, int v, int w) {
    edges.push_back(edge(u, v, w));  } };
