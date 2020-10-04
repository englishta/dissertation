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


void Main(){
    /*���dp�A�����a*/
    //����a_1 a_2 a_3....a_(n-1), a_n���^������
    //���������^������
    //�����̐�������A���������R�ɑI��ŁA�����̑��a��m�ɂ��邱�Ƃ��ł��邩�H

    LL(n, m);
    bool dp[n+1][m+1];
    vector<ll> a(n);
    rep(i,n) cin >> a[i];
    dp[0][0] = true;
    for(ll i=1; i<=m; ++i) dp[0][i] = false;

    //dp[i][j] : ����a[0]�`a[i-1]�܂ł́Ai�̐����̒��ŁA�������I�сA���̑��a��j�ɂ��邱�Ƃ��o���邩�Atrue or false
    //dp[i][j] = (dp[i-1][j-a[i-1]] || dp[i-1][j])
    //�������Aj-a[i-1]<0�͂��肦�Ȃ��̂ŏ��O����B
    
    for(ll i=1; i<=n; ++i){
        for(ll j=0; j<=m; ++j){
            dp[i][j] = dp[i-1][j];
            if(m-a[i-1] >= 0) dp[i][j] |= dp[i-1][j-a[i-1]];
        }
    }
    if(dp[n][m]) cout << "Yes" << endl;
    else cout << "No" << endl;
}

int main(int argc, char **argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    Main();
	return 0;
}
