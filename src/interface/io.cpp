#include "include.hpp"
#include "void.hpp"
#include <dirent.h>
#include <cstring>

namespace io {
    void createdir(const char* filePath) {
        // check folder exits.
        if (!std::filesystem::exists(filePath)) {
            std::cout << "Folder at " << filePath << " does not exist. Creating it...\n";
            if (std::filesystem::create_directory(filePath)) {
                std::cout << "Folder created successfully.\n";
            } else {
                std::cerr << "Error creating folder.\n";
                return;
            }
        }
    }

    void removedir(const char* filePath) {
        // using std::filesystem::remove to remove target folder
        if (std::filesystem::remove(filePath) == 0) {
            std::cout << "File at " << filePath << " has been forcefully removed.\n";
        } else {
            std::cerr << "Error removing file at " << filePath << ".\n";
        }
    }

    void listfile(const char* filePath) {
        for (const auto & entry : std::filesystem::directory_iterator(filePath))
            std::cout << entry.path().filename() << std::endl;
    }
    void traversefile(const char* filePath) {
        DIR* dir = opendir(filePath);
        if (!dir) {
            std::cerr << "Error opening directory: " << filePath << "\n";
            return;
        }

        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type == DT_DIR) {
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                    continue;

                std::cout << entry->d_name << "\t<filePath>\n";

                char dirNew[200];
                strcpy(dirNew, filePath);
                strcat(dirNew, "/");
                strcat(dirNew, entry->d_name);

                listfile(dirNew);
            } else {
                std::cout << entry->d_name << "\t" << entry->d_reclen << " bytes.\n";
            }
        }

        closedir(dir);
    }
}
