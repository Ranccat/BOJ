#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <numeric>
#define MAX 1500

using namespace std;
typedef pair<int, int> pii;

bool checkUnion(int, int);
void makeUnion(int, int);
int findUnion(int);
int coord2int(int, int);

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int R, C;
char arr[MAX][MAX];
bool V[MAX][MAX];
int uf[MAX*MAX];
vector<int> swans;
deque<pii> dq;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> R >> C;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 'X') continue;
            V[i][j] = true;
            dq.emplace_back(i, j);
            if (arr[i][j] == 'L') {
                swans.push_back(coord2int(i, j));
            }
        }
    }

    int l = R * C;
    std::iota(uf, uf + l, 0);

    int day = 0;
    while (!dq.empty()) {
        for (const auto& p : dq) {
            for (int dir = 0; dir < 4; dir++) {
                int nx = p.first + dx[dir];
                int ny = p.second + dy[dir];

                if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
                if (!V[nx][ny]) continue;

                makeUnion(coord2int(p.first, p.second), coord2int(nx, ny));
            }
        }

        if (checkUnion(swans[0], swans[1])) break;

        deque<pii> temp;
        while (!dq.empty()) {
            pii p = dq.front();
            dq.pop_front();
            for (int dir = 0; dir < 4; dir++) {
                int nx = p.first + dx[dir];
                int ny = p.second + dy[dir];

                if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
                if (V[nx][ny]) continue;

                temp.emplace_back(nx, ny);
                V[nx][ny] = true;
            }
        }
        dq = std::move(temp);

        day++;
    }

    cout << day;

    return 0;
}

bool checkUnion(int a, int b) {
    return findUnion(a) == findUnion(b);
}

void makeUnion(int a, int b) {
    int pa = findUnion(a);
    int pb = findUnion(b);
    if (pa < pb) uf[pb] = pa;
    else uf[pa] = pb;
}

int findUnion(int a) {
    if (uf[a] == a) return a;
    return uf[a] = findUnion(uf[a]);
}

int coord2int(int a, int b) {
    return a * C + b;
}
