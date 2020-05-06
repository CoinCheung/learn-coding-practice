%module mymod

%{
    #define SWIG_FILE_WITH_INIT
    extern void Print();
    extern int addadd(int a,int b);

    extern int num;

%}
    
    void Print();
    int addadd(int a,int b);
    int num;

