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
	int h, w, k, ans = 0;
	cin >> h >> w >> k;
	vector<string> a(h);
	rep(i,h){
		cin >> a[i];
	}
	
	for(int bitw=0; bitw<(1<<w); bitw++){
		for(int bith=0; bith<(1<<h); bith++){
			int sum = 0;
			map<int, int> mh;
			map<int, int> mw;
			for(int i=0; i<h; i++){
				if(bith&(1<<i)){
					mh[i]++;
				}
			}
			for(int j=0; j<w; j++){
				if(bitw&(1<<j)){
					mw[j]++;
				}
			}
			rep(i,h){
				if(mh[i]>0) continue;
				rep(j,w){
					if(mw[j]>0) continue;
					if(a[i][j] == '#'){
						sum++;
					}
				}
			}
			if(sum == k) ans++;
		}
	}
	cout << ans << endl;
	return 0;
}