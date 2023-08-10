#include<vector>
#include<iostream>
using namespace std;


const int N = 2005;
ll a[N];
int b[N];

bool cmp(int x, int y){
	return a[x] > a[y];
}

int main(){
	int n, m, j, k;
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> m >> j >> k;
		queue<int>q;
		for(int i = 1; i <= m; i++){
			cin >> b[i];
			q.push(b[i]);
		}
		vi id;
		for(int i = 1; i <= m; i++){
			cin >> a[i];
			id.pb(i);
		}
		sort(id.begin(), id.end(), cmp);
		int id1 = id[j - 1], id2 = id[k - 1];
		int res = 0;
		while(SZ(q) > 1){
			int x = q.front();
			q.pop();
			int y = q.front();
			q.pop();
			if(x == id1 && y == id2 || x == id2 && y == id1)
				res = 1;
			if(a[x] > a[y])
				q.push(x);
			else
				q.push(y);
		}
		if(res)
			cout << "YQST\n";
		else
			cout << "...\n";
	}
}
