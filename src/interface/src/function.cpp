#include "interface.hpp"
#include <void.hpp>

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

    void readc() {
        listfile("/usr/share/moe-cintainer-manager/containers/");
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
        runsh("/usr/share/moe-container/remove.sh");
        exit(0);
    }

    void create(){
        cout << "Create a new container\n";
        // check root account
        if (geteuid() != 0) {
            runsh("/usr/share/moe-container/create.sh");
        }
        else {
            runsh("/usr/share/moe-container/create.sh", " -r");
        }
         exit(0);
    }

    void start(){
        runsh("/usr/share/moe-container/start.sh");
        exit(0);
    }

    void reg(){
        runsh("/usr/share/moe-container/register.sh");
        exit(0);
    }
    void cleanrootfs(){
        cout <<"Rootfs are downloaded to /usr/share/moe-container-manager/rootfs\n";
        cout <<"Please press any key to continue.\n";
        getchar();
        const char* rootfs = "/usr/share/moe-container-manager/rootfs";
        removedir(rootfs);
        createdir(rootfs);
        exit(0);
    }
}
