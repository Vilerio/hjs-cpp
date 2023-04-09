#ifndef HJS_HJS_H
#define HJS_HJS_H
#include <iostream>
#include <string>

bool already_init{
    return false;
};

void hjs_init(std::string directory){
    if (already_init){
        std::cout << "HJS is already configured." << std::endl;
    }
    else{
        std::cout << "Initialization of HJS..." << std::endl;
        std::string directory;
        std::cout << "Where do you want to install HJS ?" << "\n : ";
        std::cin directory;
    }
}
#endif HJS_HJS_H
