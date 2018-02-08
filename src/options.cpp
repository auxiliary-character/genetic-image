#include "options.h"
#include <argp.h>
#include <sstream>
#include <iostream>

namespace{
    error_t parse_options(int key, char* arg, struct argp_state* state){
        Options& options = *reinterpret_cast<Options*>(state->input);
        std::stringstream stream;
        stream << arg;
        switch(key){
            case 't':
                stream >> options.threads;
                if(!(options.threads > 0)){
                    std::cout << "Invalid amount of threads." << std::endl;
                    argp_usage(state);
                }
                break;
            case ARGP_KEY_END:
                if(state->arg_num < 1){
                    std::cout << "Too few arguments." << std::endl;
                    argp_usage(state);
                }
                break;
            case ARGP_KEY_ARG:
                switch(state->arg_num){
                    case 0:
                        stream >> options.in_file;
                        break;
                    default:
                        std::cout << "Too many arguments." << std::endl;
                        argp_usage(state);
                }
                break;
            default:
                return ARGP_ERR_UNKNOWN;
        }
        return 0;
    }
}
const char* argp_program_version = "genetic-image 0.0.1";
const char* argp_program_bug_address = "auxchar@gmail.com";
const std::string args_doc = "INPUT";
const std::string doc = "Generates an image resembling another image using a genetic algorithm.";

Options get_options(int argc, char** argv){
    Options options;
    options.threads = 1;

    struct argp_option options_table[] = {
        {"threads", 't', "THREADS", 0,
            "Number of threads. If unset, the default is 1.", 0},
        {0, 0, 0, 0, 0, 0}

    };
    struct argp argp = {options_table, parse_options, args_doc.c_str(), doc.c_str(), 0, 0, 0};
    argp_parse(&argp, argc, argv, 0, 0, &options);
    return options;
}
