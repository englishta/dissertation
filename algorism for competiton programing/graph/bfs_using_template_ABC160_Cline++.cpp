#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
#define lli long long int
#define rep(i,n) for(int i=0; i<n; i++)
#define loop(i, j, n) for(int i=j; i<n; i++)
using namespace std;
using Graph = vector<vector<int>>;
int main()
{
	int n, x, y;
	cin >> n >> x >> y;
	x -= 1;
	y -= 1;

	Graph G(n);
	rep(i,n-1){
		G[i].push_back(i+1);
		G[i+1].push_back(i);
	}

	G[x].push_back(y);
	G[y].push_back(x);

	queue<int> que;
	vector<int> Dist(n, 0);

	rep(i,n){
		vector<int> dist(n, -1);
		dist[i] = 0;
		que.push(i);

		while(!que.empty()){
			int v = que.front();
			que.pop();

			for(int nv : G[v]){
				if(dist[nv] != -1) continue;

				dist[nv] = dist[v] + 1;
				que.push(nv);
			}
		}
		rep(j,n) Dist[dist[j]]++;
	}

	loop(i, 1, n){
		cout << Dist[i]/2 <<endl;
	}
	return 0;
}