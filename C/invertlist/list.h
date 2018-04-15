#include<memory>


class node
{
    public:
        int data;
        std::shared_ptr<node> next;

        node(int val):data(val){}
};


class list
{
    public:
        std::shared_ptr<node> head;
        int len;

        list():head(nullptr), len(0){}

        void add(int val);
        void print();
        void clear();

        void invert_copy_new();
        void invert_traverse();
};
