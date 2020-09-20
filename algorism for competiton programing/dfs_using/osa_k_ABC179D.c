#include<bits/stdc++.h>
// Begin Header {{{
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using Graph = vector<vector<ll>>;
#define rep(i,n) for(ll i=0; i<n; i++)
#define loop(i, j, n) for(ll i=j; i<n; i++)
#define all(x) (x).begin(), (x).end()
#define UNIQUE(v) v.erase(unique(all(v)), v.end());
#define Sp(p) cout<<setprecision(25)<< fixed<<p<<endl;
constexpr int INF  = 0x3f3f3f3f;
const long long mod=1e9+7;
const long double PI = acos(-1);
template<class T> bool chmax(T &a, const T &b) { if (a<b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T &a, const T &b) { if (a>b) { a = b; return 1; } return 0; }
// }}} End Header


int main() {
	ll n, ans = 0;
	cin >> n;
	vector<ll> sieve(n);
	loop(i, 2, n){
		for(ll j=i; j<n; j+=i){
			if(sieve[j] == 0) sieve[j]=i;
		}
	}
	
	for(ll c=1; c<n; c++){
		ll x = n-c;
		ll subans=1;
		map<ll, ll> tmp;

		while(x > 1){
			tmp[sieve[x]]++;
			x/=sieve[x];
		}
		for(auto x : tmp){
			subans*=(x.second+1);
		}
		ans+=subans;
	}
	cout << ans << endl;
	return 0;
}
