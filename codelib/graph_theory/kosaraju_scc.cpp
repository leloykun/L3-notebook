#include <iostream>
#include <vector>

const int MAXN = 100000;

int N, E;

std::vector<int> adj[2][MAXN];
std::vector<bool> vis;

std::vector<std::vector<int> > sccs;

void dfs(int u, int p, int dir, std::vector<int> &ar) {
  vis[u] = true;
  for (int v : adj[dir][u])
    if (!vis[v] && v != p)
      dfs(v, u, dir, ar);
  ar.push_back(u);
}

void kosaraju() {
  std::vector<int> topo;
  vis.assign(N, false);
  for (int u = 0; u < N; ++u)
    if (!vis[u])
      dfs(u, -1, 0, topo);

  vis.assign(N, false);
  for (int i = N-1; i >= 0; --i) {
    if (!vis[topo[i]]) {
      sccs.push_back({});
      dfs(topo[i], -1, 1, sccs.back());
    }
  }
}

int main() {
  std::cin>>N>>E;
  for (int u = 0; u < N; ++u) {
    adj[0][u].clear();
    adj[1][u].clear();
  }

  for (int i = 0; i < E; ++i) {
    int u, v;   std::cin>>u>>v;
    adj[0][u].push_back(v);
    adj[1][v].push_back(u);
  }

  kosaraju();

  std::cout<<"sccs: \n";
  for (std::vector<int> scc : sccs) {
    for (int u : scc)
      std::cout<<u<<" ";
    std::cout<<"\n";
  }

  return 0;
}
