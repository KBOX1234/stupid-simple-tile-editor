#include "../include/f_utils.hpp"
#include <cstring>
#include <json.hpp>
#include <fstream>
#include <filesystem>
#include <zlib.h>
#include <sstream>      // For std::stringstream
#include <string>
#include <iostream>


using json = nlohmann::json;

namespace fs = std::filesystem;



std::string easy_file_ops::load_text_file(std::string filename){
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Unable to open file.\n";
        return NOFILE__;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();

}

int easy_file_ops::save_to_text_file(std::string data, std::string filename){
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Unable to open file for writing: " + filename + "\n";
        return -1;
    }

    file << data;

    file.close();

    return 0;
}

bool easy_file_ops::file_exists(const std::string& f_name) {
    return std::filesystem::exists(f_name);
}

std::string easy_file_ops::load_binary_file(const std::string &filename) {

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string buffer(size, '\0');
    if (!file.read(&buffer[0], size)) {
        throw std::runtime_error("Failed to read file: " + filename);
    }

    return buffer;
}

int easy_file_ops::save_binary_file(const std::string &data, std::string fname) {
    std::ofstream file(fname, std::ios::binary);
    if (!file) {
        return 1;
    }

    file.write(data.data(), data.size());
    if (!file.good()) {
        return 2;
    }

    return 0;
}
