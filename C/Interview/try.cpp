#include<iostream>
#include<sstream>


void unzip (const char* input, char* output);
void unzip1 (const char* input, char* output);


int main()
{
    using namespace std;

    // const char *str = "dstigjfidgjsrdditjrea";
    // const char *str = "dsti4gjfidgjsrdditjrea";
    // const char *str = "4dstigjfidgjsrdditjre4a";
    // const char *str = "4dstigjfidgjsrdditjre4a7";
    // const char *str = "4dstigjfidgjsrdditjre4a74343";
    // const char *str = "4dstigjfidgjsrddit1jre4a";
    // const char *str = "4dstigjfidgjsrd2ditjre4a";
    // const char *str = "4dstigjfidgj9srdditjre3434a";
    // const char *str = "dstigjfidgj9srdditjre4a";
    const char *str = "abcdefg";
    char *res{nullptr};
    unzip1(str, res);
}

void unzip (const char* input, char* output)
{
    using namespace std;

    int len{0};
    int ind{0};

    while (input[ind] != 0)
    {
        if (input[ind] > 50 && input[ind] < 58) // number
        {
            len += input[ind] + static_cast<int>(input[ind]) - 48;
            ind ++;
            if (input[ind] == 0  || (input[ind] >47 && input[ind] < 58)) 
            {
                    cout << "!error" << endl;
                    return;
            }
        }
        else if (input[ind] > 96 && input[ind] < 123) // letter
        {
            len ++;
        }
        else
        {
            cout << "!error" << endl;
            return;
        }
        ind ++;
    }

    len ++;
    ind = 0;
    output = new char[len];
    output[len-1] = 0;
    int pos{0};
    char c;
    int num{0};
    while (input[ind] != 0)
    {
        if (input[ind] > 47 && input[ind] < 58) // number
        {
            num = static_cast<int>(input[ind++]) - 48;
            cout << "num " << num << endl;
            c = input[ind];
            for (int i{0}; i < num; i++)
                output[pos++] = c;
        }
        else if (input[ind] > 96 && input[ind] < 123) // letter
        {
            output[pos++] = input[ind];
        }
        ind ++;
    }

    string str(output);
    cout << input << endl;
    cout << str << endl;

}


void unzip1 (const char* input, char* output)
{
    using namespace std;

    stringstream ss;
    stringstream out;
    char c;
    int num{44};

    ss << input;
    while(ss >> c)
    {
        if (c > 47 && c < 58) // number
        {
            // cout << c << endl;
            ss.clear();
            ss.seekg(-1, ios::cur);
            ss.clear();
            // cout << c << endl;
            ss >> num;
            if (!(ss >> c) || num <= 2)
            {
                cout << "!error: num " << num << endl;
                cout << c << endl;
                return;
            }
            for (int i{0}; i < num; i++)
                out << c;
        }
        else if (c > 96 && c < 123) // letter
            out << c;
        else
        {
            cout << "!error else" << endl;
            return;
        }
    }

    // const char* cp =  out.str().c_str();
    const char* cp = "fdsfdff";
    output = new char[out.str().length() + 1];
    std::copy(out.str().c_str(), out.str().c_str() + out.str().length() + 1, output);

    string res(output);
    // cout << res << endl;
    cout << output << endl;
    // cout << out.str().c_str() << endl;

    // cout << "new" << endl;
    // ss.clear();
    // ss << "123456";
    // cout << ss.str() << endl;
    // // ss.seekp(-3, ios::cur);
    // ss << "dfs";
    // cout << ss.str() << endl;

}
