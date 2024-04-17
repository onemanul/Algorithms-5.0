#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int main() {
    int l, x1, v1, x2, v2, v;
    double x, t1, t = numeric_limits<double>::max();
    cin >> l >> x1 >> v1 >> x2 >> v2;
    if (min(x1, l - x1) == min(x2, l - x2)) {
        cout << "YES\n" << 0;
        return 0;
    }
    if (!v1 && !v2) {
        cout << "No";
        return 0;
    }
    x = x1 - x2;
    v = v2 - v1;
    if (v) {
        for (int i = -1; i < 3; ++i) {
            t1 = (x-l*i) / v;
            if (t1 > 0 && t1 < t) t = t1;
        }
    }
    x = x1 + x2;
    v = v1 + v2;
    if (v) {
        for (int i = -1; i < 3; ++i) {
            t1 = (l*i-x) / v;
            if (t1 > 0 && t1 < t) t = t1;
        }
    }
    cout << fixed << setprecision(10) << "YES\n" << t;
    
return 0;
} 
