#include <iostream>
#include "../include/hjs/hjs.hpp"

int main()
{
    hjs_init("/Users/olivier/Documents/Dev/C++/hjs/labo");
    hjs_create_index();
    hjs_get_index();
    hjs_create_group("testgroup");

}