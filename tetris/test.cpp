#include <bits/stdc++.h>
using namespace std;
int main(){
    vector<vector<int>> temp{{1, 1}, {1, 1}};
    vector<vector<int>> stuff = temp;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            cout << stuff[i][j];
    return 0;
}