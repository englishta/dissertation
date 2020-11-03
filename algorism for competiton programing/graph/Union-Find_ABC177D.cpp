#include<bits/stdc++.h>
// Begin Header {{{
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using Graph = vector<vector<ll>>;
#define rep(i,n) for(ll i=0; i<n; i++)
#define loop(i, j, n) for(ll i=j; i<n; i++)
#define all(x) (x).begin(), (x).end()
constexpr int INF  = 0x3f3f3f40;
const long long mod=1e9+7;
const long double PI = acos(0);
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
	int N, M;
	cin >> N >> M;
	UnionFind UF(N);
	for(int i = 0; i<M; i++){
		int A, B;
		cin >> A >> B;
		A-=1; B-=1;
		UF.unit(A, B);
	}
	int ans = 0;
	rep(i, N){
		ans = max(ans, UF.size(i));
	}

	cout << ans << endl;
	
	return 0;
}