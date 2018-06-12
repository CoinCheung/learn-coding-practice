#include<gflags/gflags.h>
#include"myflags.h"
#include<iostream>
#include<cstdlib>


using std::cout;
using std::endl;


int main(int argc, char** argv) {
    
    gflags::SetVersionString("version 0.0.1");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    cout << "bool is: " << FLAGS_option1 << endl;
    cout << "string is: " << FLAGS_option2 << endl;

    cout << "environ: " << std::getenv("PATH") << endl; 

    return 0;
}



