#include<iostream>
#include<vector>
#include<algorithm>


bool compare(int a, int b)
{
    return a > b;
}

class solution
{
    public:
        int type_num;
        int res_num;
        int sum;
        int largest;
        std::vector<int> values;
};

class Stamp
{
    public:
        bool tie;
        bool none;
        int best_type_num;
        int best_num;
        int best_largest;
        int sum;
        std::vector<int> best;
        std::vector<int> stamps;
        std::vector<int> customers;
        std::vector<int> res;
        std::vector<int> types;
        // solution curr;
        // solution best;

        Stamp(): best_type_num(0), best_num(0), best_largest(-1){res.reserve(4); best.reserve(4); types.reserve(4);}
        void init();
        void solve();
        void one_custom(int);
        void get_best(int require);
        bool is_in_range(int);  // return true is sum of res[] <= require
        void print(int require);
        void compute_curr();
};


int main()
{
    using namespace std;
    std::ios_base::sync_with_stdio(false);

    Stamp stmp;
    int n;

    while (true)
    {
        stmp.init();

        cin >> n;
        if (n == EOF)
            exit(0);

        while (n != 0)
        {
            stmp.stamps.push_back(n);
            cin >> n;
        }

        cin >> n;
        while (n != 0)
        {
            stmp.customers.push_back(n);
            cin >> n;
        }

        stmp.solve();


    }

    return 0;
}


void Stamp::init()
{
    stamps.clear();
    stamps.push_back(-1);
    customers.clear();
    best_type_num = 0;
    best_num = 0;
    best_largest = -1;
    tie = false;
}


void Stamp::solve()
{
    using namespace std;

    sort(stamps.begin() + 1, stamps.end(), compare);

    int customer_num{static_cast<int>(customers.size())};

    for (int i{0}; i < customer_num; i ++)
    {
        one_custom(customers[i]);
        print(customers[i]);
    }

}


void Stamp::one_custom(int require)
{
    int stamp_size;
    stamp_size = stamps.size();
    best.clear();
    for (int i0{0}; i0 < stamp_size; i0 ++)
    {
        res[0] =  stamps[i0];
        for (int i{1}; i < 4; i ++)
            res[i] = -1;
        if (!is_in_range(require))
            break;

        for (int i1{0}; i1 < stamp_size; i1 ++)
        {
            res[1] = stamps[i1];
            for (int i{2}; i < 4; i ++)
                res[i] = -1;
            if (!is_in_range(require))
                break;

            for (int i2{0}; i2 < stamp_size; i2 ++)
            {
                res[2] = stamps[i2];
                for (int i{3}; i < 4; i ++)
                    res[i] = -1;
                if (!is_in_range(require))
                    break;

                for (int i3{0}; i3 < stamp_size; i3 ++)
                {
                    res[3] = stamps[i3];
                    if (!is_in_range(require))
                        break;

                    get_best(require);  // see if res[] is the best, and store the best to array best[]. If there is tie, set flag tie=true
                }
            }
        }
    }
    if (best.size() == 0)
        none = true;
    else
        none = false;
}


bool Stamp::is_in_range(int require)
{
    sum = 0;
    int res_size{static_cast<int>(res.size())};

    for (int i{0}; i < res_size; i ++)
        if (res[i] != -1)
            sum += res[i];

    return sum <= require;
}


void Stamp::get_best(int require)
{
    int res_size{static_cast<int>(res.size())};
    int type_num{0};
    int res_num;

    if (sum == require)
    {
        types.clear();
        for(int i{0}; i < res_size; i++)
            if (res[i] != -1)
                types.push_back(res[i]);
        res_num = static_cast<int>(types.size());

        sort(types.begin(), types.end(), compare);
        types.erase(unique(types.begin(), types.end()), types.end());
        type_num = static_cast<int>(types.size());

        if (type_num > best_type_num)
        {
            tie = false;
            best_type_num = type_num;
            best_num = res_num;
            best_largest = types[0];
            std::swap(best, types);
        }
        else if (type_num == best_type_num)
        {
            if (res_num < best_num)
            {
                tie = false;
                best_type_num = type_num;
                best_num = res_num;
                best_largest = types[0];
                std::swap(best, types);
            }
            else if (res_num == best_num)
            {
                if (res[0] > best_largest)
                {
                    tie = false;
                    best_type_num = type_num;
                    best_num = res_num;
                    best_largest = types[0];
                    std::swap(best, types);
                }
                else if (res[0] == best_num)
                    tie = true;
            }
        }
    }


}


void Stamp::print(int require)
{
    using namespace std;
    std::ios_base::sync_with_stdio(false);

    // TODO:
    if (tie)
        cout << require << " (" << best_num << "): tie" << endl;
}
