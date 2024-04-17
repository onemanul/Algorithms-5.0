// Возможно, всё здесь держится на косылях и честном слове.
// Но главное, что оно держится

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int w, h, c, he = 100;
int xF, yF;
bool xyF = 0, xS = 0, hTr = 0;
vector<int> param = { 0,0,0,0,0 };
ifstream file("input.txt");

int ret_int(string str, string what) {
    size_t pos;
    pos = str.find(what);
    str.erase(0, pos + what.size());
    istringstream ss(str);
    int chislo;
    ss >> chislo;
    return chislo;
}
string layout(string str) {
    string s = str, word;
    size_t pos;
    bool yes = 0;
    pos = s.find("(image");
    s.erase(0, pos + 6);
    if (s.empty()) getline(file, s);
    while (!yes) {
        pos = s.find(")");
        if (pos != string::npos) {
            str = s.substr(pos + 1);
            s.erase(pos);
            yes = 1;
        }
        istringstream ss(s);
        while (ss >> word) {
            switch (word[1]) {
            case 'a': //layout
                switch (word[7]) {
                case 'e': param[0] = 0; break;
                case 's': param[0] = 1; break;
                case 'f': param[0] = 2; break;
                }
                break;
            case 'i': //width
                param[1] = ret_int(s, "width=");
                break;
            case 'e': //height
                param[2] = ret_int(s, "height=");
                break;
            case 'x': //dx
                param[3] = ret_int(s, "dx=");
                break;
            case 'y': //dy
                param[4] = ret_int(s, "dy=");
                break;
            default: break;
            }
        }
        if (!yes) getline(file, s);
    }
    return str;
}
bool comp(pair<int, int> a, pair<int, int> b) {
    return a.first < b.first;
}
void erel(vector<pair<int, int>>& wel, vector<pair<int, int>>& hel, vector<bool> posel) {
    for (int i = 0; i < wel.size() - 1; ++i) {
        if (wel[i].second >= wel[i + 1].first) {
            if (wel[i].first == 0) posel[i] = 0;
            if (wel[i + 1].second == w) posel[i] = 1;
            if (hel[i].first < hel[i + 1].first || !posel[i + 1]) {
                hel[i].first = hel[i + 1].first;
                hel[i].second = hel[i + 1].second;
            }
            wel[i].second = wel[i + 1].second;
            wel.erase(wel.begin() + i + 1);
            hel.erase(hel.begin() + i + 1);
            posel.erase(posel.begin() + i + 1);
            --i;
        }
    }
    if (wel.size() == 1 && wel[0].first == 0 && wel[0].second == w) wel.clear();
}
void place(int& x, int& y, int dl, vector<pair<int, int>>& wel, vector<pair<int, int>>& hel, vector<bool> posel, bool prob) {
    bool stop = 0;
    while (!stop && wel.size()) {
        for (int i = 0; i < wel.size(); ++i) {
            if (x < wel[i].first || x > wel[i].second) continue;
            if (prob && x - c < wel[i].first) x = wel[i].first;
            if (x + dl <= wel[i].second) {
                stop = 1;
                break;
            }
            else
                if (i + 1 != wel.size()) x = wel[i + 1].first;
        }
        if (!stop) {
            y += h;
            for (int i = 0; i < hel.size(); ++i) {
                hel[i].first -= h;
                if (hel[i].first <= 0) {
                    if (posel[i]) {
                        wel[i].first -= hel[i].second;
                        if (wel[i].first < 0) wel[i].first = 0;
                        if (i) hel[i].first = hel[i - 1].first;
                    }
                    else {
                        wel[i].second += hel[i].second;
                        if (wel[i].second > w) wel[i].second = w;
                        if (i + 1 < wel.size()) hel[i].first = hel[i + 1].first;
                    }
                }
            }
            if (h > he && hTr) {
                swap(he, h);
                hTr = 0;
            }
            if (wel.size()) x = wel[0].first;
            else x = 0;
        }
        erel(wel, hel, posel);
    }
}

void embedded(int& x, int& y) {
    xyF = 0; xS = 0;
    int wid = param[1], hei = param[2];
    if (x + wid <= w) {
        cout << x << " " << y << "\n";
        x += wid + c;
    }
    else {
        y += h;
        if (h > he && hTr) {
            swap(he, h);
            hTr = 0;
        }
        x = wid + c;
        cout << 0 << " " << y << "\n";
    }
    if (hei > h) {
        if (hTr) h = hei;
        else {
            he = hei;
            swap(he, h); // h = new(>he), he = h
            hTr = 1;
        }
    }
}
void floating(int& x, int& y) {
    int wid = param[1], hei = param[2], dx = param[3], dy = param[4];
    bool pr = 0;
    if (x && !xyF && !xS) {
        x -= c;
        pr = 1;
    }
    if (x > w) {
        x = 0;
        y += h;
        if (h > he && hTr) {
            swap(he, h);
            hTr = 0;
        }
    }
    if (x + dx < 0 || x + dx + wid > w) {
        if (x + dx < 0) {
            cout << 0 << " " << y + dy << "\n";
            xF = wid; yF = y + dy;
        }
        else {
            cout << w - wid << " " << y + dy << "\n";
            xF = w; yF = y + dy;
        }
    }
    else {
        cout << x + dx << " " << y + dy << "\n";
        xF = x + dx + wid; yF = y + dy;
    }
    if (pr) x += c;
    xyF = 1; xS = 0;
}
string surrounded(string str, int& x, int& y) {
    xyF = 0;
    int wid = param[1], hei = param[2];
    vector<pair<int, int>> wel, hel_wid;
    vector<bool> posel;
    if (x > 0 && !xS) x -= c;
    if (x + wid >= w) {
        if (x + wid > w) {
            y += h;
            if (h > he && hTr) {
                swap(he, h);
                hTr = 0;
            }
            x = wid;
            cout << 0 << " " << y << "\n";
            wel.push_back({ x,w });
            hel_wid.push_back({ hei,wid });
            posel.push_back(1);
        }
        else {
            cout << x << " " << y << "\n";
            wel.push_back({ 0,x });
            hel_wid.push_back({ hei,wid });
            posel.push_back(0);
            x += wid;
        }
    }
    else {
        cout << x << " " << y << "\n";
        if (x == 0) {
            x = wid;
            wel.push_back({ x,w });
            hel_wid.push_back({ hei,wid });
            posel.push_back(1);
        }
        else {
            wel.push_back({ 0,x });
            hel_wid.push_back({ hei,wid });
            posel.push_back(0);
            x += wid;
            wel.push_back({ x,w });
            hel_wid.push_back({ hei,wid });
            posel.push_back(1);
        }
    }
    xS = 1;
    if (hei <= h) return str;

    if (str.empty()) getline(file, str);
    int dl;
    string word, im = "(image";
    bool prob = 0;
    do {
        if (str.empty()) {
            pair<int, int> max_hel = *max_element(hel_wid.begin(), hel_wid.end(), comp);
            y += max(h, max_hel.first);
            if (h > he && hTr) {
                swap(he, h);
                hTr = 0;
            }
            x = 0;
            xS = 0;
            return str;
        }
    label2: istringstream ss(str);
        while (wel.size() && ss >> word) {
            if (word != im) {
                xyF = 0; xS = 0;
                if (prob) {
                    x += c;
                    for (int i = 0; i < wel.size() - 1; ++i)
                        if (x > wel[i].second && x < wel[i + 1].first) {
                            x = wel[i + 1].first;
                            break;
                        }
                }
                dl = word.size() * c;
                place(x, y, dl, wel, hel_wid, posel, prob);
                x += dl;
                prob = 1;
            }
            else {
                str = layout(str); // param[0] : e,s,f
                switch (param[0]) {
                case 0: {
                    xyF = 0;
                    wid = param[1], hei = param[2];
                    if (prob) {
                        if (find_if(wel.begin(), wel.end(), [=](const pair<int, int>& p) { return p.first == x; }) == wel.end()) x += c;
                        for (int i = 0; i < wel.size() - 1; ++i) {
                            if (x > wel[i].second && x < wel[i + 1].first) {
                                x = wel[i + 1].first;
                                break;
                            }
                        }
                    }
                    place(x, y, wid, wel, hel_wid, posel, prob);
                    if (hei > h) {
                        if (hTr) h = hei;
                        else {
                            he = hei;
                            swap(he, h); // h = new(>he), he = h
                            hTr = 1;
                        }
                    }
                    cout << x << " " << y << "\n";
                    x += wid;
                    prob = 1;
                    xS = 0;
                    break;
                }
                case 1: {
                    prob = 0; xyF = 0; xS = 1;
                    wid = param[1], hei = param[2];
                    place(x, y, wid, wel, hel_wid, posel, 0);
                    cout << x << " " << y << "\n";
                    if (hei <= h) {
                        x += wid;
                        break;
                    }
                    if (!wel.size()) {
                        hel_wid.clear(); posel.clear();
                        x = wid;
                        wel.push_back({ x,w });
                        hel_wid.push_back({ hei,wid });
                        posel.push_back(1);
                    }
                    else {
                        bool yes = 0;
                        for (int i = 0; i < wel.size(); ++i) {
                            if (x == wel[i].first) {
                                x += wid;
                                if (posel[i]) {
                                    wel.insert(wel.begin() + i, { wel[i].first, wel[i].first });
                                    hel_wid.insert(hel_wid.begin() + i, { hel_wid[i].first, hel_wid[i].second });
                                    posel.insert(posel.begin() + i, 1);
                                    wel[i + 1].first = x;
                                    hel_wid[i + 1].first = hei;
                                    hel_wid[i + 1].second = wid;
                                }
                                else {
                                    wel.insert(wel.begin() + i, { wel[i].first, wel[i].first });
                                    hel_wid.insert(hel_wid.begin() + i, { hei, wid });
                                    posel.insert(posel.begin() + i, 0);
                                    wel[i + 1].first = x;
                                }
                                yes = 1;
                                break;
                            }
                            if ((x > wel[i].first) && (x + wid == wel[i].second)) {
                                wel.insert(wel.begin() + i + 1, { wel[i].second, wel[i].second });
                                hel_wid.insert(hel_wid.begin() + i + 1, { hei,wid });
                                posel.insert(posel.begin() + i + 1, 1);
                                wel[i].second = x;
                                if (i + 2 < wel.size()) x = wel[i + 2].first;
                                else x = w;
                                yes = 1;
                                break;
                            }
                        }
                        if (!yes) {
                            for (int i = 0; i < wel.size(); ++i) {
                                if (x < wel[i].first || x >= wel[i].second) continue;
                                if (posel[i]) {
                                    wel.insert(wel.begin() + i + 1, { x + wid, wel[i].second });
                                    hel_wid.insert(hel_wid.begin() + i + 1, { hei,wid });
                                    posel.insert(posel.begin() + i + 1, 1);
                                    wel[i].second = x;
                                    x += wid;
                                    break;
                                }
                                else {
                                    wel.insert(wel.begin() + i, { wel[i].first, x });
                                    hel_wid.insert(hel_wid.begin() + i, { hei,wid });
                                    posel.insert(posel.begin() + i, 0);
                                    wel[i + 1].first = x + wid;
                                    x += wid;
                                    break;
                                }
                            }
                        }
                    }
                    break;
                }
                case 2: {
                    if (prob) x += c;
                    if (xyF) floating(xF, yF);
                    else floating(x, y);
                    break;
                }
                }
                if (str.empty()) break;
                else goto label2; // istringstream ss(str);
            }
        }
        if (!wel.size()) {
            if (prob) x += c;
            auto pos = str.find(word);
            str.erase(0, pos + word.size());
            return str;
        }
    } while (getline(file, str));
    return "";
}

int main() {
    int x = 0, y = 0, dl;
    string str, word, im = "(image";
    file >> w >> h >> c;
    getline(file, str); // досчитать \n после чисел
    while (getline(file, str)) {
        if (str.empty()) {
            xyF = 0; xS = 0;
            y += h;
            if (h > he && hTr) {
                swap(he, h);
                hTr = 0;
            }
            x = 0;
            continue;
        }
    label: istringstream ss(str);
        while (ss >> word) {
            if (word != im) {
                xyF = 0; xS = 0;
                dl = word.size() * c;
                if (x + dl <= w) x += dl + c;
                else {
                    y += h;
                    if (h > he && hTr) {
                        swap(he, h);
                        hTr = 0;
                    }
                    x = dl + c;
                }
            }
            else {
                str = layout(str); // param[0] : e,s,f
                switch (param[0]) {
                case 0: embedded(x, y); break;
                case 1: str = surrounded(str, x, y); break;
                case 2: {
                    if (xyF) floating(xF, yF);
                    else floating(x, y);
                    break;
                }
                }
                if (str.empty()) break;
                else goto label; // istringstream ss(str);
            }
        }
    }

    return 0;
}
