#ifndef _MYFLAGS_H_
#define _MYFLAGS_H_

#include<gflags/gflags.h>
#include<string>
#include<iostream>

using std::string;
using std::cout;
using std::endl;




static bool ValidOption1(const char* name, bool arg);
static bool ValidOption2(const char* name, string arg);


DEFINE_bool(option1, true, "dfdfdfd");
DEFINE_string(option2, "fuck you asshole", "dfdfdfd");
static const bool option1_dummy = gflags::RegisterFlagValidator(&FLAGS_option1, &ValidOption1);


static bool ValidOption1(const char* name, bool arg) {
    if (string(name) == "option1") {
        if (arg) {
            cout << "option1 is true\n";
            return true;
        }
        else {
            cout << "option1 is false\n";
            return false;
        }
    } else {
        cout << "not option1\n";
        return false;
    }
}



static bool ValidOption2(const char* name, string arg) {
    return false;
}

#endif
