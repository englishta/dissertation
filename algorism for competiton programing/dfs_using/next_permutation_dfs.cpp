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


void permutation(ll pos, ll n, vector<bool>& used, vector<ll>& perm){
    if(pos >= n){
        for(auto x : perm){
            cout << x << " ";
        }
        cout << endl;
        return;
    }

    for(ll i=1; i<=n; i++){
        if(used[i] == true) continue;
        used[i] = true;
        perm.push_back(i);
        permutation(pos+1, n, used, perm);
        perm.pop_back();
        used[i]  = false;
    }
}

void Main(){
    //1`N‚Ì®”—ñ‚ðŽ«‘‡‚É•À‚Ñ‘Ö‚¦‚Ä—ñ‹“‚·‚éƒvƒƒOƒ‰ƒ€Anext_permutation
    ll N;
    cin >> N;
    vector<bool> used(N);
    vector<ll> perm;
    permutation(0, N, used, perm);
}

int main(int argc, char **argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    Main();
	return 0;
}
