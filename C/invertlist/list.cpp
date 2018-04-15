#include<memory>
#include<iostream>
#include"list.h"


// add a node with value val to the list
void list::add(int val)
{
    using namespace std;

    shared_ptr<node> n(new node(val));
    n->next = head;
    head = n;
    len ++;
}


// print the contents of the list from head towards rear
void list::print()
{
    using namespace std; 

    shared_ptr<node> sp;

    sp = head;
    while(sp != nullptr)
    {
        cout << sp->data << " ";
        sp = sp->next;
    }
    cout << endl;
}


// implement list inversion with traverse method
void list::invert_traverse()
{
    using namespace std;

    shared_ptr<node> p1{nullptr}, p2{nullptr}, p3{nullptr};

    if(head == nullptr || head->next == nullptr)
        return;

    p1 = head;
    if(p1->next != nullptr)
        p2 = p1->next;
    if(p2->next != nullptr)
        p3 = p2->next;

    p1->next = nullptr;

    while(p3 != nullptr)
    {
        p2->next = p1;
        p1 = p2;
        p2 = p3;
        p3 = p2->next;
    }

        p2->next = p1;
        head = p2;
}


// implement list inversion with construction method
void list::invert_copy_new()
{
    using namespace std;

    shared_ptr<node> old_head(head), temp;

    if(head == nullptr)
        return;

    head = old_head;
    old_head = old_head->next;
    head->next = nullptr;

    while(old_head != nullptr)
    {
        temp = old_head;
        old_head = old_head->next;
        temp->next = head;
        head = temp;
    }
    
}

