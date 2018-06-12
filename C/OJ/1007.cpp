#include<iostream>
#include<string>
#include<vector>
#include<algorithm>


class Order
{
    public:
        int len;
        int order;
        int nums[4];

        Order(int len): len(len), order(0){};
        int compute_order(std::string& str);
};


class SE
{
    public:
        std::string se;
        int order;

        SE(){}
        SE(std::string& str, Order& order);
};


SE::SE(std::string& str, Order& ord)
{
    se = str;
    order = ord.compute_order(str);
}


bool compare(const SE&, const SE&);

int main()
{
    using namespace std;
    std::ios_base::sync_with_stdio(false);

    int num;
    int len;

    cin >> len;
    cin >> num;

    Order order(len);
    string str;
    vector<SE> seqs(num);
    vector<SE>::iterator it_beg;
    vector<SE>::iterator it_end;
    SE se;


    for (int i{0}; i < num; i++)
    {
        cin >> str;
        // se.se = str;
        // se.order = order.compute_order(str);
        // seqs.push_back(se);
        seqs.push_back(SE(str, order));
    }

    it_beg = seqs.begin();
    it_end = seqs.end();

    stable_sort(it_beg, it_end, compare);

    for (vector<SE>::iterator it(it_beg); it != it_end; it++)
        cout << it->se << '\n';

    return 0;
}


int Order::compute_order(std::string& str)
{
    order = 0;
    for (int i{0}; i < 4; i++) 
        nums[i] = 0;

    for (int i{0}; i < len; i++)
    {
        if (str[i] == 'A')
        {
            order = order + nums[1] + nums[2] + nums[3];
            nums[0] ++;
        }
        else if (str[i] == 'C')
        {
            nums[1] ++;
            order = order + nums[2] + nums[3];
        }
        else if (str[i] == 'G')
        {
            nums[2] ++;
            order = order + nums[3];
        }
        else
            nums[3] ++;
    }

    return order;
}


bool compare(const SE& s1, const SE& s2)
{
    return s1.order < s2.order;
}
