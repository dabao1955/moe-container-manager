#include "main.hpp"
#include "log.hpp"
#include "void.hpp"

using namespace proj;
using namespace io;
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
        << "-d               remove installed container.\n"
        << "-r               register a new container.\n"
        << "-s               start a container.\n"
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
            XLOG_ERROR("Can not create file: {}");
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
            XLOG_ERROR("Can not list container: {}");
            exit(0);
        }

        cout << "Installed container list:\n";
        char buf[1024]={0};
        while (fin.getline(buf, sizeof(buf)))
        {
            cout << buf << endl;
        }
        fin.close(); // Add this line to close the file.
    }

    void version(){
        cout <<prog_name<<" version "<<prog_version<<endl;
        cout << "Build date: " << __DATE__ <<" "<< __TIME__ <<endl;
        cout <<"Compiler version: "<<__VERSION__<< endl;
        cout << "Copyright (C) 2024 dabao1955\n"
        << "License: Apache-2.0\n";
        exit(0);
    }

    void remove(){
        cout << "remove a installed container\n";
        system("/usr/share/moe-container/remove.sh");
        exit(0);
    }

    void create(){
        cout << "Create a new container\n";
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

    void reg(){
        system("/usr/share/moe-container/register.sh");
        exit(0);
    }
    void cleanrootfs(){
        cout <<"Rootfs are downloaded to /usr/share/moe-container-manager/rootfs\n";
        cout <<"Please press any key to continue.\n";
        getchar();
        const char* rootfs = "/usr/share/moe-container-manager/rootfs";
        removedir(rootfs);
        createdir(rootfs);
        XLOG_INFO("Removed downloaded rootfs: {}");
        exit(0);
    }
}
