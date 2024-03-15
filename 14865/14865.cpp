#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int fx, fy;
    cin >> fx >> fy;

    bool upside = false;
    bool opposite = false;
    if (fy > 0) {
        upside = true;
        opposite = true;
    }

    int x, y;
    queue<int> q;
    for (int i = 1; i < N; i++) {
        cin >> x >> y;

        if (y < 0 && !upside) continue;
        if (y > 0 && upside) continue;

        upside = !upside;
        q.push(x);
    }

    if (q.size() & 1) {
        q.push(fx);
    }

    if (opposite) {
        q.push(q.front());
        q.pop();
    }

    vector<pair<int, int>> arr;
    while (!q.empty()) {
        int s = q.front();
        q.pop();
        int e = q.front();
        q.pop();

        if (s > e) swap(s, e);
        arr.emplace_back(s, e);
    }
    sort(arr.begin(), arr.end());

    stack<pair<int, int>> s;
    int ans1 = 0;
    int ans2 = 1;
    for (auto hill : arr) {
        if (s.empty()) {
            s.push(hill);
            ans1++;
            continue;
        }

        if (hill.first < s.top().second) {
            s.push(hill);
            continue;
        }

        ans2++;

        while (!s.empty() && s.top().second < hill.first) {
            s.pop();
        }
        if (s.empty()) {
            ans1++;
        }

        s.push(hill);
    }
    cout << ans1 << " " << ans2;

    return 0;
}
