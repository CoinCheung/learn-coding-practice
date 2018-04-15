#include<iostream>
#include<sstream>


using namespace std;


string mult_int(string& product, string mul);
void string2num(string& input);
void num2string(string& input);
void remove_zero(string& input);
int remove_dot(string& input);
void add_int(string& res, string& middle, int offset);
void add_dot(string& input, int dot_num);


int main()
{
    int n;
    stringstream ss;
    string mul;
    string product;
    int dot_num{0};

    while (cin >> mul >> n)
    {
        dot_num = remove_dot(mul);
        product = string(mul);

        string2num(mul);
        string2num(product);

        if (n == 0)
            cout << "1" << endl;
        else if (product == "0")
            cout << "0" << endl;
        else
        {
            for (int i{0}; i < n-1; i++)
            {
                product = mult_int(product, mul);
            }

            num2string(product);
            add_dot(product, n*dot_num);
            cout << product << endl;
        }
    }

    return 0;
}



string mult_int(string& product, string mul)
{
    int size1, size2;

    size1 = static_cast<int>(product.size());
    size2 = static_cast<int>(mul.size());

    string res(size1+size2, 0);
    string middle(size1+1, 0);
    int ind;
    char count{0};
    for (int i{size2-1}; i >= 0; i--)
    {
        middle[0] = 0;
        count = 0;
        for (int j{size1-1}; j >= 0; j--)
        {
            ind = j + 1;
            middle[ind] = product[j] * mul[i] + count;
            if (middle[ind] >= 10)
            {
                count = middle[ind] / 10;
                middle[ind] = middle[ind] % 10;
            }
            else
                count = 0;
        }
        middle[0] += count;
        add_int(res, middle, size2-1-i);
    }

    return res;
}



void string2num(string& input)
{
    remove_zero(input);
    int size{static_cast<int>(input.size())};

    for (int i{0}; i < size; i++)
        input[i] -= 48;
}


void num2string(string& input)
{
    int size{static_cast<int>(input.size())};

    for (int i{0}; i < size; i++)
        input[i] += 48;
}


void add_int(string& res, string& middle, int offset)
{
    int size_mid{static_cast<int>(middle.size())};
    int size_res{static_cast<int>(res.size())};
    int pos{size_res-1-offset};
    char count{0};

    for (int i{size_mid-1}; pos >= 0; i--, pos--)
    {
        res[pos] += count;
        if (i >= 0)
            res[pos] += middle[i];
        if (res[pos] >= 10)
        {
            res[pos] -= 10;
            count = 1;
        }
        else
            count = 0;
    }
}


void add_dot(string& input, int dot_num)
{
    int size{static_cast<int>(input.size())};
    string token;

    if (dot_num >= size)
    {
        token = string(dot_num - size + 1, '0');
        token[0] = '.';
        input.insert(0, token);
    }
    else
    {
        input.insert(size - dot_num, ".");
        remove_zero(input);
    }
}


void remove_zero(string& input)
{
    int start{0};
    int size{static_cast<int>(input.size())};
    int end{size - 1};
    char flag;

    while(start < end)
    {
        flag = 0;
        if (input[start] == '0')
            start ++;
        else
            flag += 1;
        if (input[end] == '0')
            end --;
        else
            flag += 1;

        if (flag == 2 || start >= end)
            break;
    }

    if (input.rfind(".", end) != string::npos)
    {
        if (input[end] == '.')
            end --;
        else if (input[start] == '.')
            start --;

        if (start > end)
            input = string("0");
        else
            input = input.substr(start, end + 1 - start);
    }
    else
        input = input.substr(start, size - start);
}



int remove_dot(string& input)
{
    int dot_num{0};
    size_t dot_pos;
    int len{2};

    remove_zero(input);

    dot_pos = input.rfind('.');
    if (dot_pos != string::npos)
    {
        dot_num = input.size() - 1 - static_cast<int>(dot_pos);
        if (dot_pos == 1 && input[0] == '0')
        {
            while(input[len] == '0')
                len ++;
            input.replace(0, len, "");
        }
        else
            input.replace(dot_pos, 1, "");
    }
    else
        dot_pos = 0;

    return dot_num;
}
