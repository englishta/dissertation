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

class Permu_tation{
    public:

    long long array_size;
    vector<long long> perm;
    vector<long long> array;
    vector<bool> used;

    //コンストラクタ
    Permu_tation(long long N){
        array_size = N;
        array = vector<long long>(N);
        used = vector<bool>(N, false);
    }

    //入力の関数,昇順ソートの関数
    void input(){
        for(ll i=0; i<array_size; ++i) cin >> array[i];
        sort(array.begin(), array.end());
    }

    void permutation(long long pos){
        if(pos >= array_size){
            for(auto x : perm){
                cout << x << " ";
            }
            cout << endl;
            return;
        }

        for(auto x : array){
            if(used[x] == true) continue;
            used[x] = true;
            perm.push_back(x);
            permutation(pos+1);
            perm.pop_back();
            used[x]  = false;
        }
    }
};

void Main(){
    //配列の要素数を入力
    LL(N);
    Permu_tation pt(N);
    pt.input();
    pt.permutation(0);
}

int main(int argc, char **argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    Main();
	return 0;
}
//入力
/*
N
a_0, a_1, ....a_n-1

(sample)
入力
3
7 5 3

出力
3 5 7 
3 7 5 
5 3 7 
5 7 3 
7 3 5 
7 5 3 
*/