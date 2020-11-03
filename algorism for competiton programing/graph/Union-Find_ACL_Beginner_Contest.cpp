#include<bits/stdc++.h>
#include<atcoder/all>
// Begin Header {{{
using namespace atcoder;
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
#define INT(...)                                                                                                                                               \
    int __VA_ARGS__;                                                                                                                                           \
    IN(__VA_ARGS__)
#define LL(...)                                                                                                                                                \
    ll __VA_ARGS__;                                                                                                                                            \
    IN(__VA_ARGS__)
#define STR(...)                                                                                                                                               \
    string __VA_ARGS__;                                                                                                                                        \
    IN(__VA_ARGS__)
#define CHR(...)                                                                                                                                               \
    char __VA_ARGS__;                                                                                                                                          \
    IN(__VA_ARGS__)
#define DBL(...)                                                                                                                                               \
    double __VA_ARGS__;                                                                                                                                        \
    IN(__VA_ARGS__)
template<class T> void scan(T &a) { cin >> a; }
void IN() {}
template<class Head, class... Tail> void IN(Head &head, Tail &... tail){ scan(head); IN(tail...); }
// }}} End Header

class UnionFind{
	public:
	vector<int> r;

	UnionFind(int N){
		r = vector<int>(N, -1);
	}

	int root(int x){
		if(r[x] < 0) return x;
		return r[x] = root(r[x]);
	}

	bool unit(int x, int y){
		x = root(x);
		y = root(y);
		if(x == y) return false;
		if(r[x] > r[y]) swap(x, y);
		r[x] += r[y];
		r[y] = x;
		return true;
	}

	int size(int x){
		return -r[root(x)];
	}

};

int main() {
	ll ans = 0;
	LL(N, M);
	UnionFind UF(N);

	rep(i,M){
		LL(a, b);
		a--;
		b--;
		UF.unit(a, b);
	}
	rep(i,N){
		if(UF.root(i) == i) ans++;
		//if(UF.r[i] < 0) ans++;
	}

	cout << ans-1 << endl;
	return 0;
}
