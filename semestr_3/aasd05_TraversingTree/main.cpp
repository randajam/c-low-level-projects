#include <iostream>

using namespace std;

void preorder(int* p, int N, int pos) {
    if (pos > N) return;

    cout << p[pos - 1] << " ";

    preorder(p, N, pos * 2);
    preorder(p, N, pos * 2 + 1);
}

void postorder(int* p, int N, int pos) {
    if (pos > N) return;
    else {
        postorder(p, N, pos * 2);
        postorder(p, N, pos * 2 + 1);
        cout << p[pos - 1] << " ";
    }
}

int main() {
    int N;
    cin >> N;
    int* p = new int[N];
    for (int i = 0; i < N; i++) {
        cin >> p[i];
    }

    preorder(p, N, 1);
    cout << endl;
    postorder(p, N, 1);

    return 0;
}