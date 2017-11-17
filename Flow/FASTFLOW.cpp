#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(false);
#define int long long

const int N = 5005;

struct edge {
	int from, to, cap, flow;
};

vector<edge> e;
vector<int> adj[N];
int d[N], ptr[N], s, t, n, m, cap[N][N];

void add_edge(int from, int to, int cap) {
	adj[from].push_back((int)e.size());
	e.push_back({from, to, cap, 0});
	adj[to].push_back((int)e.size());
	e.push_back({to, from, cap, cap});
}

bool bfs(int lim) {
	queue<int> q;
	memset(d, -1, sizeof d);
	d[s] = 0;
	q.push(s);
	while (q.size() and d[t] == -1) {
		int v = q.front();
		q.pop();
		for (int id: adj[v])
			if (d[e[id].to] == -1 and e[id].cap - e[id].flow >= lim) {
				d[e[id].to] = d[v] + 1;
				q.push(e[id].to);
			}
	}
	memset(ptr, 0, sizeof ptr);
	return d[t] != -1;
}

bool dfs(int v, int lim) {
	if (v == t)
		return true;
	for (; ptr[v] < adj[v].size(); ++ptr[v]) {
		int id = adj[v][ptr[v]];
		if (d[e[id].to] == d[v] + 1 and e[id].cap - e[id].flow >= lim)
			if (dfs(e[id].to, lim)) {
				e[id ^ 0].flow += lim;
				e[id ^ 1].flow -= lim;
				return true;
			}
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
		cap[u][v] += c;
		cap[v][u] += c;
	}
	for (int i = 0; i < n; ++i)
		for (int j = 1; j < n; ++j)
			if (cap[i][j])
				add_edge(i, j, cap[i][j]);
	s = 0;
	t = n - 1;
	cout << dinic() << endl;
}
