#include <iostream>
#include <memory>
#include <array>
#include <cstdio>

int main() {
    std::array<char, 128> buffer;
    std::string result;

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("bash test-root.sh", "r"), pclose);
    if (!pipe) {
        std::cerr << "Failed to run script." << std::endl;
        return 1;
    }

    int status = 0;
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    status = pclose(pipe.get());

    if (status != 0) {
        std::cerr << "Script failed with exit status: " << status << std::endl;
        return 1;
    }

    std::cout << result;
    return 0;
}

