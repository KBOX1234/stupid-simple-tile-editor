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

std::string easy_file_ops::compress_gzip(const std::string &data){
    z_stream zs{};
    deflateInit2(&zs, Z_BEST_COMPRESSION, Z_DEFLATED, 15 + 16, 8, Z_DEFAULT_STRATEGY); // +16 → gzip

    zs.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(data.data()));
    zs.avail_in = data.size();

    std::vector<char> outbuffer(32768);
    std::string outstring;

    int ret;
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer.data());
        zs.avail_out = outbuffer.size();
        ret = deflate(&zs, Z_FINISH);
        outstring.append(outbuffer.data(), outbuffer.size() - zs.avail_out);
    } while (ret == Z_OK);

    deflateEnd(&zs);
    return outstring;
}

std::string easy_file_ops::decompress_gzip(const std::string &data) {
    z_stream zs{};
    zs.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(data.data()));
    zs.avail_in = data.size();

    if (inflateInit2(&zs, 15 + 16) != Z_OK) {
        throw std::runtime_error("inflateInit2() failed while decompressing gzip data");
    }

    std::vector<char> outbuffer(32768);
    std::string outstring;

    int ret;
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer.data());
        zs.avail_out = outbuffer.size();

        ret = inflate(&zs, 0);

        if (ret != Z_OK && ret != Z_STREAM_END) {
            inflateEnd(&zs);
            throw std::runtime_error("inflate() failed while decompressing gzip data");
        }

        outstring.append(outbuffer.data(), outbuffer.size() - zs.avail_out);
    } while (ret != Z_STREAM_END);

    inflateEnd(&zs);
    return outstring;
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
