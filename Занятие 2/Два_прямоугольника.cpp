#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Rect {
    int l, r, t, b;
};
bool comp(pair<int, Rect>& a, pair<int, Rect>& b) {
    return a.first > b.first;
}
bool all_b(char **a, int l, int r, int b) {
    for (int j = l; j <= r; ++j)
        if (a[b][j] == '.') return 0;
    return 1;
}
bool all_r(char** a, int t, int b, int r) {
    for (int i = t; i <= b; ++i)
        if (a[i][r] == '.') return 0;
    return 1;
}
bool podelit(vector<pair<int, Rect>>& rv) {
    if (rv[0].second.l != rv[0].second.r) {
        rv[1].second.l = rv[0].second.l;
        rv[1].second.r = rv[0].second.l;
        rv[1].second.t = rv[0].second.t;
        rv[1].second.b = rv[0].second.b;
        ++rv[0].second.l;
    }
    else {
        rv[1].second.l = rv[0].second.l;
        rv[1].second.r = rv[0].second.r;
        rv[1].second.t = rv[0].second.t;
        rv[1].second.b = rv[0].second.t;
        ++rv[0].second.t;
    }
    return 1;
}

bool itis(vector<pair<int, Rect>>& rv, int k) {
    sort(rv.begin(), rv.end(), comp);
    for (int i = 0; i < rv.size(); ++i) {
        for (int j = i+1; j < rv.size(); ++j) {
            if (rv[i].first + rv[j].first < k) break;
            if (rv[i].first + rv[j].first == k && (rv[i].second.r != rv[j].second.r || rv[i].second.b != rv[j].second.b) && 
               (rv[i].second.r < rv[j].second.l || rv[j].second.r < rv[i].second.l || rv[i].second.b < rv[j].second.t || rv[j].second.b < rv[i].second.t)) {
                rv[0] = rv[i];
                rv[1] = rv[j];
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    int n, m, k = 0, l, r=0, t, b;
    vector<pair<int, Rect>> rv;
    bool yes = 0, part = 0;
    cin >> n >> m;
    char** a = new char* [n];
    for (int i = 0; i < n; i++) {
        a[i] = new char[m];
        t = k;
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
            if (a[i][j] == '#') ++k;
        }
        if (!part && k != t) {
            ++r;
            part = 1;
        }
        if (k==t) part = 0;
    }
    if (!k || k == 1 || r>2 || (k == n*m-1 && a[0][0]=='#' && a[0][m-1]=='#' && a[n-1][0]=='#' && a[n-1][m-1]=='#')) { 
        cout << "NO"; 
        for (int i = 0; i < n; i++) delete[] a[i];
        delete[] a; 
        return 0; 
    }
    if (k == n * m) {
        cout << "YES\n";
        if (n != 1) {
            string str = "";
            for (int j = 0; j < m; ++j) {
                cout << 'a';
                str += 'b';
            }
            for (int i = 1; i < n; ++i) cout << "\n" << str;
        }
        else {
            cout << 'a';
            for (int j = 1; j < m; ++j) cout << 'b';
        }
        for (int i = 0; i < n; i++) delete[] a[i];
        delete[] a;
        return 0;
    }
    else {
        for (int i = 0; i < n; ++i) { // левый верхний - правый нижний
            for (int j = 0; j < m; ++j) {
                if (a[i][j] == '#') {
                    l = r = j;
                    t = b = i;
                    while (r + 1 < m && a[i][r + 1] == '#') ++r;
                    rv.push_back({ (r - l + 1) * (b - t + 1), { l,r,t,b } });
                    while (b + 1 < n && (l == 0 || r + 1 == m || a[b + 1][l - 1] == '.' || a[b + 1][r + 1] == '.') && all_b(a, l, r, b + 1)) ++b;
                    if (b != t) rv.push_back({ (r - l + 1) * (b - t + 1), { l,r,t,b } });

                    l = r = j;
                    t = b = i;
                    while (b + 1 < n && a[b + 1][j] == '#') ++b;
                    rv.push_back({ (r - l + 1) * (b - t + 1), { l,r,t,b } });
                    while (r + 1 < m && (t == 0 || b + 1 == n || a[t - 1][r + 1] == '.' || a[b + 1][r + 1] == '.') && all_r(a, t, b, r + 1)) ++r;
                    if (r != l) rv.push_back({ (r - l + 1) * (b - t + 1), { l,r,t,b } });
                }
            }
        }
        if (rv[0].first == k) yes = podelit(rv);
        else yes = itis(rv, k);
    }

    if (yes) {
        for (k = 0; k < 2; ++k) {
            for (int i = rv[k].second.t; i <= rv[k].second.b; ++i) {
                for (int j = rv[k].second.l; j <= rv[k].second.r; ++j) {
                    if (k) a[i][j] = 'b';
                    else a[i][j] = 'a';
                }
            }
        }
        cout << "YES\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                cout << a[i][j];
            cout << "\n";
        }
    }
    else cout << "NO";

    for (int i = 0; i < n; i++) delete[] a[i];
    delete[] a;

return 0;
}
