#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;


void solve_radar();
class Interval {
    public: 
        double left;
        double right;
        Interval() {left=0; right=0;}
};
bool compare(const Interval&, const Interval&);


int main() {
    std::ios_base::sync_with_stdio(false);
    solve_radar();
    return 0;
}


bool compare(const Interval& a, const Interval& b) {return a.left < b.left;}

void solve_radar() {
    int n, d, d2;
    vector<Interval> intervals(1000);
    int x, y;
    int c{0};
    while (true) {
        cin >> n >> d;
        if (n==0 && d==0) break;
        d2 = d * d;
        bool no_solution = false;
        c += 1;
        for (int i{0}; i < n; ++i) {
            cin >> x >> y;
            if (y > d) {
                no_solution = true;
                break;
            }
            double range = sqrt(d2 - y*y);
            intervals[i].left = x - range;
            intervals[i].right = x + range;
        }
        if (no_solution) {
            cout << "Case " << c << ": " << -1 << endl;
        } else {
            std::sort(intervals.begin(), intervals.begin()+n, compare);
            double pos{intervals[0].right};
            int count{0};
            for (int i{0}; i < n; ++i) {
                if (i==0) {
                    count += 1;
                    continue;
                }
                if (intervals[i].left <= pos) {
                    if (intervals[i].right < pos) {
                        pos = intervals[i].right;
                    } 
                } else {
                    pos = intervals[i].right;
                    count += 1;
                }
            }
            cout << "Case " << c << ": " << count << endl;
        }
    }
}
