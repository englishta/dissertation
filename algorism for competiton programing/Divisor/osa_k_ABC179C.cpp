#include<bits/stdc++.h>
//#include<atcoder/all>
// Begin Header {{{
//using namespace atcoder;
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

std::vector<ll> Eratos_sieve(ll n){
	//[0, n]のインデックスに対して、最小の素因数を記録するリスト
	vector<ll> sieve(n);
	iota(sieve.begin(), sieve.end(), 0);
	for(ll i=2; i*i<n; ++i){
		if(sieve[i] < i) continue;
		for(ll j=i*i; j<n; j+=i){
			if(sieve[j] == j) sieve[j] = i;
		}
	}
	return sieve;
}
int main() {
	ll n, ans = 0;
	cin >> n;
	vector<ll> sieve = Eratos_sieve(n);
	
	for(ll c=1; c<n; c++){
		ll x = n-c;
		ll divisors=1;
		map<ll, ll> cnt;

		while(x > 1){
			cnt[sieve[x]]++;
			x/=sieve[x];
		}
		for(auto x : cnt){
			divisors*=(x.second+1);
		}
		ans+=divisors;
	}
	cout << ans << endl;
	return 0;
}
