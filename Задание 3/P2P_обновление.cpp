#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

struct ustr {
    set<int> obn; // k
    vector <int> prior; // n
};
int n, k, t = 0;
vector<ustr> u;
map<int, set<int>> ch;
vector<pair<int, int>> plus_prior; // кому, чей

void zapros(vector<int>& kolch, vector<vector<pair<int, int>>>& zpr) {
    for (int i = 1; i < n; ++i) {
        if (u[i].obn.size()) {
            int cha = *u[i].obn.begin();
            for (int m : u[i].obn)
                if (kolch[cha] > kolch[m]) cha = m;

            int us = *ch[cha].begin();
            for (int s : ch[cha])
                if (u[us].obn.size() < u[s].obn.size()) us = s;
            zpr[us].push_back({ i, cha });
        }
    }
}

void otvet(vector<int>& kolch, vector<vector<pair<int, int>>>& zpr) {
    for (int i = 0; i < n; ++i) {
        if (zpr[i].size()) {
            int wo = zpr[i][0].first, wha = zpr[i][0].second, max_pr = u[i].prior[wo];
            for (const auto& [who, what] : zpr[i]) {
                if (u[i].prior[wo] < u[i].prior[who]) {
                    wo = who;
                    wha = what;
                    max_pr = u[i].prior[who];
                }
            }
            for (const auto& [who, what] : zpr[i]) {
                if (u[i].prior[who] == max_pr) {
                    if (u[wo].obn.size() < u[who].obn.size()) {
                        wo = who;
                        wha = what;
                    }
                }
            }
            ++kolch[wha];
            ch[wha].insert(wo);
            u[wo].obn.erase(wha);
            plus_prior.push_back({ wo,i });
        }
    }

}

int check_obn(vector<int>& ans) {
    int a = 0;
    for (int i = 0; i < n-1; ++i) {
        if (!u[i+1].obn.size()) {
            if (!ans[i]) ans[i] = t;
        }
        else ++a;
    }
    return a;
}

int main() {
    cin >> n >> k;
    vector<int> ans(n-1,0), kolch(k, 1), pr(n, 0);
    vector<vector<pair<int,int>>> zpr(n), zpr1(n); // запрашиваемое {запрашивающее, часть}
    set<int> s;
    ustr a;
    s.insert(0);
    a.prior = pr;
    u.push_back(a);
    for (int i = 0; i < k; ++i) {
        a.obn.insert(i);
        ch.insert({ i,s });
    }
    for (int i = 1; i < n; ++i) u.push_back(a);
    while (check_obn(ans)) {
        ++t;
        zapros(kolch, zpr);
        otvet(kolch, zpr);
        zpr = zpr1;
        for (const auto& [who, whom] : plus_prior) ++u[who].prior[whom];
        plus_prior.clear();
    }
    for (int i : ans) cout << i << " ";

return 0;
}
