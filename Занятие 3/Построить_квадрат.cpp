#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int hesh(int x, int y) {
    int tmp = (y + ((x + 1) / 2));
    return x + (tmp * tmp);
}

int main() {
    int n, x, y, mx = 1000000000, a[4]; // 10^9
    double x0, y0, x1, y1, x2, y2;
    set<int> s;
    vector<pair<int, int>> v;
    bool zero = 1, p1 = 0, p2 = 0, put_two = 1;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        v.push_back({ x,y });
        s.insert(hesh(x, y));
    }
    for (int i = 0; i < v.size(); ++i) {
        for (int j = i + 1; j < v.size(); ++j) {
            x0 = double(v[i].first + v[j].first) / 2;
            y0 = double(v[i].second + v[j].second) / 2;
            x1 = x0 - v[i].second + y0;
            if (int(x1) - x1 || abs(x1) > mx) continue;
            y1 = y0 + v[i].first - x0;
            if (int(y1) - y1 || abs(y1) > mx) continue;
            x2 = x0 - v[j].second + y0;
            if (int(x2) - x2 || abs(x2) > mx) continue;
            y2 = y0 + v[j].first - x0;
            if (int(y2) - y2 || abs(y2) > mx) continue;
            p1 = p2 = 0;
            if (s.count(hesh(int(x1), int(y1))) ) {
                if (find(v.begin(), v.end(), make_pair(int(x1), int(y1)) ) != v.end())  p1 = 1;
            }
            if (s.count(hesh(int(x2), int(y2))) ) {
                if (find(v.begin(), v.end(), make_pair(int(x2), int(y2)) ) != v.end()) p2 = 1;
            }
            if (p1 && p2) break;
            if (zero && p1) {
                x = x2;
                y = y2;
                zero = 0;
            }
            if (zero && p2) {
                x = x1;
                y = y1;
                zero = 0;
            }
            if (put_two) {
                a[0] = x1;
                a[1] = y1;
                a[2] = x2;
                a[3] = y2;
                put_two = 0;
            }
        }
        if (p1 && p2) break;
    }

    if (p1 && p2) cout << 0;
    else {
        if (!zero) cout << 1 << "\n" << x << " " << y;
        else cout << 2 << "\n" << a[0] << " " << a[1] << "\n" << a[2] << " " << a[3];
    }

return 0;
}
