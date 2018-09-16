#include<unordered_map>
#include<string>
#include<iostream>
#include<iterator>
#include<utility>


using std::unordered_map;
using std::string;
using std::cout;
using std::endl;
using std::pair;
using std::make_pair;
using std::pair;


void do_it();


int main() {
    do_it();
    return 0;
}



void do_it() {
    unordered_map<long, string> ump({{1, "fuck"}, {2, "you"}});
    // unordered_map<long, string> ump2{{1, "fuck"}, {2, "you"}};
    unordered_map<long, string> ump2;
    unordered_map<long, string>(ump).swap(ump2);

    pair<long, string> mypair(4, "hello");

    ump.insert(make_pair<long, string>(3, "what"));
    ump.insert(make_pair<long, string>(3, "wh0"));
    ump.insert(mypair);
    mypair.first = 8;
    ump.insert({{5, "five"}, {6, "six"}});
    ump[7] = "seven";
    ump[7] = "seveiiiiiin";
    ump.insert({{5, "fddive"}, {6, "sddix"}});
    ump[18] = "eight";

    for (auto& el : ump) cout << el.first << el.second << endl;
    cout << ump2[2] << endl;
    cout << ump.count(3) << endl;
    cout << mypair.first << endl;
    // cout << ump.find(666)->first << endl;
    // cout << ump.find(666)->second << endl;
    cout << ump.size() << endl;
    cout << ump.bucket(999) << endl;
    cout << ump.bucket_count() << endl;
    ump.clear();
    cout << ump.bucket_count() << endl;
    ump.reserve(300);
    cout << ump.bucket_count() << endl;

}
