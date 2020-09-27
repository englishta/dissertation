#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;

int main() {
	long long N, M;
	cin >> N >> M;
	dsu d(N);

	for(long long i=0; i<M; ++i){
		long long a, b;
		cin >> a >> b;
		a--; b--;
		d.merge(a, b);
	}
	long long ans = d.groups().size();
	cout << ans-1 << endl;
	return 0;
}
