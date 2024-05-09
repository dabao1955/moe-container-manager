#include "main.hpp"
#include "log.hpp"
#include "void.hpp"

using namespace proj;
// New feature from c++17,from List directory name
namespace fs = std::filesystem;

// A simple usage
namespace func {
    void usage(){
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

    void readc(){
        // If file not found, create it
        ofstream nif("/usr/share/moe-container/container-list.txt");
        nif.open("/usr/share/moe-container/container-list.txt", ios::app);
        if (!nif) { // If file can not create,exit 1
            cout << "can not create file." << endl;
            XLOG_ERROR("this is error log record: {}");
            exit(0);
        }
        else {
            // Set search directory
            string path = "</usr/share/moe-cintainer-manager/containers/>";

            // List of directory and write directoey name to txt
            for (const auto & entry : fs::directory_iterator(path)) {
                nif << entry.path().filename() << '\n';
                XLOG_WARN("this is warn log record, param: {}");
            }
            nif.close();
            return;
        }

        // Read and cat txt to output the screen
        ifstream fin;
        fin.open("/usr/share/moe-container/container-list.txt",ios::in);
        if(!fin.is_open()) {
            cerr<<"cannot open the file\n";
            exit(0);
        }

        cout << "Installed container list:\n";
        char buf[1024]={0};
        while (fin >> buf)
        {
            cout << buf << endl;
        }
        fin.close(); // Add this line to close the file.
    }

    void version(){
        cout <<prog_name<<" version "<<prog_version<<endl
        << "Build date: " << __DATE__ << " " << __TIME__ <<endl
        << "Copyright (C) 2024 dabao1955\n"
        << "License: Apache-2.0\n";
        exit(0);
    }

    void remove(){
        cout << "remove a installed container\n";
        system("/usr/share/moe-container/remove.sh");
        exit(0);
    }

    void create(){
        cout << "remove a installed container\n";
        // check root account
        if (geteuid() != 0) {
            system("/usr/share/moe-container/create.sh");
        }
        else {
            system("/usr/share/moe-container/create.sh -r");
        }
         exit(0);
    }

    void start(){
        system("/usr/share/moe-container/start.sh");
        exit(0);
    }

}
