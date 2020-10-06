#include<bits/stdc++.h>
using namespace std;
using ll = long long;

//n�ȉ��̑f�����i�[�����z���Ԃ��A�f���̐��́Aprime.size()�ŋ��܂�
//�v�Z��O(nloglogn)=n�̐��`����

vector<ll> sieve(ll n){
	vector<ll> prime;  //�f�����i�[����z��
	bool is_prime[n+1];  //is_prime[i]��true�Ȃ�i�͑f��

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
