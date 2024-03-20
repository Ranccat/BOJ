#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

vector<pii> cows;
vector<pii> grasses;
multiset<int> s;
ll ans;

bool cmp(const pii& a, const pii& b) {
    if (a.second == b.second) return (a.first < b.first);
    return a.second > b.second;
}

int main() {
    int N, M;
    cin >> N >> M;

    int a, b;
    for (int i = 0; i < N; i++) {
        cin >> a >> b;
        cows.emplace_back(a, b);
    }
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        grasses.emplace_back(a, b);
    }

    // sort grass's gourmet score by decreasing order
    // if same, lower price should come first
    sort(cows.begin(), cows.end(), cmp);
    sort(grasses.begin(), grasses.end(), cmp);

    // for each cow
    int last = 0;
    for (int i = 0; i < N; i++) {
        pii cow = cows[i];

        // insert all the possible grasses into set
        while (last < M) {
            pii grass = grasses[last];
            if (grass.second < cow.second) break;
            s.insert(grass.first);
            last++;
        }

        // find the cheapest grass in the set and erase it
        // if none, print -1 and finish
        auto it = s.lower_bound(cow.first);
        if (it == s.end()) {
            ans = -1;
            break;
        }

        ans += *it;
        s.erase(it);
    }

    cout << ans;
    return 0;
}
