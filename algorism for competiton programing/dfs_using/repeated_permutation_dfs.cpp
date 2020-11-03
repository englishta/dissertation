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
template <class T>void UNIQUE(vector<T> &x){
	sort(all(x));
	x.erase(unique(all(x)), x.end());
}

// }}} End Header
//bfsを使った重複順列5P3
vector<int> buf;

void dfs(int i, int size, int start, int end){
	if(i == size){
		for(int i = 0; i<buf.size(); ++i){
			cout << buf[i];
		}
		cout << endl;
	}else{
		for(int j = start; j<=end; ++j){
			buf[i] = j;
			dfs(i+1, size, start, end);
		}
	}
}
int main() {
	//1～5の数字から重複ありで3つ選ぶ
	int size = 3;
	int start = 1;
	int end = 5;

	buf.resize(size);
	dfs(0, size, start, end);

	return 0;
}
