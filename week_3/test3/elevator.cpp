#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int N, A, B;
    while (cin >> N && N != 0) {
        cin >> A >> B;
        vector<int> k(N);
        for (int i = 0; i < N; ++i) {
            cin >> k[i];
        }
        if (A == B) {
            cout << 0 << endl;
            continue;
        }
        vector<int> distance(N + 1, -1);
        queue<int> q;
        distance[A] = 0;
        q.push(A);
        bool found = false;
        while (!q.empty() && !found) {
            int current = q.front();
            q.pop();
            int kv = k[current - 1];
            int next_up = current + kv;
            if (next_up >= 1 && next_up <= N && next_up != current) {
                if (distance[next_up] == -1) {
                    distance[next_up] = distance[current] + 1;
                    if (next_up == B) {
                        cout << distance[next_up] << endl;
                        found = true;
                        break;
                    }
                    q.push(next_up);
                }
            }
            int next_down = current - kv;
            if (next_down >= 1 && next_down <= N && next_down != current) {
                if (distance[next_down] == -1) {
                    distance[next_down] = distance[current] + 1;
                    if (next_down == B) {
                        cout << distance[next_down] << endl;
                        found = true;
                        break;
                    }
                    q.push(next_down);
                }
            }
        }
        if (!found) {
            cout << -1 << endl;
        }
    }
    return 0;
}