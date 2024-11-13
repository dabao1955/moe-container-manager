#include <iostream>
#include <memory>
#include <array>
#include <cstdio>
#include <cstdlib>

int main() {
    std::array<char, 128> buffer;

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("sudo bash test-root.sh", "r"), pclose);
    if (!pipe) {
        std::cerr << "Failed to run script." << std::endl;
        return 1;
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        std::cout << buffer.data();
        std::cout.flush();
    }

    int returnCode = pclose(pipe.release());
    if (!WIFEXITED(returnCode) || WEXITSTATUS(returnCode) != 0) {
        return 1;
    }

    return 0;
}

