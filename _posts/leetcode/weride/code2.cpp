#include<vector>
#include<iostream>
using namespace std;

//第二题
const int mod = 1e9 + 7;
const int N = 4e5 + 5;

int lowbit(int x){
	return x & (-x);
}

struct BIT{
	int n;
	ll sum1[N], sum2[N];
	void update(int L, int R, ll k){
		int x = L;
		while(L <= n){
			sum1[L] += k;
			sum2[L] += 1ll * k * x % mod;
			L += lowbit(L);
			sum1[L] %= mod, sum2[L] %= mod;
		}
		R++, x = R;
		while(R <= n){
			sum1[R] -= k;
			sum2[R] -= 1ll * k * x % mod;
			R += lowbit(R);
			sum1[R] = (sum1[R] + mod) % mod;
			sum2[R] = (sum2[R] + mod) % mod;
		}
	}
	ll get_sum(int L, int R){
		ll ans = 0;
		int x = R;
		while(R > 0){
			ans += 1ll * (x + 1) * sum1[R] % mod - sum2[R];
			ans = (ans + mod) % mod;
			R -= lowbit(R);
		}
		L--, x = L;
		while(L > 0){
			ans -= 1ll * (x + 1) * sum1[L] % mod - sum2[L];
			ans = (ans % mod + 2 * mod) % mod;
			L -= lowbit(L);
		}
		return ans;
	}
}bit[15];

ll dp[15][N];
char s[N], t[15];
int k;

int main(){
	for(int i = 0; i < 15; i++)
		bit[i].n = 4e5;
	scanf("%s", s + 1);
	scanf("%s", t + 1);
	scanf("%d", &k);
	int n = strlen(s + 1), m = strlen(t + 1);
	int L = 2e5;
	//dp[0][L + 0] = 1;
	bit[0].update(L, L, 1);
	for(int p = 1; p <= n; p++){
		for(int i = 1; i <= m; i++){
			if(s[p] != t[i])
				continue;
			ll tmp = 0;
			//for(int kg = 0; kg <= k; kg++)
			//	tmp = (tmp + dp[i - 1][L + kg]) % mod;
			tmp = bit[i - 1].get_sum(L, L + k);
			//dp[i][L - 1] = (dp[i][L - 1] + tmp) % mod;
			bit[i].update(L - 1, L - 1, tmp);
		}
		L--;
		//dp[0][L] = 1;
		bit[0].update(L, L, 1);
		//dp[0][L + 1] = 0;
		bit[0].update(L + 1, L + 1, -1);
	}
	ll ans = 0;
	//for(int i = 0; i < N; i++)
		//ans = (ans + dp[m][i]) % mod;
	ans = bit[m].get_sum(1, 4e5);
	cout << ans;
}
