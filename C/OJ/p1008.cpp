#include<iostream>
#include<iomanip>
#include<string>
#include<sstream>


int main()
{
    using namespace std;
    std::ios_base::sync_with_stdio(false);

    string HaabMonth[] = {"pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", "chen", "yax", "zac", "ceh", "mac", "kankin", "muan", "pax", "koyab", "cumhu", "uayet"};
    string TzolkinMonth[] = {"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"};

    stringstream ss;
    int num;
    string line;
    long all_days, remain_days;
    int hday, hmonth, hyear;
    string mth;
    int tds, tdn, tyear;

    cin >> num;
    cout << num << '\n';

    for (int i{0}; i < num; i++)
    {
        cin >> hday;
        cin.ignore();
        cin >> mth >> hyear;

        for (hmonth = 0; hmonth < 19; hmonth++)
            if (HaabMonth[hmonth] == mth)
                break;

        if (hmonth != 18)
            all_days = 365 * hyear + hmonth * 20 + hday;
        else
            all_days = 365 * hyear + 360 + hday;

        tyear = all_days / 260;
        remain_days = all_days % 260;
        tds = remain_days % 20;
        tdn = remain_days % 13 + 1;
        cout << tdn << " " << TzolkinMonth[tds] << " " << tyear << '\n';

    }

    return 0;
}
