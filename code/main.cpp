#include <bits/stdc++.h>

using namespace std;
int dcent[1510];// 每一点的层数
int cents = 1, mcent[1510];// 继承每一点最大数值
queue<int> q;
int rudu[1510], n;
vector<pair<int, int>> g[1510];
void print(int arr[]){
    for(int i = 1;i <= n;i++){
        cout << arr[i] << ' ';
    }
    cout << endl;
}
int main() {
    int m, u, v, w, x;
    cin >> n >> m;
    for(int i = 1;i <= m;i++){
        cin >> u >> v >> w;
        g[u].push_back(make_pair(v, w));
        rudu[v]++;
    }
//    print(rudu);
//    for(int i = 1;i <= n;i++){
//        if (rudu[i] == 0) {
//            q.push(i);
//            mcent[i] = 0;
//            dcent[i] = 1;
//        }
//    }
    q.push(1);
    mcent[1] = 0;
    dcent[1] = 1;
    int maxn = 0;
    int cnt = 0;
    while(!q.empty()){
        cnt++;
        x = q.front();
        q.pop();
        for(int i = 0;i < g[x].size();i++){
            rudu[g[x][i].first]--;
            dcent[g[x][i].first] = dcent[x] + 1;
            cents = max(cents, dcent[x] + 1);
            mcent[g[x][i].first] = max(mcent[x] + g[x][i].second, mcent[g[x][i].first]);
//            print(mcent);
            if (rudu[g[x][i].first] == 0){
                q.push(g[x][i].first);
            }
        }
    }
    for(int i = 1;i <= n;i++){
        maxn = max(maxn, mcent[i]);
    }
    cout << mcent[n]?mcent[n]:-1;
    return 0;
}
/*
 12 15
 1 2 1
 1 3 2
 2 4 4
 3 6 6
 3 5 7
 4 7 9
 5 8 1
 6 8 3
 7 9 1
 8 9 2
 10 3 2
 11 10 4
 11 1 3
 12 2 9
 4 6 7
 */