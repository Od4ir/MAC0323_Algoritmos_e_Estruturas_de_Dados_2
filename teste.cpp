#include <bits/stdc++.h>
using namespace std;

bool promoveu[2] = {false, false};

vector<char *> www;

int main() {
    int n; cin >> n;
    char word[100];

    for(int i = 0; i < n; i++) {
        cin >> word;
        www.push_back(word);

        cout << " ---- WWW ATUAL ---- \n";

        for(int j = 0; j < www.size(); j++) {
            cout << www[j] << endl;
        }
    }
}