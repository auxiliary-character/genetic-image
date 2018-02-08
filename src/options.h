#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>

struct Options{
    unsigned int threads;
    std::string in_file;
};

Options get_options(int argc, char** argv);

#endif
