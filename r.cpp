#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    char id[5];
    unsigned seed = time(0);

    srand(100);

    for(int i = 0; i < 2; i++) {
        id[i] = (char)(rand()%26 + 'A');
    }
    for(int i = 2; i < 5; i++) {
        id[i] = (char)(rand()%10 + 48);
    }

    cout << id << endl;
}