void biconnected_components(graph &adj,
                            std::vector<std::vector<int>> &comps,
                            graph &tree) {
	int n = adj.n;

	std::vector<int> num(n), low(n), art(n, 0), stk;

	std::function<void(int, int, int&)> dfs = [&](int u, int p, int &t) {
		num[u] = low[u] = ++t;
		stk.push_back(u);

		for (int v : adj[u]) if (v != p) {
			if (!num[v]) {
				dfs(v, u, t);
				low[u] = std::min(low[u], low[v]);

				if (low[v] >= num[u]) {
					art[u] = (num[u] > 1 || num[v] > 2);

					comps.push_back({u});
					while (comps.back().back() != v)
						comps.back().push_back(stk.back()), stk.pop_back();
				}
			}
			else low[u] = std::min(low[u], num[v]);
		}
	};

	for (int u = 0, t; u < n; ++u)
		if (!num[u]) dfs(u, -1, t = 0);

	// build the block cut tree
	std::vector<int> id(n);

	for (int u = 0; u < n; ++u)
		if (art[u]) id[u] = tree.add_node();

	for (auto &comp : comps) {
		int node = tree.add_node();
		for (int u : comp) {
			if (!art[u]) id[u] = node;
      else tree.add_edge(node, id[u]);
		}
	}

}
