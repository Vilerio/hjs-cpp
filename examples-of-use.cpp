#include <iostream>
#include "hjs.hpp"

int main()
{
    hjs_init("/home/hjs/storage");
    hjs_create_index();
    hjs_get_index();

}