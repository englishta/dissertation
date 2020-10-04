#include<bits/stdc++.h>
//#include<atcoder/all>
// Begin Header {{{
//using namespace atcoder;
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using Graph = vector<vector<ll>>;
#define rep(i,n) for(ll i=0; i<n; i++)
#define loop(i, j, n) for(ll i=j; i<n; i++)
#define all(x) (x).begin(), (x).end()
#define UNIQUE(v) v.erase(unique(all(v)), v.end());
#define Sp(p) cout<<setprecision(25)<< fixed<<p<<endl;
constexpr int INF  = 0x3f3f3f3f;
const long long mod=1e9+7;
const long double PI = acos(-1);
template<class T, class S> inline bool chmax(T &a, const S &b) { if (a<b) { a = b; return 1; } return 0; }
template<class T, class S> inline bool chmin(T &a, const S &b) { if (a>b) { a = b; return 1; } return 0; }
#define INT(...)                                                                                                                                               \
    int __VA_ARGS__;                                                                                                                                           \
    IN(__VA_ARGS__)
#define LL(...)                                                                                                                                                \
    ll __VA_ARGS__;                                                                                                                                            \
    IN(__VA_ARGS__)
#define STR(...)                                                                                                                                               \
    string __VA_ARGS__;                                                                                                                                        \
    IN(__VA_ARGS__)
#define CHR(...)                                                                                                                                               \
    char __VA_ARGS__;                                                                                                                                          \
    IN(__VA_ARGS__)
#define DBL(...)                                                                                                                                               \
    double __VA_ARGS__;                                                                                                                                        \
    IN(__VA_ARGS__)
template<class T> void scan(T &a) { cin >> a; }
void IN() {}
template<class Head, class... Tail> void IN(Head &head, Tail &... tail){ scan(head); IN(tail...); }
// }}} End Header
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

    template<class T> bool p_judge(T number){
        if(array[number] == 2) return true;//1とその数字の2つの約数だけ持つためtrue
        else return false;//false
    }
};


int main() {
    LL(n, k);

    Eratos t(n);
    t.make_sieve();
    if(t.p_judge(k)) cout << k << " is Prime_number!!" << endl;
    else cout << "No" << endl;
    
	return 0;
}
