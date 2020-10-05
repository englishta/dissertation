#include<bits/stdc++.h>
using namespace std;
using ll = long long;

class Eratos{
    public:

    //1�`N�܂ł̐����őf������A�f�����������o����v���O����
    //�����o�ϐ�

    long long N;
    vector<ll> array;

    //�R���X�g���N�^
    Eratos(long long size){
        N = size;
        array = vector<ll>(size+1, 1);
    }

    //⿂��쐬����A�v�Z��O(NlogN)
    void make_sieve(){
        for(long long i=2; i<=N; i++){
            for(long long j=i; j<=N; j+=i){
                array[j]++;
            }
        }
    }

    template<class T> bool judge(T number){
        if(array[number] == 2) return true;//1�Ƃ��̐�����2�̖񐔂���������true
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