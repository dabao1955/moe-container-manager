#include "main.hpp"
using namespace std;

inline void usage(int exit_value = 0){
    cout << "Usage: interface [OPTION]... [FILE]...\n";
    cout << "List information about the FILEs (the current directory by default).\n\n";
    cout << "-c               create new container.\n";
    cout << "-h               show the program usage.\n";
    cout << "-l               list the installed container.\n";
    cout << "-r               remove installed container.\n";
    cout << "-v               show the program version.\n\n";
    cout << "N: this is a unstable app.\n";
    return;
}

int main(int argc, char *argv[]) {
    if (argc < 2)  {
        cout << "Error: No inputs, use <interface -h> to learn how to use.\n";
        return -1;
    } else if (argc > 4){
        cout << "Error: Too many inputs.\n";
        return -2;
    }
        for(int i = 1;i < argc; ++i){
        char *pchar = argv[i];
        switch(pchar[0]){
            case '-':{
                switch(pchar[1]){
                    case 'v':
                        cout <<proj::prog_name<<" version "<<proj::prog_version<<endl;
                        cout << "Copyright (C) 2024 dabao1955\n";
                        cout << "License: Apache-2.0\n";
                        return 0;
                    case 'h':
                        usage();
                        return 0;
                    case 'c':
                        cout << "create a new container\n";
                        system("/usr/share/moe-container/create.sh");
                        return 0;
                    case 'l':
                        cout << "Installed container list:\n";
                        return 0;
                    default:
                        cerr<<proj::prog_name<<":error:unrecognition option -:"<<pchar<<endl;
                        usage();
                        return -1;
                    }
                break;
            }
        }
    }
}

