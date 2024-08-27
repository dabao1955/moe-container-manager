#include "interface.hpp"
#include <void.hpp>

using namespace func;
using namespace projsignal;

void interface(int argc, char *argv[]) {
    register_signal();

    if (argc < 2)  {
        cout << "Error: No inputs.\n"
        << "Please use 'interface -h' to learn how to use.\n";
        exit(1);
    } else if (argc > 4){
        cout << "Error: Too many inputs.\n";
        exit(2);
    }

   // Main options
    for(int i = 1;i < argc; ++i){
        char *pchar = argv[i];
        switch(pchar[0]){
            case '-':{
                switch(pchar[1]){
                    case 'v':
                        version();
                        exit(0);
                    case 'h':
                        usage();
                        exit(0);
                    case 'c':
                        create();
                        exit(0);
                    case 'l':
                        readc();
                        exit(0);
                    case 'd':
                        remove();
                        exit(0);
                    case 'r':
                        reg();
                        exit(0);
                    case 's':
                        start();
                        exit(0);
                    case 'f':
                        cleanrootfs();
                        exit(0);
                    default:
                        cerr<<proj::prog_name<<":Error: Unrecognition option: "<<pchar<<endl;
                        exit(254);
                    }
                break;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    interface(argc, argv);
    return 0;
}
