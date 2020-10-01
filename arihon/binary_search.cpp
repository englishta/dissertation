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

int main() {
    vector<ll> a = {1, 1, 2, 2, 3, 5, 6};
    //　　　　　　　 0, 1, 2, 3, 4, 5, 6
    sort(all(a));
    auto uposi = upper_bound(all(a), 2);//指定した 数(2) 以上の要素の内，一番左側の要素の位置（最小のインデックス）をイテレータで返します．
    auto lopsi = lower_bound(all(a), 2);//指定した 数(2) より大きい要素の内，一番左側の要素の位置（最小のインデックス）をイテレータで返します．
    
    
    //条件を満たす要素が見つからなかった場合は，配列の末尾のイテレータを返します
    //（std::vector なら vec.end()，配列なら A + N）．そのため，見つからなかった場合に戻り値のイテレータからインデックスを計算して使おうとすると配列の範囲外を指定して予期せぬ結果が起こる可能性があります．
    //uposi のインデックス=2,
    //lopsi のインデックス=4,

    //*(イテレータ）でそのイテレータの要素を参照できる
    cout << *lopsi << endl;//  a[2]=2;
    cout << *uposi << endl;//  a[4]=3;

    cout << distance(a.begin(), lower_bound(all(a), 2)) << endl; //2 a[2]の位置に挿入される
    cout << distance(a.begin(), upper_bound(all(a), 2)) << endl; //4 a[4]の位置に挿入される

    //配列aにその数字があるなら、True ないなら、Falseを返す

    if(binary_search(all(a), 4)) puts("Yes");
    else puts("No");

    if(binary_search(all(a), 5)) puts("Yes");
    else puts("No");

    /*
    出力結果
    2
    3
    2
    4
    No
    Yes
    */
	return 0;
}
