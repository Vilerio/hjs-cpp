#ifndef HJS_HJS_H
#define HJS_HJS_H
#include <iostream>
#include <string>
#include "json.hpp"

bool already_init{
    // Open conf.json
    std::ifstream json_mainconf_file("conf.json");
    nlohmann::json json_mainconf_file_values;
    json_mainconf_file >> json_mainconf_file_values;
    json_mainconf_file.close();
    json_mainconf_file_values["already_configured"] = already_configured_bool;
    return already_configured_bool;
};

void hjs_init(std::string directory){
    if (already_init){
        std::cout << "HJS is already configured." << std::endl;
    }
    else{
        // Open conf.json
        std::ifstream json_mainconf_file("conf.json");
        nlohmann::json json_mainconf_file_values;
        json_mainconf_file >> json_mainconf_file_values;
        json_mainconf_file.close();
        json_mainconf_file_values["storage_directory"] = actual_storage_directory;
        // Open conf.json in reading mode
        std::ofstream json_mainconf_file_write("conf.json");
        json_mainconf_file_write << json_mainconf_file_values;
        json_mainconf_file_write.close();
        std::cout << "HJS is now configured." << std::endl;
    }
}
#endif HJS_HJS_H
