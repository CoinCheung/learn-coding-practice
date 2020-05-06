#include<iostream>
#include<vector>
#include<unordered_set>

using namespace std;


class Solution {
 public:
    vector<vector<int>> connect;
    vector<bool> visited;
    vector<int> res;
    vector<int> n_childs;
    int n_nodes;

    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
        connect = vector<vector<int>>(N);
        for (auto& item : edges) {
            connect[item[0]].push_back(item[1]);
            connect[item[1]].push_back(item[0]);
        }
        res.assign(N, 0);
        n_childs = vector<int>(N, 0);
        n_nodes = N;

        if (edges.size() > 0) {
            visited.assign(N, false);
            dfs_root(edges[0][0]);
            visited.assign(N, false);
            dfs_children(edges[0][0]);
        }

        return res;
    }

    void dfs_root(int root) {
        visited[root] = true;
        for (int other : connect[root]) {
            if (visited[other]) {
                continue;
            }
            dfs_root(other);
            res[root] += res[other] + n_childs[other];
            n_childs[root] += n_childs[other];
        }
        ++n_childs[root];
    }

    void dfs_children(int root) {
        visited[root] = true;
        for (int other : connect[root]) {
            if (visited[other]) {
                continue;
            }
            res[other] += res[root] - (res[other] + n_childs[other])
                + (n_nodes - n_childs[other]);
            dfs_children(other);
        }
    }
};


//// time limit
//
// class Solution {
//  public:
//     vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
//         vector<vector<int>> dists(N, vector<int>(N, 0));
//         vector<vector<bool>> visited;
//         for (auto &el : edges) {
//             dists[el[0]][el[1]] = 1;
//             dists[el[1]][el[0]] = 1;
//         }
//         for (int i{0}; i < N; ++i) {
//             for (int j{i}; j < N; ++j) {
//                 if (i == j) {
//                     continue;
//                 }
//                 if (dists[i][j] == 0) {
//                     visited.assign(N, vector<bool>(N, false));
//                     int d = fill_dist(dists, visited, i, j);
//                     dists[i][j] = d;
//                     dists[j][i] = d;
//                 }
//             }
//         }
//         vector<int> res(N, 0);
//         for (int i{0}; i < N; ++i) {
//             for (int j{0}; j < N; ++j) {
//                 res[i] += dists[i][j];
//             }
//         }
//         return res;
//     }
//
//     int fill_dist(vector<vector<int>>& dist, vector<vector<bool>> visited, int i, int j) {
//         if (dist[i][j] != 0) {
//             return dist[i][j];
//         }
//         if (i == j) {
//             return 0;
//         }
//         int N = dist.size();
//         int min = 10000000;
//         for (int k = 0; k < N; ++k) {
//             if (k == i || k == j) {
//                 continue;
//             }
//             if (visited[i][k] || visited[k][j]) {
//                 continue;
//             }
//             visited[i][k] = visited[k][j] = true;
//             int d = fill_dist(dist, visited, i, k) + fill_dist(dist, visited, k, j);
//             if (d < min) {
//                 min = d;
//             }
//         }
//         return min;
//     }
// };


int main() {
    Solution sol;
    // int N = 6;
    // vector<vector<int>> edges{{0, 1}, {0, 2}, {2, 3}, {2, 4}, {2, 5}};
    // int N = 8;
    // vector<vector<int>> edges{{0, 6}, {2, 1}, {7, 0}, {6, 1}, {5, 0}, {5, 3}, {1, 4}};
    int N = 1;
    vector<vector<int>> edges{};
    auto res = sol.sumOfDistancesInTree(N, edges);
    for (auto &el : res) {
        cout << el << ", ";
    }
    cout << endl;
    return 0;
}
