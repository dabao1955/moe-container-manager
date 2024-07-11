#include "include.hpp"
#include "void.hpp"

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
}
