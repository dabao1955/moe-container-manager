#include "include.hpp"
#include "void.hpp"
#include <dirent.h>
#include <cstring>
#include "log.hpp"

namespace io {
    void createdir(const char* filePath) {
        // check folder exits.
        if (!std::filesystem::exists(filePath)) {
            std::cout << "Folder at " << filePath << " does not exist. Creating it...\n";
            XLOG_INFO(filePath," does not exist");
            if (std::filesystem::create_directory(filePath)) {
                std::cout << "Folder created successfully.\n";
                XLOG_INFO(filePath,"created");
            } else {
                std::cerr << "Error creating folder.\n";
                XLOG_ERROR(filePath,"create failed");
                return;
            }
        }
    }

    void removedir(const char* filePath) {
        // using std::filesystem::remove to remove target folder
        if (std::filesystem::remove(filePath) == 0) {
            std::cout << "File at " << filePath << " has been forcefully removed.\n";
            XLOG_INFO(filePath,"removed");
        } else {
            std::cerr << "Error removing file at " << filePath << ".\n";
            XLOG_ERROR(filePath,"remove failed");
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
            XLOG_INFO(filePath,"open failed");
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

    void runsh(const std::string& filePath, const std::string& args = "") {
        // check filePath string
        if (filePath.find(' ') != std::string::npos) {
            std::cerr << "Error: filePath should not contain spaces or additional arguments." << std::endl;
            XLOG_ERROR(filePath, "should not contain spaces or additional arguments.");
            exit(-1);
        }

        FILE *fp = nullptr;
        char *buff = nullptr;

        buff = (char*)malloc(20);
        if (buff == nullptr) {
            perror("malloc:");
            XLOG_ERROR(filePath, "execute failed by malloc");
            exit(-1);
        }
        memset(buff, 0, 20);

        fp = popen(filePath.c_str(), args.c_str());
        if (fp == nullptr) {
            perror("popen error:");
            XLOG_ERROR(filePath, "execute failed by popen error");
            free(buff);
            exit(-1);
        }

        if (fgets(buff, 20, fp) != nullptr) {
            std::cout << "Output: " << buff << std::endl;
        } else {
            perror("fgets error:");
            XLOG_ERROR(filePath, "execute failed by fgets error");
        }

        pclose(fp);
        free(buff);
    }

}
