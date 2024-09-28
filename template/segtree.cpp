#include<bits/stdc++.h>
using namespace std;
int n, m, a[500001], f[2000001];

void buildtree(int k, int l, int r) {
	if(l == r) {
		f[k] = a[l];
		return ;
	}
	int mid = (l + r) >> 1;
	buildtree(k * 2, l, mid);
	buildtree(k * 2 + 1, mid + 1, r);
	f[k] = f[k * 2] + f[k * 2 + 1];
}

void add(int k, int l, int r, int x, int y) {
	if(l == r) return ;
	f[k] += y;
	int mid = (l + r) >> 1;
	if(x <= m) {
		add(k * 2, l, mid, x, y);
	} else {
		add(k * 2 + 1, mid + 1, r, x, y);
	}
}

int calc(int k, int l, int r, int s, int t) {
	if(l == s && r == t) return f[k];
	int mid = (l + r) >> 1;
	if(t <= mid) {
		return calc(k * 2, l, mid, s, t);
	} else if(s > mid) {
		return calc(k * 2 + 1, mid + 1, r, s, t);
	} else {
		return calc(k * 2, l, mid, s, mid) + calc(k * 2 + 1, mid + 1, r, mid + 1, t);
	}
}



int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	buildtree(1, 1, n);

	for(int i = 1; i <= m; i ++) {
		int t, x, y;
		scanf("%d%d%d", &t, &x, &y);
		if(t == 1) add(1, 1, n, x, y);
		else printf("%d\n", calc(1, 1, n, x, y));	
	}
}
