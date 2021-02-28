//
// Created by huiyan on 2021/2/28.
//
#include <iostream>

#include "step1_config.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        // report version
        std::cout << argv[0] << " Version " << Step1_VERSION_MAJOR << "."
                  << Step1_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }
    return 0;
}