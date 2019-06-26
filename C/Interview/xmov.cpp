#include<iostream>
#include<vector>

using std::vector;
using std::cout;
using std::endl;

int require = 100;

int main() {
    int pos{0};
    int i{1};
    int remain;
    vector<int> steps;

    while (true) {
        steps.push_back(i);
        pos += i++;
        if ((pos > require) && ((pos - require) % 2 == 0)) {
            remain = (pos - require) / 2;
            steps[remain - 1] = - remain;
            cout << "remain is: " << remain << endl;
            break;
        }
    }
    cout << "the steps are: \n";
    for (auto& step : steps) cout << step << ",";
    cout << endl;
    int sum{0};
    for (auto& step : steps) sum += step;
    cout << sum << endl;

    return 0;
}
