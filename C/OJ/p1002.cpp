#include<iostream>
#include<iomanip>
#include<string>
#include<map>

/* 1. 前导零
 * 2. ss转化和字符串表示num速度太慢了。 
 * 3. 输入输出用cin + string太慢了，还是用scanf+char[]更快些
 * 4. No duplicates. 后面要有一个句号才行。
 * 5. 实测string 比 char[]或者const char * 要慢很多
 * 6. cin 比scanf慢很多
 * */


// int get_tele_num(char*);
int get_tele_num(std::string&);


int main()
{
    using namespace std;

    int num;
    // char input[128];
    string input;
    int tele_num;
    map<int, long> num_map;
    map<int, long>::iterator it;
    map<int, long>::iterator it_end;
    bool has_dup{false};

    std::ios_base::sync_with_stdio(false);

    cin >> num;

    for (int i{0}; i < num; i++)
    {
        // scanf("%s", input);
        cin >> input;
        tele_num = get_tele_num(input);
        num_map[tele_num] ++;
    }

    it = num_map.begin();
    it_end = num_map.end();
    while (it != it_end)
    {
        if (it->second > 1)
        {
            has_dup = true;
            cout << setw(3) << setfill('0') << it->first / 10000 << "-" << setw(4) <<setfill('0') << it->first % 10000 << " " << it->second << endl;
        }
        it ++;
    }

    if (!has_dup)
        cout << "No duplicates." << endl;

    return 0;
}


// int get_tele_num(char* input)
int get_tele_num(std::string& input)
{
    using namespace std;

    const char *maptable{"2223334445556667077888999"};
    // static string maptable("2223334445556667077888999");
    int res{0};
    int size{static_cast<int>(input.size())};

    // for (int i{0}; input[i]; i++)
    for (int i{0}; i < size; i++)
    {
        if (input[i] >= '0' && input[i] <= '9')  // pass number directly
        {
            res = 10 * res + input[i] - '0';
        }
        else if (input[i] >= 'A' && input[i] <= 'Z')  // pass upper case
        {
            res = 10 * res + maptable[input[i] - 'A'] - '0';
        }
    }

    return res;
}
