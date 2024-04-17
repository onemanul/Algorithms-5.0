#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool comp(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) {
    return a.first > b.first;
}

int main() {
    int n, m, a, str1, stb1, str2, stb2, k1=0, k2=0;
    vector<pair<int, pair<int, int>>> v;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a;
            v.push_back({ a, {i,j} });
        }
    }
    sort(v.begin(), v.end(), comp);
    
    str1 = v[0].second.first;
    for (int j = 1; j < v.size(); ++j) {
        if (str1 == v[j].second.first) continue;
        else {
            stb1 = v[j].second.second;
            k1 = j;
            break;
        }
    }
    stb2 = v[0].second.second;
    for (int i = 1; i < v.size(); ++i) {
        if (stb2 == v[i].second.second) continue;
        else {
            str2 = v[i].second.first;
            k2 = i;
            break;
        }
    }

    while (k1 == k2) {
        for (int k = k1 + 1; k < v.size(); ++k) {
            if (str1 == v[k].second.first || stb1 == v[k].second.second) ++k1;
            if (str2 == v[k].second.first || stb2 == v[k].second.second) ++k2;
            if (k1!=k2) break;
        }
    }
    if (k1>k2) cout << str1 + 1 << " " << stb1 + 1;
    if (k1<k2) cout << str2 + 1 << " " << stb2 + 1;

return 0;
}
