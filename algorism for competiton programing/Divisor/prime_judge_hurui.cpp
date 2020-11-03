#include<bits/stdc++.h>
using namespace std;
using ll = long long;

class Eratos{
    public:

    //1～Nまでの整数で素数判定、素因数分解が出来るプログラム
    //メンバ変数

    long long N;
    vector<ll> array;

    //コンストラクタ
    Eratos(long long size){
        N = size;
        array = vector<ll>(size+1, 1);
    }

    //篩を作成する、計算量O(NlogN)
    void make_sieve(){
        for(long long i=2; i<=N; i++){
            for(long long j=i; j<=N; j+=i){
                array[j]++;
            }
        }
    }

    template<class T> bool judge(T number){
        if(array[number] == 2) return true;//1とその数字の2つの約数だけ持つためtrue
        else return false;//false
    }
};
int main() {
	ll n, k;
	cin >> n >> k;
	Eratos t(n);
	t.make_sieve();
	if(t.judge(k)) cout << "Prime Number"<< endl;
	else cout << "Not Prime Number" << endl;
	
	return 0;
}