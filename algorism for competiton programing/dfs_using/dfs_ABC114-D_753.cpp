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
template <class T>void UNIQUE(vector<T> &x){
	sort(all(x));
	x.erase(unique(all(x)), x.end());
}

// }}} End Header
ll n;
ll dfs(string s){
	ll ans = 0;
	string list = "753";

	if((int)s.size() > 0){
		if(stoll(s) > n) return ans;
		bool ok = true;
		for(auto x : list) if(s.find(x) == string::npos) ok = false;
		if(ok) ans++;
	}
	for(auto x : list){
		s.push_back(x);
		ans+=dfs(s);
		s.pop_back();
	}
	return ans;
}


int main() {
	cin >> n;
	string s = "";
	cout << dfs(s) << endl;
	return 0;
}