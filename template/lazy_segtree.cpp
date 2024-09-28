#include<bits/stdc++.h>
using namespace std;
int n, m, a[100001];
long long f[400001], v[400001];

void buildtree(int k, int l, int r) {
	v[k] = 0;
	if(l == r) {
		f[k] = a[l];
		return ;
	}
	int mid = (l + r) >> 1;
	buildtree(k * 2, l, mid);
	buildtree(k * 2 + 1, mid + 1, r);
	f[k] = f[k * 2] + f[k * 2 + 1];
}

void insert(int k, int l, int r, int x, int y, long long z) {
	if(l == x && r == y) {
		v[k] += z;
		return ;
	}
	
	if(v[k]) {
		v[k * 2] += v[k];
		v[k * 2 + 1] += v[k];
		v[k] = 0;
	}

	int mid = (l + r) >> 1;
	if(y <= mid) {
		insert(k * 2, l, mid, x, y, z);
	} else if(x > mid) {
		insert(k * 2 + 1, mid + 1, r, x, y, z);
	} else {
		insert(k * 2, l, mid, x, mid, z);
		insert(k * 2 + 1, mid + 1, r, mid + 1, y, z);
	}
	f[k] = f[k * 2] + v[k * 2] * (mid - l + 1) + f[k * 2 + 1] + v[k * 2 + 1] * (r - mid);
}

long long calc(int k, int l, int r, int x, int y) {
	if(l == x && r == y) return f[k] + v[k] * (r - l + 1);
	if(v[k]) {
		v[k * 2] += v[k];
		v[k * 2 + 1] += v[k];
		v[k] = 0;
	}

	int mid = (l + r) >> 1;
	long long res = 0;
	if(y <= mid) {
		res = calc(k * 2, l, mid, x, y);
	} else if(x > mid) {
		res = calc(k * 2 + 1, mid + 1, r, x, y);
	} else {
		res = calc(k * 2, l, mid, x, mid) + calc(k * 2 + 1, mid + 1, r, mid + 1, y);
	}
	
	f[k] = f[k * 2] + v[k * 2] * (mid - l + 1) + f[k * 2 + 1] + v[k * 2 + 1] * (r - mid);
	return res;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	buildtree(1, 1, n);

	for(int i = 1; i <= m; i ++) {
		int t;
		scanf("%d", &t);
		if(t == 1) {
			int x, y;
			long long z;
			scanf("%d%d%lld", &x, &y, &z);
			insert(1, 1, n, x, y, z);
		} else {
			int x, y;
			scanf("%d%d", &x, &y);
			printf("%d\n", calc(1, 1, n, x, y));
		}
	}
	return 0;
}
