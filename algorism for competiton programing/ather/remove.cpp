#include<bits/stdc++.h>
// Begin Header {{{
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using Graph = vector<vector<ll>>;
#define rep(i,n) for(ll i=0; i<n; i++)
#define loop(i, j, n) for(ll i=j; i<n; i++)
#define all(x) (x).begin(), (x).end()
constexpr int INF  = 0x3f3f3f3f;
const long long mod=1e9+7;
const long double PI = acos(-1);
// }}} End Header

int main() {
	vector<int> a;
	rep(i,10){
		a.push_back(i);
		a.push_back(i);
	}
	for(auto x : a) cout << x << " ";
	cout << endl;
	//a.erase(remove(all(a), 2), a.end());
	//↑連結版
	//要素２をすべて削除する、ただし消した分だけ最後尾に要素が追加される
	auto itr = remove(all(a), 2);//itr = (removeした後のvectorの最終要素+1)のイテレータ
	a.erase(itr, a.end());//[itr,a.end())までをコンテナから消す,itr<=**消す**<a.end()
	for(auto x : a) cout << x << " ";

	/*ABC170-cで実際に使ってみると、
	int x, n;
	cin >> x >> n;
	vector<int> a(102);
	rep(i,102) a[i] = i;
	rep(i,n){
		int p;
		cin >> p;
		a.erase(remove(all(a), p), a.end());
	}
	pair<int, int> ans(9999, -1);
	rep(i,a.size()){
		int dif = abs(x-a[i]);
		ans = min(ans, pair<int, int>(dif, a[i]));
	}
	cout << ans.second << endl;
	*/
	return 0;
}