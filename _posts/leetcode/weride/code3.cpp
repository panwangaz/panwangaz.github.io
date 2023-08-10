#include<vector>
#include<iostream>
using namespace std;

//第三题
int main(){
	int n, m, k;
	cin >> n >> m >> k;
	ll L = 1, R = 1ll * n * m;
	while(L < R){
		ll mid = (L + R + 1) / 2;
		ll cnt = 0;
		for(int i = 1; i <= n; i++){
			ll x = mid / i;
			if(mid % i != 0)
				x++;
			if(x <= m)
				cnt += (m - x + 1);
		}
		if(cnt >= k)
			L = mid;
		else
			R = mid - 1;
	}
	cout << L;
}
