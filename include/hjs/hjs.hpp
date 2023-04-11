#ifndef HJS_HJS_H
#define HJS_HJS_H

#include <iostream>
#include <string>
#include "../json.hpp"
#include <fstream>
#include "hjs-index.hpp"
#include <ctime>

using json = nlohmann::json;

std::string storage_directory(){
    // Open conf.json
    std::ifstream json_mainconf_file("/Users/olivier/Documents/Dev/C++/hjs/labo/conf.json");
    nlohmann::json json_mainconf_file_values;
    json_mainconf_file >> json_mainconf_file_values;
    json_mainconf_file.close();

    return (json_mainconf_file_values["storage_directory"].dump()).substr(1, json_mainconf_file_values["storage_directory"].dump().length() - 2);

}

bool already_init(){
    // Open conf.json
    std::ifstream json_mainconf_file("/Users/olivier/Documents/Dev/C++/hjs/labo/conf.json");
    nlohmann::json json_mainconf_file_values;
    json_mainconf_file >> json_mainconf_file_values;
    json_mainconf_file.close();

    bool already_configured_bool = json_mainconf_file_values["already_configured"].get<bool>();

    return already_configured_bool;
}

void hjs_init(std::string directory){
    if (already_init()){
        std::cout << "HJS is already configured." << std::endl;
    }
    else{
        // Open conf.json
        //std::ifstream json_mainconf_file("../conf.json");
        std::ifstream json_mainconf_file("/Users/olivier/Documents/Dev/C++/hjs/labo/conf.json");
        nlohmann::json json_mainconf_file_values;
        json_mainconf_file >> json_mainconf_file_values;
        json_mainconf_file.close();

        json_mainconf_file_values["already_configured"] = true;
        json_mainconf_file_values["storage_directory"] = directory;

        // Open conf.json in writing mode
        std::ofstream json_mainconf_file_write("/Users/olivier/Documents/Dev/C++/hjs/labo/conf.json");
        json_mainconf_file_write << json_mainconf_file_values;
        json_mainconf_file_write.close();

        std::cout << "HJS is now configured." << std::endl;
    }
}

void hjs_create_index(){
    std::ifstream index_file(storage_directory() + "/index.json");
    if (!index_file.good()) {

        json futur_index_values;
        futur_index_values["actual_index"] = true;
        std::ofstream index_file(storage_directory() + "/index.json");
        index_file << futur_index_values.dump();
        index_file.close();
    }
    else{
        std::cout << "The index already exists." << std::endl;
    }
}

void hjs_create_group(std::string group_name){
    std::ifstream index_file(storage_directory() + "/index.json");
    json index_values;
    index_file >> index_values;
    index_file.close();

    if (!index_values["actual_index"].get<bool>()) {
        std::cout << "Error: index is not initialized." << std::endl;
        return;
    }

    if (index_values.find(group_name) != index_values.end()) {
        std::cout << "Error: group already exists." << std::endl;
        return;
    }

    json new_group;
    new_group["data"] = json::array();

    index_values[group_name] = new_group;

    std::ofstream index_file_write(storage_directory() + "/index.json");
    index_file_write << index_values.dump(4);
    index_file_write.close();

    std::cout << "Group \"" << group_name << "\" created successfully." << std::endl;
}

#endif // HJS_HJS_H
