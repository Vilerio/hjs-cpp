#ifndef HJS_INDEX_H
#define HJS_INDEX_H

#include <iostream>
#include <string>
#include "../json.hpp"
#include <fstream>

std::string hjs_get_index(){
    // Open conf.json
    std::ifstream json_mainconf_file("/Users/olivier/Documents/Dev/C++/hjs/labo/conf.json");
    nlohmann::json json_mainconf_file_values;
    json_mainconf_file >> json_mainconf_file_values;
    json_mainconf_file.close();

    std::string index_file = (json_mainconf_file_values["storage_directory"].dump()).substr(1, json_mainconf_file_values["storage_directory"].dump().length() - 2) + "/index.json";

    // Open index.json
    std::ifstream json_index_file(index_file);
    nlohmann::json json_index_file_values;
    json_index_file >> json_index_file_values;
    json_index_file.close();

    // Print index.json values
    std::cout << json_index_file_values.dump() << std::endl;

    return json_index_file_values.dump();
}

#endif // HJS_INDEX_H