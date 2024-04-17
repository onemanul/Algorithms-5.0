#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int mx_n=0;
bool comp3(pair <pair<int, int>, int> a, pair <pair<int, int>, int> b) {
    int i = a.first.first - a.first.second, j = b.first.first - b.first.second;
    if (((a.second == mx_n && j>0) || (b.second == mx_n && i>0)) && (a.first.first != b.first.first)) return a.first.first < b.first.first;
    if (i>0 || j>0) return i > j;
    else return a.first.first > b.first.first;
}
bool comp(pair <pair<int, int>, int> a, pair <pair<int, int>, int> b) {
    return a.first.first - a.first.second > b.first.first - b.first.second;
}

int main() {
    int n, mx = 0;
    long long int s, m;
    vector<pair <pair<int, int>, int> > v;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s >> m;
        if (s-m > 0 && m > mx) {
            mx = m;
            mx_n = i + 1;
        }
        v.push_back({ {s,m},i + 1 });
    }

    sort(v.begin(), v.end(), comp);
    s = 0;
    m = 0;
    for (int i = 0; i < v.size(); ++i) {
        s += v[i].first.first;
        m = max(m, s);
        s -= v[i].first.second;
    }
    mx = m;

    sort(v.begin(), v.end(), comp3);
    s = 0;
    m = 0;
    for (int i = 0; i < v.size(); ++i) {
        s += v[i].first.first;
        m = max(m, s);
        s -= v[i].first.second;
    }

    if (mx > m) {
        sort(v.begin(), v.end(), comp);
        cout << mx << "\n";
        for (pair i : v) cout << i.second << " ";
    }
    else {
        cout << m << "\n";
        for (pair i : v) cout << i.second << " ";
    }

return 0;
}
