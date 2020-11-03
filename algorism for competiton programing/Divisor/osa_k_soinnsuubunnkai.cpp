#include<bits/stdc++.h>
using namespace std;
using ll = long long;

class Eratos{
    public:

	vector<ll> array;//0`N-1‚Ü‚Å‚ÌÅ¬‚Ì‘fˆö”‚ğŠi”[‚·‚éƒŠƒXƒg
	ll N;

	Eratos(ll size){
		array = vector<ll>(size);
		N = size;
		iota(array.begin(), array.end(), 0);
	}

	vector<ll> make(){
		for(ll i=2; i*i<N; ++i){
			if(array[i] < i) continue;
			for(ll j=i*i; j<N; j+=i){
				if(array[j] == j) array[j] = i;
			}
		}
		return array;
	}

	map<ll, ll> factor(ll x){
		map<ll, ll> cnt;
		while(x>1){
			cnt[array[x]]++;
			x/=array[x];
		}
		return cnt;
	}

};
int main() {
	//ğŒ@k < n
	ll n, k;
	cin >> n >> k;
	Eratos Clas(n);
	Clas.make();
	for(auto x : Clas.factor(k)){
		cout << x.first << "**" << x.second << endl;
	}

	return 0;
}
	/*
	“ü—Í
	37 36

	o—Í
	K=
	2**2
	3**2
	*/