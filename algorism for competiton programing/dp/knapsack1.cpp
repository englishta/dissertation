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
template<class T, class S> inline bool chmax(T &a, const S &b) { if (a<b) { a = b; return 1; } return 0; }
template<class T, class S> inline bool chmin(T &a, const S &b) { if (a>b) { a = b; return 1; } return 0; }
template<class T> void scan(T &a) { cin >> a; }
void IN() {}
template<class Head, class... Tail> void IN(Head &head, Tail &... tail){ scan(head); IN(tail...); }
// }}} End Header
int main() {
	ll n, W;
	IN(n, W);
	vector<ll> w(n), v(n);
	rep(i,n) cin >> w[i] >> v[i];
	ll dp[n+1][W+1];
	rep(j,W+1) dp[0][j] = 0;


	for(ll i=0; i<n; i++){
		for(ll j=0; j<=W; j++){
			if(j-w[i]>=0) dp[i+1][j] = max(dp[i][j-w[i]]+v[i], dp[i][j]);
			else dp[i+1][j] = dp[i][j];
		}
	}
	cout << dp[n][W] << endl;
	return 0;
}
