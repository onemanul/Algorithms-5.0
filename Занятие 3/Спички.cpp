#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    int n, x1,x2,y1,y2, mx = 0;
    pair<int, int> k;
    multimap< pair<int,int>, pair<int,int> > a, b; // вектор, начало
    map<pair<int, int>, int> sdv;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        if (x2 - x1 < 0 || (x2 - x1 == 0 && y2 - y1 < 0)) a.insert({ {x1 - x2, y1 - y2 }, {x2,y2} });
        else a.insert({ {x2 - x1,y2 - y1},{x1,y1} });
    }
    for (int i = 0; i < n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        if (x2 - x1 < 0 || (x2 - x1 == 0 && y2 - y1 < 0)) {
            swap(x1, x2);
            swap(y1, y2);
        }
        if (a.contains({x2-x1,y2-y1})) b.insert({ {x2-x1,y2-y1},{x1,y1} });
    }
    if (!b.size()) { cout << n; return 0; }
    for (auto it = a.begin(); it != a.end(); ) {
        if (!b.contains(it->first)) it = a.erase(it);
        else ++it;
    }

    for (const auto& [vec1, beg1] : a) {
        for (const auto& [vec2, beg2] : b) {
            if (vec1 != vec2) continue;
            k = { beg1.first - beg2.first, beg1.second - beg2.second };
            if (sdv.count(k)) ++sdv[k];
            else sdv.insert({ k,1 });
        }
    }
    for (const auto& [vec, raz] : sdv) mx = max(mx, raz);
    cout << n-mx;

return 0;
}
