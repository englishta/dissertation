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
	int n, m, k;
	cin >> n >> m >> k;
	vector<ll> a(n);
	vector<ll> b(m);
	rep(i,n) cin >> a[i];
	rep(i,m) cin >> b[i];
	ll t = 0;
	rep(i,m) t+=b[i];//t�́AB�̖{�I�̖{��S�ēǂނ̂ɂ����鎞��
	int j = m;
	int ans = 0;
	rep(i, n+1){
		while(j>0 && t>k){
			--j;
			t-=b[j];
		}
		if(t>k) break;//b[i]�̗v�f���[���ł����Ԃ����𒴂��Ă��܂��ꍇ�A
		if(ans < i+j) ans = i+j;
		//ans = max(ans, i+j);
		if(i >= n) break;//a[n]�ɒB������I���A
		t+=a[i];//�{�IA�̓ǂޖ{������₷�A���Ԃ����̕�����
	}
	cout << ans << endl;
 	return 0;
}
