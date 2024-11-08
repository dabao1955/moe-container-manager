#include <iostream>
#include <memory>
#include <array>

int main() {
    std::array<char, 128> buffer;
    std::string result;

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("sudo bash test-root.sh", "r"), pclose);
    if (!pipe) {
        std::cerr << "Failed to run script." << std::endl;
        return 1;
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    std::cout << result;
    return 0;
}

