#include <iostream>
#include <cstring>
#include <vector>

std::vector<int> adj[100001];
char ans[100001];
int marked[100001];
int sub_size[100001];

void dfs(int u, int p) {
  sub_size[u] = 1;
  for (int v : adj[u]) {
    if (v != p and !marked[v]) {
      dfs(v, u);
      sub_size[u] += sub_size[v];
    }
  }
}

int find_centroid(int u, int p, int n) {
  bool is_centroid = true;

  int heavy_child = -1;

  for (int v : adj[u]) {
    if (v != p and !marked[v]) {
      if (sub_size[v] > n/2)
        is_centroid = false;

      if (heavy_child = -1 or sub_size[v] > sub_size[heavy_child])
        heavy_child = v;
    }
  }

  if (is_centroid and n - sub_size[u] <= n/2)
    return u;
  return find_centroid(heavy_child, u, n);
}

int find_centroid(int s) {
  dfs(s, -1);

  int u = find_centroid(s, -1, sub_size[s]);
  marked[u] = true;
  return u;
}

void decompose_tree(int s, int dep) {
  int u = find_centroid(s);
  ans[u] = 'A' + dep;

  for (int v : adj[u])
    if (!marked[v])
    decompose_tree(v, dep+1);
}

int main () {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  int N;  std::cin>>N;
  for (int i = 0; i < N-1; ++i) {
    int u, v;   std::cin>>u>>v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  memset(marked, 0, sizeof(marked));
  memset(sub_size, 0, sizeof(sub_size));
  decompose_tree(1, 0);

  for (int u = 1; u <= N; ++u)
    std::cout<<ans[u]<<" ";

  return 0;
}
