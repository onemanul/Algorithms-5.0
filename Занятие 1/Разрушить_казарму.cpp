#include <iostream>
using namespace std;

int already_possible(int x, int y, int s, bool stop) {
    int n = 0, k;
    if (!stop) k = what(x, y-max(x-s,0), s, 1);
    s -= x-y;
    x -= s;
	while (s > 0 && x > 0) {
        s -= x;
        x -= s;
        ++n;
    }
    if (stop) return n;
    if ((s <= 0) && (!k || k+1 > n)) return n;
    else return 0;
}

int check(int x, int s) {
    x -= s;
    while (s > 0 && x > 0) {
        s -= x;
        x -= s;
    }
    if (s > 0) return 1;
    else return 0;
}

int main() {
    int x, y, p, s=0, n = 1;
    cin >> x >> y >> p;
    y -= x; 
    if (y>0) s = p;
    while (s+y > 0 && x > 0) {
        if (x == s && (y >= s || check(x, s-x+y)) ) break;
        if (y>0 && y<=x && already_possible(x,y,s,0) ) {
            s -= x-y;
            y = 0;
        }
        else {
            s -= x;
            if (y>0 && s<0) {
                y += s;
                s = 0;
            }
        }
        x -= s;
        if (y>0) s += p;
        ++n;
    }
    if (s+y <= 0) cout << n;
    else cout << -1;

return 0;
} 
