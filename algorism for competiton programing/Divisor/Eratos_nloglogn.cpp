#include<bits/stdc++.h>
using namespace std;
using ll = long long;

//nΘΊΜfπi[΅½zρπΤ·AfΜΝAprime.size()Εάι
//vZΚO(nloglogn)=nΜό`Τ

vector<ll> sieve(ll n){
	vector<ll> prime;  //fπi[·ιzρ
	bool is_prime[n+1];  //is_prime[i]ͺtrueΘηiΝf

	for(ll i=0; i<=n; i++) is_prime[i] = true;
	is_prime[0] = is_prime[1] = false;

	for(ll i=2; i<=n; i++){
		if(is_prime[i]){
			prime.push_back(i);
			for(ll j=2*i; j<=n; j+=i) is_prime[j] = false;
		}
	}
	return prime;
}


int main() {
	ll n;
	cin >> n;
	vector<ll> array = sieve(n);
	cout << array.size() << endl;
	for(auto x : array) cout << x << endl;
	return 0;
}
