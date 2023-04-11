#include <iostream>
#include "../include/hjs/hjs.hpp"

int main()
{
    hjs_create_index();
    hjs_create_group("testgroup");
    hjs_create_group("testgroup2");

    /*hjs_delete_group("testgroup");
    for (const auto& group : hjs_list_groups()) {
        std::cout << group << std::endl;
    }*/



    std::cout << hjs_get_float_element("testgroup2", "testelement1") << std::endl;
    std::cout << hjs_get_int_element("testgroup", "testelement") << std::endl;
    std::cout << hjs_get_bool_element("testgroup", "testelement2") << std::endl;
    std::cout << hjs_get_string_element("testgroup", "testelement") << std::endl;
    std::cout << hjs_get_element_type("testgroup", "testelement") << std::endl;

}