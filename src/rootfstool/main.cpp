#include <iostream>
#include <string>
#include <map>
#include "httplib.h"
#include <vector>

const std::string ROOTFSTOOL_VERSION = "1.5-hotfix";
std::string LXC_MIRROR, CPU_ARCH, DISTRO, VERSION;
std::map<std::string, std::string> MIRRORS = {
    {"main", "http://images.linuxcontainers.org"},
    {"bfsu", "https://mirrors.bfsu.edu.cn/lxc-images"},
    {"tuna", "https://mirrors.tuna.tsinghua.edu.cn/lxc-images"},
    {"nju", "https://mirror.nju.edu.cn/lxc-images"},
    {"iscas", "https://mirror.iscas.ac.cn/lxc-images"}
};

void show_help() {
    std::cout << "Usage:\n"
              << "  rootfstool <command> [<args>]\n\n"
              << "Commands:\n"
              << "  version,v    Show version info\n"
              << "  help,h       Show help\n"
              << "  list,l       List all distros\n"
              << "  search,s     Search available versions of distro\n"
              << "  url,u        Get rootfs download link\n"
              << "  download,d   Download rootfs as rootfs.tar.xz\n\n"
              << "Args:\n"
              << "  --distro,-d  Specify os distro\n"
              << "  --arch,-a    Specify cpu architecture\n"
              << "  --version,-v Specify distro version\n"
              << "  --mirror,-m  Specify the mirror (e.g., main, bfsu, tuna, nju, iscas)\n";
}

void show_version() {
    std::cout << "rootfstool version " << ROOTFSTOOL_VERSION << " by Moe-hacker\n";
}

void select_mirror(const std::string &mirror) {
    if (MIRRORS.find(mirror) != MIRRORS.end()) {
        LXC_MIRROR = MIRRORS[mirror];
    } else {
        std::cerr << "Unknown mirror!\n";
        exit(1);
    }
}

std::string get_rootfs_url() {
    httplib::Client cli(LXC_MIRROR.c_str());
    std::string meta_path = "/meta/1.0/index-system";
    auto res = cli.Get(meta_path.c_str());
    if (res && res->status == 200) {
        std::string body = res->body;
        std::size_t pos = body.find(DISTRO + ";" + VERSION + ";" + CPU_ARCH);
        if (pos != std::string::npos) {
            std::size_t start = body.rfind("/", pos) + 1;
            std::string path = body.substr(start, body.find("\n", pos) - start);
            return LXC_MIRROR + path + "rootfs.tar.xz";
        }
    }
    return "";
}

void download_rootfs() {
    std::string url = get_rootfs_url();
    if (url.empty()) {
        std::cerr << "Rootfs URL not found.\n";
        return;
    }

    httplib::Client cli(LXC_MIRROR.c_str());
    std::string path = url.substr(url.find(LXC_MIRROR) + LXC_MIRROR.size());
    auto res = cli.Get(path.c_str());
    if (res && res->status == 200) {
        std::ofstream ofs("rootfs.tar.xz", std::ios::binary);
        ofs << res->body;
        ofs.close();
        std::cout << "Download complete.\n";
    } else {
        std::cerr << "Download failed.\n";
    }
}

void parse_arguments(int argc, char *argv[], std::string &command) {
    command = argv[1];
    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "--distro" || arg == "-d") && i + 1 < argc) {
            DISTRO = argv[++i];
        } else if ((arg == "--arch" || arg == "-a") && i + 1 < argc) {
            CPU_ARCH = argv[++i];
        } else if ((arg == "--version" || arg == "-v") && i + 1 < argc) {
            VERSION = argv[++i];
        } else if ((arg == "--mirror" || arg == "-m") && i + 1 < argc) {
            select_mirror(argv[++i]);
        } else {
            std::cerr << "Unknown argument: " << arg << "\n";
            show_help();
            exit(1);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        show_help();
        return 1;
    }

    std::string command;
    parse_arguments(argc, argv, command);

    if (command == "help" || command == "h") {
        show_help();
    } else if (command == "version" || command == "v") {
        show_version();
    } else if (command == "list" || command == "l") {
        // List available distros
        // This would involve fetching data and filtering by architecture (omitted for brevity)
        std::cout << "Listing available distros for " << CPU_ARCH << "...\n";
    } else if (command == "search" || command == "s") {
        // Search versions for specified distro
        // This would involve fetching data and filtering by distro (omitted for brevity)
        std::cout << "Searching versions for " << DISTRO << " on " << CPU_ARCH << "...\n";
    } else if (command == "url" || command == "u") {
        if (LXC_MIRROR.empty() || DISTRO.empty() || VERSION.empty() || CPU_ARCH.empty()) {
            std::cerr << "Please specify --mirror, --distro, --version, and --arch.\n";
            return 1;
        }
        std::string url = get_rootfs_url();
        if (!url.empty()) {
            std::cout << "Rootfs URL: " << url << std::endl;
        } else {
            std::cerr << "URL not found.\n";
        }
    } else if (command == "download" || command == "d") {
        if (LXC_MIRROR.empty() || DISTRO.empty() || VERSION.empty() || CPU_ARCH.empty()) {
            std::cerr << "Please specify --mirror, --distro, --version, and --arch.\n";
            return 1;
        }
        download_rootfs();
    } else {
        std::cerr << "Unknown command: " << command << "\n";
        show_help();
    }

    return 0;
}
