#include<iostream>
#include<vector>
#include<map>



class Diff
{
    public:
        std::vector<int> pixs;
        std::vector<int> lens;
        std::vector<int> starts;
        std::map<long, int> res;
        long width;
        long height;
        long img_size;

        Diff();
        void reset();
        int compute_diff(long pos, long pos_neighbor);
        int get_pix(long pos);
        void compute_one_pos(long pos);
        void print();
};



Diff::Diff()
{
    pixs.reserve(1000);
    lens.reserve(1000);
    starts.reserve(1001);
}

void Diff::reset()
{
    pixs.clear();
    lens.clear();
    starts.clear();
    res.clear();
}



int main()
{
    using namespace std;
    std::ios_base::sync_with_stdio(false);

    long width, height;
    int pix;
    int len;
    long size{0};
    long pos;
    int posw, posh;
    Diff diff;

    while (true)
    {
        diff.reset();

        cin >> width;
        cout << width << '\n';
        if (width == 0)
            break;

        size = 0;
        diff.starts.push_back(0);
        while (true)
        {
            cin >> pix >> len;
            size += len;

            if (pix == 0 && len == 0)
                break;
            diff.pixs.push_back(pix);
            diff.lens.push_back(size);
            diff.starts.push_back(size);
        }
        diff.pixs.push_back(pix);  // 这里需要再加上一个，因为不止需要计算连续段的开头，还需要计算最后一个的结尾

        height = size / width;
        diff.width = width;
        diff.height = height;
        diff.img_size = size;

        for (int i{0}; i < static_cast<int>(diff.pixs.size()); i ++)
        {
            posh = diff.starts[i] / width;
            posw = diff.starts[i] % width;

            for (int row{posh - 1}; row <= posh + 1; row ++)
                for (int col{posw - 1}; col <= posw + 1; col ++)
                {
                    pos = row * width + col;

                    if (pos < 0 || pos >= size)
                        continue;
                    diff.compute_one_pos(pos);
                }
        }

        diff.print();
    }

    return 0;
}


int Diff::compute_diff(long pos, long pos_neighbor)
{
    int curr, neighbor;
    int diff;

    curr = -1;
    neighbor = -1;

    curr = get_pix(pos);
    neighbor = get_pix(pos_neighbor);

    if (curr > neighbor)
        diff = curr - neighbor;
    else
        diff = neighbor - curr;

    return diff;
}


int Diff::get_pix(long p)
{
    int val;
    long size{static_cast<int>(lens.size())};

    for (int i{0}; i < size; i++)
        if (lens[i] > p)
        {
            val = pixs[i];
            break;
        }
    return val;
}


void Diff::compute_one_pos(long pos)
{
    int diff;
    int diff_max{-1};
    long nei;
    int row, col;

    if (res.count(pos) != 0)
        return;

    row = pos / width;
    col = pos % width;

    for (int i{row - 1}; i <= row + 1; i ++)
        for (int j{col - 1}; j <= col + 1; j ++)
        {
            if (i < 0 || j < 0 || i >= height || j >= width || (i == row && j == col))
                continue;
            else
            {
                nei = i * width + j;
                diff = compute_diff(pos, nei); 
                if (diff > diff_max)
                    diff_max = diff;
            }
        }
    res[pos] = diff_max;
}




void Diff::print()
{
    using namespace std;
    std::ios_base::sync_with_stdio(false);

    int val_pre;
    int len;
    long pos_pre{0};
    std::map<long, int>::iterator it_end(res.end());
    std::map<long, int>::iterator it(res.begin());

    val_pre = it->second;
    while(true)
    {
        it ++;
        if (it == it_end)
            break;
        if (val_pre != it->second)
        {
            len = it->first - pos_pre;
            std::cout << val_pre << " " << len << '\n';
            pos_pre = it->first;
            val_pre = it->second;
        }
    }
    std::cout << val_pre << " " << img_size - pos_pre << '\n';
    std::cout << "0 0" << '\n';

}
