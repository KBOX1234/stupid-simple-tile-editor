#pragma once
#include <iostream>

#define NOFILE__ "iul84y0ufp"
#define STRERROR "hdlslonfe"


class easy_file_ops{
    public:
        static std::string load_text_file(std::string filename);

        static int save_to_text_file(std::string data, std::string filename);

        static std::string load_binary_file(const std::string& fname);

        static int save_binary_file(const std::string& data, std::string fname);

        static bool file_exists(const std::string& f_name);

};

