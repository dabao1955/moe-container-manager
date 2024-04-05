#include "main.hpp"

// New feature from c++17,from List directory name
namespace fs = std::filesystem;
using namespace std;

// A simple usage
inline void usage(int exit_value = 0){
    cout << "Usage: interface [OPTION]... [FILE]...\n"
         << "List information about the FILEs (the current directory by default).\n\n"
         << "-c               create new container.\n"
         << "-h               show the program usage.\n"
         << "-l               list the installed container.\n"
         << "-r               remove installed container.\n"
         << "-v               show the program version.\n\n"
         << "N: this is a unstable app.\n";
    return;
}

inline void readc(int exit_value = 1){
    // If file not found, create it
    ofstream nif("/usr/share/moe-container/container-list.txt");
    nif.open("/usr/share/moe-container/container-list.txt", ios::app);
    if (!nif) // If file can not create,exit 1
    {
        cout << "can not create file." << endl;
        std::exit(exit_value);
    }
    else
    {
        // Set search directory
        std::string path = "</usr/share/moe-cintainer-manager/containers/>";

        // List of directory and write directoey name to txt
        for (const auto & entry : fs::directory_iterator(path)) {
            nif << entry.path().filename() << '\n';
        }
        nif.close();
        return;
    }

    // Read and cat txt to output the screen
    ifstream fin;
    fin.open("/usr/share/moe-container/container-list.txt",ios::in);
    if(!fin.is_open())
    {
        std::cerr<<"cannot open the file\n";
        std::exit(exit_value);
    }

    cout << "Installed container list:\n";
    char buf[1024]={0};
    while (fin >> buf)
    {
        cout << buf << endl;
    }
    fin.close(); // Add this line to close the file.
}

int main(int argc, char *argv[]) {
    svlog::basic_logfile();
    if (argc < 2)  {
        cout << "Error: No inputs.\n"
        << "Please use 'interface -h' to learn how to use.\n";
        return -1;
    } else if (argc > 4){
        cout << "Error: Too many inputs.\n";
        return -2;
    }

   // Main options
    for(int i = 1;i < argc; ++i){
        char *pchar = argv[i];
        switch(pchar[0]){
            case '-':{
                switch(pchar[1]){
                    case 'v':
                        cout <<proj::prog_name<<" version "<<proj::prog_version<<endl
                             << "Copyright (C) 2024 dabao1955\n"
                             << "License: Apache-2.0\n";
                        return 0;
                    case 'h':
                        usage();
                        return 0;
                    case 'c':
                        cout << "create a new container\n";
                        system("/usr/share/moe-container/register.sh");
                        return 0;
                    case 'l':
                        readc();
                        return 0;
                    default:
                        // proj::prog_name is in main.hpp.
                        cerr<<proj::prog_name<<":error:unrecognition option -:"<<pchar<<endl;
                        usage();
                        return -1;
                    }
                break;
            }
        }
    }
}
