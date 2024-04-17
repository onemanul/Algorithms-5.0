#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

void day(int x) {
    switch (x) {
    case 0: { cout << "Monday"; break; }
    case 1: { cout << "Tuesday"; break; }
    case 2: { cout << "Wednesday"; break; }
    case 3: { cout << "Thursday"; break; }
    case 4: { cout << "Friday"; break; }
    case 5: { cout << "Saturday"; break; }
    case 6: { cout << "Sunday"; break; }
    default: break;
    }
}

int main() {
    int n, year, d, dm[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }, a = 0;
    map<string, int> m{ {"January", 0}, {"February", 1}, {"March", 2}, {"April", 3}, {"May", 4}, {"June", 5},
                        {"July", 6}, {"August", 7}, {"September", 8}, {"October", 9}, {"November", 10}, {"December", 11} },
                    days{ {"Monday", 0}, {"Tuesday", 1}, {"Wednesday", 2}, {"Thursday", 3}, {"Friday", 4}, {"Saturday", 5}, {"Sunday", 6} };
    vector<int> pr, dn = { 52,52,52,52,52,52,52 };
    string mstr;
    cin >> n >> year;
    if (year%400==0 || (year%4==0 && year%100!=0)) dm[1]++;
    for (int i = 0; i < n; ++i) {
        cin >> d >> mstr;
        for (int j = 0; j < m[mstr]; ++j) 
            a += dm[j];
        pr.push_back((a+d-1)%7);
        a = 0;
    }
    cin >> mstr;
    d = days[mstr];
    dn[d]++;
    if (year % 4 == 0 && year % 100 != 0) dn[(d+1)%7]++;
    for (int p : pr) dn[(p+d)%7]--;
    day(max_element(dn.begin(), dn.end()) - dn.begin());
    cout << " ";
    day(min_element(dn.begin(), dn.end()) - dn.begin());

return 0;
} 
