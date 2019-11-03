#include <iostream>
#include <utility>
#include <vector>
using namespace std;

const int MAX_N = 1000;
vector<int> adj[MAX_N];
vector<int> disc;
vector<int> low;
int TIME;

vector<pair<int, int> > bridges;
vector<int> articulation_points;

void bridges_artics (int u, int p) {
  disc[u] = low[u] = TIME++;
  int children = 0;
  bool has_low_child = false;
  for (int v : adj[u]) {
    if (disc[v] == -1) {
      bridges_artics(v, u);
      children++;

      if (disc[u] < low[v])
        bridges.push_back({u, v});
      if (disc[u] <= low[v])
        has_low_child = true;

      low[u] = min(low[u], low[v]);
    } else if (v != p)
      low[u] = min(low[u], disc[v]);
  }

  if ((p == -1 && children >= 2) || (p != -1 && has_low_child))
    articulation_points.push_back(u);
}

int main() {
  int N;  cin>>N;
  disc.assign(N, -1);
  low.assign(N, -1);

  TIME = 0;
  for (int u = 0; u < N; ++u)
    if (disc[u] == -1)
      bridges_artics(u, -1);

  cout<<"articulation points:\n";
  for (int u : articulation_points)
    cout<<u<<" ";
  cout<<"\n";

  cout<<"bridges\n";
  for (pair<int, int> bridge : bridges)
    cout<<bridge.first<<" "<<bridge.second<<"\n";
  cout<<"\n";

  return 0;
}
