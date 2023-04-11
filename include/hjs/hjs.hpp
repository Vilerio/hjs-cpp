#ifndef HJS_HJS_H
#define HJS_HJS_H

#include <iostream>
#include <string>
#include "../json.hpp"
#include <fstream>
#include <ctime>

using json = nlohmann::json;

std::string hjs_storage_directory(){
    // Open conf.json
    std::ifstream json_mainconf_file("/Users/olivier/Documents/Dev/C++/hjs/labo/conf.json");
    nlohmann::json json_mainconf_file_values;
    json_mainconf_file >> json_mainconf_file_values;
    json_mainconf_file.close();

    return (json_mainconf_file_values["storage_directory"].dump()).substr(1, json_mainconf_file_values["storage_directory"].dump().length() - 2);

}

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
    std::ifstream index_file(hjs_storage_directory() + "/index.json");
    if (!index_file.good()) {

        json futur_index_values;
        futur_index_values["actual_index"] = true;
        std::ofstream index_file(hjs_storage_directory() + "/index.json");
        index_file << futur_index_values.dump();
        index_file.close();
    }
    else{
        std::cout << "The index already exists." << std::endl;
    }
}

void hjs_create_group(std::string group_name){
    std::ifstream index_file(hjs_storage_directory() + "/index.json");
    json index_values;
    index_file >> index_values;
    index_file.close();

    if (!index_values["actual_index"].get<bool>()) {
        std::cout << "Error : index is not initialized." << std::endl;
        return;
    }

    if (index_values.find(group_name) != index_values.end()) {
        std::cout << "Error : group already exists." << std::endl;
        return;
    }

    json new_group;

    index_values[group_name] = new_group;

    std::ofstream index_file_write(hjs_storage_directory() + "/index.json");
    index_file_write << index_values.dump(4);
    index_file_write.close();

    std::cout << "Group \"" << group_name << "\" created successfully." << std::endl;
}

std::vector<std::string> hjs_list_groups() {
    std::ifstream index_file(hjs_storage_directory() + "/index.json");
    json index_values;
    index_file >> index_values;
    index_file.close();

    if (!index_values["actual_index"].get<bool>()) {
        std::cout << "Error : index is not initialized." << std::endl;
        return {};
    }

    std::vector<std::string> groups;
    for (auto& group : index_values.items()) {
        if (group.key() == "actual_index") {
            continue;
        }
        groups.push_back(group.key());
    }

    return groups;
}


void hjs_delete_group(std::string group_name){
    std::ifstream index_file(hjs_storage_directory() + "/index.json");
    json index_values;
    index_file >> index_values;
    index_file.close();

    if (!index_values["actual_index"].get<bool>()) {
        std::cout << "Error: index is not initialized." << std::endl;
        return;
    }

    if (index_values.find(group_name) == index_values.end()) {
        std::cout << "Error: group does not exist." << std::endl;
        return;
    }

    index_values.erase(group_name);

    std::ofstream index_file_write(hjs_storage_directory() + "/index.json");
    index_file_write << index_values.dump(4);
    index_file_write.close();

    std::cout << "Group \"" << group_name << "\" deleted successfully." << std::endl;
}

void hjs_create_element(std::string group_name, std::string element_name, json element_value, std::string element_type){
    std::ifstream index_file(hjs_storage_directory() + "/index.json");
    json index_values;
    index_file >> index_values;
    index_file.close();

    if (!index_values["actual_index"].get<bool>()) {
        std::cout << "Error : index is not initialized." << std::endl;
        return;
    }

    if (index_values.find(group_name) == index_values.end()) {
        std::cout << "Error : group does not exist." << std::endl;
        return;
    }
    // Checking if element already exist
    if (index_values[group_name].find(element_name) != index_values[group_name].end()) {
        std::cout << "Error : element already exists." << std::endl;
        return;
    }

    json group = index_values[group_name];
    json element;
    element["type"] = element_type;
    if (element_type == "string")
        element["value"] = element_value.get<std::string>();
    else if (element_type == "int")
        element["value"] = element_value.get<int>();
    else if (element_type == "float")
        element["value"] = element_value.get<float>();
    else if (element_type == "bool")
        element["value"] = element_value.get<bool>();
    else if (element_type == "json")
        element["value"] = element_value;

    group[element_name].push_back(element);

    index_values[group_name] = group;

    std::ofstream index_file_write(hjs_storage_directory() + "/index.json");
    index_file_write << index_values.dump(4);
    index_file_write.close();

    std::cout << "Element \"" << element_name << "\" created successfully in group \"" << group_name << "\"." << std::endl;
}

std::string hjs_get_string_element(std::string group_name, std::string element_name){
    std::ifstream index_file(hjs_storage_directory() + "/index.json");
    json index_values;
    index_file >> index_values;
    index_file.close();

    if (!index_values["actual_index"].get<bool>()) {
        std::cout << "Error : index is not initialized." << std::endl;
        return "";
    }

    if (index_values.find(group_name) == index_values.end()) {
        std::cout << "Error : group does not exist." << std::endl;
        return "";
    }

    if (index_values[group_name].find(element_name) == index_values[group_name].end()) {
        std::cout << "Error : element does not exist." << std::endl;
        return "";
    }

    if (index_values[group_name][element_name][0]["type"] != "string") {
        std::cout << "Error : element is not a string." << std::endl;
        return "";
    }

    return index_values[group_name][element_name][0]["value"].get<std::string>();
}

int hjs_get_int_element(std::string group_name, std::string element_name){
    std::ifstream index_file(hjs_storage_directory() + "/index.json");
    json index_values;
    index_file >> index_values;
    index_file.close();

    if (!index_values["actual_index"].get<bool>()) {
        std::cout << "Error : index is not initialized." << std::endl;
        return 0;
    }

    if (index_values.find(group_name) == index_values.end()) {
        std::cout << "Error : group does not exist." << std::endl;
        return 0;
    }

    if (index_values[group_name].find(element_name) == index_values[group_name].end()) {
        std::cout << "Error : element does not exist." << std::endl;
        return 0;
    }

    if (index_values[group_name][element_name][0]["type"] != "int") {
        std::cout << "Error : element is not an int." << std::endl;
        return 0;
    }

    return index_values[group_name][element_name][0]["value"].get<int>();
}

float hjs_get_float_element(std::string group_name, std::string element_name){
    std::ifstream index_file(hjs_storage_directory() + "/index.json");
    json index_values;
    index_file >> index_values;
    index_file.close();

    if (!index_values["actual_index"].get<bool>()) {
        std::cout << "Error : index is not initialized." << std::endl;
        return 0;
    }

    if (index_values.find(group_name) == index_values.end()) {
        std::cout << "Error : group does not exist." << std::endl;
        return 0;
    }

    if (index_values[group_name].find(element_name) == index_values[group_name].end()) {
        std::cout << "Error : element does not exist." << std::endl;
        return 0;
    }

    if (index_values[group_name][element_name][0]["type"] != "float") {
        std::cout << "Error : element is not a float." << std::endl;
        return 0;
    }

    return index_values[group_name][element_name][0]["value"].get<float>();
}

double hjs_get_double_element(std::string group_name, std::string element_name){
    std::ifstream index_file(hjs_storage_directory() + "/index.json");
    json index_values;
    index_file >> index_values;
    index_file.close();

    if (!index_values["actual_index"].get<bool>()) {
        std::cout << "Error : index is not initialized." << std::endl;
        return 0;
    }

    if (index_values.find(group_name) == index_values.end()) {
        std::cout << "Error : group does not exist." << std::endl;
        return 0;
    }

    if (index_values[group_name].find(element_name) == index_values[group_name].end()) {
        std::cout << "Error : element does not exist." << std::endl;
        return 0;
    }

    if (index_values[group_name][element_name][0]["type"] != "double") {
        std::cout << "Error : element is not a double." << std::endl;
        return 0;
    }

    return index_values[group_name][element_name][0]["value"].get<double>();
}

bool hjs_get_bool_element(std::string group_name, std::string element_name){
    std::ifstream index_file(hjs_storage_directory() + "/index.json");
    json index_values;
    index_file >> index_values;
    index_file.close();

    if (!index_values["actual_index"].get<bool>()) {
        std::cout << "Error : index is not initialized." << std::endl;
        return false;
    }

    if (index_values.find(group_name) == index_values.end()) {
        std::cout << "Error : group does not exist." << std::endl;
        return false;
    }

    if (index_values[group_name].find(element_name) == index_values[group_name].end()) {
        std::cout << "Error : element does not exist." << std::endl;
        return false;
    }

    if (index_values[group_name][element_name][0]["type"] != "bool") {
        std::cout << "Error : element is not a bool." << std::endl;
        return false;
    }

    return index_values[group_name][element_name][0]["value"].get<bool>();
}


std::string hjs_get_element_type(std::string group_name, std::string element_name){
    std::ifstream index_file(hjs_storage_directory() + "/index.json");
    json index_values;
    index_file >> index_values;
    index_file.close();

    if (!index_values["actual_index"].get<bool>()) {
        std::cout << "Error : index is not initialized." << std::endl;
        return "";
    }

    if (index_values.find(group_name) == index_values.end()) {
        std::cout << "Error : group does not exist." << std::endl;
        return "";
    }

    if (index_values[group_name].find(element_name) == index_values[group_name].end()) {
        std::cout << "Error : element does not exist." << std::endl;
        return "";
    }

    return index_values[group_name][element_name][0]["type"].get<std::string>();
}

#endif // HJS_HJS_H