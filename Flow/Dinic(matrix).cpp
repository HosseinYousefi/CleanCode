#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(false);

const int N = 5005;

int d[N], ptr[N], cap[N][N], flow[N][N], s, t, n, m;

bool bfs(int lim) {
	queue<int> q;
	memset(d, -1, sizeof d);
	d[s] = 0;
	q.push(s);
	while (q.size() and d[t] == -1) {
		int v = q.front();
		q.pop();
		for (int i = 0; i < n; ++i)
			if (d[i] == -1 and cap[v][i] - flow[v][i] >= lim) {
				d[i] = d[v] + 1;
				q.push(i);
			}
	}
	memset(ptr, 0, sizeof ptr);
	return d[t] != -1;
}

bool dfs(int v, int lim) {
	if (v == t)
		return true;
	for (; ptr[v] < n; ++ptr[v])
		if (d[ptr[v]] == d[v] + 1 and cap[v][ptr[v]] - flow[v][ptr[v]] >= lim)
			if (dfs(ptr[v], lim)) {
				flow[v][ptr[v]] += lim;
				flow[ptr[v]][v] -= lim;
				return true;
			}
	return false;
}

int64_t dinic() {
	int64_t flow = 0;
	for (int lim = 1 << 30; lim; lim >>= 1)
		while (bfs(lim))
			while (dfs(s, lim))
				flow += lim;
	return flow;
}

int32_t main() { _
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int u, v, c;
		cin >> u >> v >> c;
		--u; --v;
		if (u != v) {
			cap[u][v] += c;
			cap[v][u] += c;
		}
	}
	s = 0;
	t = n - 1;
	cout << dinic() << endl;
}
