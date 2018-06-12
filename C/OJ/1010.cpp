#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<iterator>
#include<stdio.h>  // for EOF

// TODO: refine the format

bool compare(int a, int b) {return a < b;}

class Solution {
    public:
        int type_num;  // num of stamp types
        int res_num;  // num of stamps
        int sum;
        int largest;
        bool tie;
        std::vector<int> values;
        std::vector<int> types;

        Solution();
        void init();
        void compute_sum(int pos);
        bool is_in_range(int require);
        void compute_all();
        Solution& operator=(const Solution&);
        bool is_equal(Solution&);
};

Solution::Solution() {
    values.reserve(4);
}

void Solution::init() {
    type_num = 0;
    res_num = 0;
    sum = 0;
    largest = -1;
}

void Solution::compute_sum(int pos) {
    sum = 0;
    for (int i{0}; i <= pos; i++) {
        sum += values[i];
    }
}

inline bool Solution::is_in_range(int req) {
    return sum <= req;
}

void Solution::compute_all() {
    int val;
    std::map<int, int> unique_vals;

    init();
    for (int i{0}; i < 4; i++) {
        val = values[i];
        if (val != 0) {
            sum += val;
            res_num ++;

            if (unique_vals.count(val) == 0) {
                unique_vals[val] = 1;
            } else unique_vals[val] ++;
        }
        if(val > largest) largest = val;
    }
    tie = false;
    std::map<int, int>::iterator begin = unique_vals.begin();
    std::map<int, int>::iterator end = unique_vals.end();
    for (std::map<int, int>::iterator iter = begin; iter != end; iter++) {
        val = iter->first;
        if (types[val] < iter->second) {
            type_num += types[val];
        } else type_num += iter->second;
        if (types[val] != iter->second && types[val] > 1) tie = true;
    }
}

Solution& Solution::operator=(const Solution& sol) {
    type_num = sol.type_num;
    res_num = sol.res_num;
    sum = sol.sum;
    largest = sol.largest;
    values.assign(sol.values.begin(), sol.values.end());
    std::sort(values.begin(), values.end(), compare);
    return *this;
}

bool Solution::is_equal(Solution& sol) {
    using namespace std;
    int ind1[4];
    for (int i{0}; i < 4; i ++) {
        ind1[i] = sol.values[i];
    }
    std::sort(ind1, ind1 + 4);
    for (int i{0}; i < 4; i ++) {
        if (ind1[i] != 0) {
            if (ind1[i] != values[i]) return false;
        }
    }
    return true;
}

class Stamp {
    public:
        bool tie;
        bool none;
        // std::vector<int> customers;
        int customer;
        Solution curr;
        Solution best;

        Stamp();
        void init();
        void solve();
        void one_custom(int);
        void get_best(int require);
        void print(int require);

        // debug
        std::vector<int> types;  // stamp of value i has types[i] repeats
        std::vector<int> values;
        int largest_value;
        void print_enum();
        void update();
};


Stamp::Stamp() {
    types.reserve(26);
    values.reserve(26);
}

void Stamp::init() {

    types.assign(26, 0);
    types[0] = 1;
    values.clear();
    values.push_back(0);
}

void Stamp::solve() {
    for (int i{0}; i <= largest_value; i++) {
        if (types[i] > 0)
            values.push_back(i);
    }
    one_custom(customer);
    print(customer);
}

void Stamp::one_custom(int require) {
    int stamp_size;
    best.init();
    stamp_size = static_cast<int>(values.size());
    tie = false;

    for (int i0{0}; i0 < stamp_size; i0 ++) {
        curr.values[0] = values[i0];
        curr.compute_sum(0);
        if (!curr.is_in_range(require)) break;

        for (int i1{0}; i1 < stamp_size; i1 ++) {
            curr.values[1] = values[i1];
            curr.compute_sum(1);
            if (!curr.is_in_range(require)) break;

            for (int i2{0}; i2 < stamp_size; i2 ++) {
                curr.values[2] = values[i2];
                curr.compute_sum(2);
                if (!curr.is_in_range(require)) break;

                for (int i3{0}; i3 < stamp_size; i3 ++) {
                    curr.values[3] = values[i3];

                    curr.compute_all();
                    if (!curr.is_in_range(require)) break;
                    // for (int i{0}; i < 4; i++)
                    //     std::cout << curr.values[i] << ", ";
                    // std::cout << std::endl;
                    get_best(require);
                }
            }
        }
    }
    // see style here
    if (best.type_num == 0) none = true;
    else none = false;
}

void Stamp::get_best(int require) {
    // return directly if current solution does not meet require
    if (curr.sum != require) return;
    // if no previous best solutions computed
    if (best.type_num == 0) {
        tie = false;
        best = curr;
        return;
    }
    // see if there is a tie 
    if (best.type_num < curr.type_num) {
        tie = false;
        best = curr;
        return;
    } else if (best.type_num == curr.type_num) {
        if (best.res_num > curr.res_num) {
            tie = false;
            best = curr;
            return;
        } else if (best.res_num == curr.res_num) {
            if (curr.largest > best.largest) {
                tie = false;
                best = curr;
                return;
            } else if (curr.largest == best.largest) {
                // std::cout << "herere" << std::endl;;
                // std::cout << best.is_equal(curr) << std::endl;
                // for (int i{0}; i < 4; i++)
                //     std::cout << curr.values[i].first << " ,";
                // std::cout << std::endl;
                // for (int i{0}; i < 4; i++)
                //     std::cout << best.values[i].first << " ,";
                // std::cout << std::endl;

                if (curr.tie)  {
                    tie = true;
                    return;
                }
                if (best.is_equal(curr)) return;
                tie = true;
            }
        }
    }
}


void Stamp::print(int require) {
    using namespace std;
    std::ios_base::sync_with_stdio(false);

    if (none) {
        cout << require << " ---- none\n";
    } else if (tie) {
        cout << require << " (" << best.type_num << "): tie\n";
    } else {
        /////////////////
        // cout << best.values[0] << endl;
        // cout << best.values[1] << endl;
        // cout << best.values[2] << endl;
        // cout << best.values[3] << endl;
        // for (auto& el:best.values)
        //     cout << el << ", ";
        // cout << endl;
        /////////////////
        cout << require << " (" << best.type_num << "): ";
        for (int i{0}; i < 3; i ++) {
            if (best.values[i] != 0) {
                cout << best.values[i] << " ";
            }
        }
        cout << best.values[3] << '\n';
    }
}


void Stamp::update() {
    curr.types = types;
}



int main() {
    using namespace std;
    std::ios_base::sync_with_stdio(false);

    Stamp stmp;
    int n;

    while (cin >> n) {
        stmp.init();

        // cin >> n;
        // if (n == EOF) exit(0);

        stmp.largest_value = 0;
        while (n != 0) {
            if (stmp.types[n] < 5) {
                if (n > stmp.largest_value) stmp.largest_value = n;
                stmp.types[n] ++;
            }
            cin >> n;
        }
        stmp.update();

        while (cin >> stmp.customer) {
            if (stmp.customer == 0) break;
            stmp.solve();
        }
    }
    return 0;
}

