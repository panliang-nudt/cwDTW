#ifndef OPTS_H__
#define OPTS_H__

#include <iostream>
#include <sstream>
#include <cassert>
extern "C" {
#include <getopt.h>
}
#include "util/exception.h"

struct options {
    char input[65532];
    char output[65532];
    int scale=1;
    int kmer=1;
    int zsco=0;
    int rna=0;
    int name=0;
};

inline int GetOpts(int argc, char **argv, options* opts_){

    static struct option longopts[] = {
        { "help",            no_argument,            NULL,              'h' },
        { "output",          required_argument,      NULL,              'o' },
        { "input",    	     required_argument,      NULL,              'i' },
	{ "scale",           required_argument,      NULL,              's' },
	{ "kmer",            required_argument,      NULL,              'k' },
	{ "zsco",            required_argument,      NULL,              'z' },
	{ "rna",             required_argument,      NULL,              'R' },
	{ "name",            required_argument,      NULL,              'N' },
        { NULL,              0,                      NULL,               0  }
    };
	
    if((argc != 5 && argc != 7 && argc != 9 && argc != 11 && argc != 13 && argc != 15 ) && argc >= 3 || (argc == 2 && argv[1][0] != '-' && argv[1][1] != 'h') || argc == 1){
            EX_TRACE("[-i GENOME INPUT][-o SIGNAL OUTPUT]([-s SCALE=1])([-k kmer=1])([-z zsco=0])([-R RNA=0])([-N name=0])\n");
            return -1;
    }
    
    int ch;
    while((ch = getopt_long(argc, argv, "hi:o:s:k:z:R:N:", longopts, NULL))!= -1){
        switch (ch) {

        case '?':
        {
            EX_TRACE("Invalid option '%s'.", argv[optind-1]);
            return -1;
        }

        case ':':
        {
            EX_TRACE("Missing option argument for '%s'.", argv[optind-1]);
            return -1;
        }

        case 'h':
        {
            EX_TRACE("[-i GENOME INPUT][-o SIGNAL OUTPUT]([-s SCALE=1])([-k KMER=1])([-z zsco=0])([-R RNA=0])([-N name=0])\n");
            EX_TRACE("[note]: to use 5mer pore model, set -k 0; to use 6mer pore model, set -k 1\n");
            EX_TRACE("        if zsco is set to 0, then Z-normalize pore model. \n");
            EX_TRACE("        if RNA is set to 0, use DNA pore mode; 1 for 200mv RNA, -1 for 180mv RNA \n");
            EX_TRACE("        if name is set to 1, then output Kmer name in the output file. \n");
            return -1;
        }

        case 'i':
        {
            std::istringstream iss(optarg);
            iss >> opts_->input;
            if (iss.fail()){
                EX_TRACE("Invalid argument '%s'.", optarg);
                return -1;
            }
        }
        break;
        
        case 'o':
        {
            std::istringstream iss(optarg);
            iss >> opts_->output;
            if (iss.fail()){
                EX_TRACE("Invalid argument '%s'.", optarg);
                return -1;
            }
        }
        break;

        case 's':
        {
            std::istringstream iss(optarg);
            iss >> opts_->scale;
            if (iss.fail()){
                EX_TRACE("Invalid argument '%s'.", optarg);
                return -1;
            }
        }
        break;

        case 'k':
        {
            std::istringstream iss(optarg);
            iss >> opts_->kmer;
            if (iss.fail()){
                EX_TRACE("Invalid argument '%s'.", optarg);
                return -1;
            }
        }
        break;

        case 'z':
        {
            std::istringstream iss(optarg);
            iss >> opts_->zsco;
            if (iss.fail()){
                EX_TRACE("Invalid argument '%s'.", optarg);
                return -1;
            }
        }
        break;

        case 'R':
        {
            std::istringstream iss(optarg);
            iss >> opts_->rna;
            if (iss.fail()){
                EX_TRACE("Invalid argument '%s'.", optarg);
                return -1;
            }
        }
        break;

        case 'N':
        {
            std::istringstream iss(optarg);
            iss >> opts_->name;
            if (iss.fail()){
                EX_TRACE("Invalid argument '%s'.", optarg);
                return -1;
            }
        }
        break;

        case 0: 
            break;

        default:
            assert(false);
        }
    }
    return 1;
}

#endif
