#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <string>
using namespace std;

struct team {
    int games, goals, begins;
    set<string> players;
};
struct player {
    int games, goals, begins;
    map<int, int> minutes;
};
ifstream in("input.txt");
map<string, team> t;
map<string, player> p;

void comand(string& com, int g) {
    if (t.count(com)) {
        ++t[com].games;
        t[com].goals += g;
    }
    else {
        team tm;
        tm.games = 1;
        tm.goals = g;
        tm.begins = 0;
        t.insert({ com,tm });
    }
}
void ftballer(string& pl, int mnt) {
    if (p.count(pl)) {
        ++p[pl].goals;
        if (p[pl].minutes.count(mnt)) ++p[pl].minutes[mnt];
        else p[pl].minutes.insert({ mnt,1 });
    }
    else {
        player igr;
        igr.goals = 1;
        igr.minutes.insert({ mnt,1 });
        igr.begins = 0;
        p.insert({ pl,igr });
    }
}
void game(string& str) {
    string::size_type n = str.find('"',1), m = str.find('"', n+1);
    string pl, pl1, pl2, com1 = str.substr(1, n - 1), com2 = str.substr(m+1, str.find('"',m+1)-m-1); // "Juventus" - "Milan" 3:1
    int  a, b, mnt, mn1 = 90, mn2 = 90;
    n = str.find_last_of(' ');
    str = str.substr(n);
    n = str.find_last_of(':');
    str.replace(n, 1, " ");
    istringstream ss(str);
    ss >> a >> b;
    comand(com1, a);
    comand(com2, b);
    if (a || b) {
        for (int i = 0; i < a; ++i) {
            getline(in, str);
            str.pop_back();
            n = str.find_last_of(' ');
            pl = str.substr(0, n);
            mnt = stoi(str.substr(n + 1));
            t[com1].players.insert(pl);
            ftballer(pl, mnt);
            if (!i) {
                mn1 = mnt;
                pl1 = pl;
            }
        }
        for (int i = 0; i < b; ++i) {
            getline(in, str);
            str.pop_back();
            n = str.find_last_of(' ');
            pl = str.substr(0, n);
            mnt = stoi(str.substr(n + 1));
            t[com2].players.insert(pl);
            ftballer(pl, mnt);
            if (!i) {
                mn2 = mnt;
                pl2 = pl;
            }
        }
        if (mn1 < mn2) {
            ++p[pl1].begins;
            ++t[com1].begins;
        }
        else {
            ++p[pl2].begins;
            ++t[com2].begins;
        }
    }
    for (string name : t[com1].players) p[name].games = t[com1].games;
    for (string name : t[com2].players) p[name].games = t[com2].games;
}

int main() {
    string str, word;
    string::size_type n;
    int m, g;
    while (getline(in, str)) {
        switch (str[0]) {
            case '"': 
                game(str); 
                break;
            case 'T': {
                n = str.find('"');
                if (n == string::npos) {
                    n = str.find("by");
                    word = str.substr(n + 3);
                    cout << p[word].goals << "\n";
                }
                else {
                    str.pop_back();
                    word = str.substr(n + 1);
                    cout << t[word].goals << "\n";
                }
                break;
            }
            case 'M': {
                n = str.find('"');
                if (n == string::npos) {
                    n = str.find("by");
                    word = str.substr(n + 3);
                    cout << double(p[word].goals)/p[word].games << "\n";
                }
                else {
                    str.pop_back();
                    word = str.substr(n + 1);
                    cout << double(t[word].goals)/t[word].games << "\n";
                }
                break;
            }
            case 'G': {
                n = str.find("by");
                word = str.substr(n + 3);
                n = str.find("minutes");
                if (n != string::npos) { // first || last
                    g = 0;
                    str = str.substr(8, n-8);
                    istringstream ss(str);
                    ss >> str >> m;
                    if (str == "first") {
                        for (const auto& [min, goal] : p[word].minutes) {
                            if (min <= m) g += goal;
                            else break;
                        }
                    }
                    else {
                        for (const auto& [min, goal] : p[word].minutes)
                            if (min >= 91-m) g += goal;
                    }
                    cout << g << "\n";
                }
                else { // on
                    n = str.find("minute");
                    str = str.substr(n+6);
                    istringstream ss(str);
                    ss >> m;
                    cout << p[word].minutes[m] << "\n";
                }
                break;
            }
            case 'S': {
                n = str.find('"');
                if (n == string::npos) {
                    n = str.find("by");
                    word = str.substr(n + 3);
                    cout << p[word].begins << "\n";
                }
                else {
                    str.pop_back();
                    word = str.substr(n + 1);
                    cout << t[word].begins << "\n";
                }
                break;
            }
            default: break;
        }
    }

return 0;
}
