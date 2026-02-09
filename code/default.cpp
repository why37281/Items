#include <bits/stdc++.h>

using namespace std;
int goesto[8][2] = {
        {2, 1},
        {2, -1},
        {1, 2},
        {1, -2},
        {-1, 2},
        {-1, -2},
        {-2, 1},
        {-2, -1}

};
int step[450][450];
int n, m, x, y;
void bfs(int x, int y, int times){
    step[x][y] = times;
    for(int i = 0;i < 8;i++){
        if (x + goesto[i][0] > 0 && x + goesto[i][0] <= n                               &&
        y + goesto[i][1] > 0 && y + goesto[i][1] <= m                                   &&
                (step[x + goesto[i][0]][y + goesto[i][1]] == -1
                || step[x + goesto[i][0]][y + goesto[i][1]] > times + 1
                )){
            bfs(x + goesto[i][0], y + goesto[i][1], times + 1);
        }
    }
}
int main() {
    cin >> n >> m >> x >> y;
    for(auto & i : step){
        for(int & j : i){
            j = -1;
        }
    }
    bfs(x, y, 0);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            cout <<  step[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}