import os
import sys

def install_missing_dependencies():
    dependencies = ['libseccomp', 'p7zip', 'unzip', 'zip', 'git', 'go', 'wget', 'curl', 'nano', 'proot', 'axel', 'pv', 'gawk', 'gettext', 'git', 'build-devel', 'make', 'libcap', "libspdlog", 'go', 'zip', 'pv', 'cmake']
    missing_dependencies = []
    for dependency in dependencies:
        if os.system(f"pacman -Qs {dependency} > /dev/null") != 0:
            missing_dependencies.append(dependency)
    if len(missing_dependencies) > 0:
        os.system(f"sudo pacman --noconfirm -S {' '.join(missing_dependencies)}")
        print(f"Installed missing dependencies: {missing_dependencies}")
    else:
        print("All dependencies are already installed.")

def main():
    if os.system("uname -a | grep arch > /dev/null") != 0:
        print("This script is only intended to run on Arch Linux.")
        return
    install_missing_dependencies()
    os.system("makepkg -s --skipinteg")

if __name__ == "__main__":
    main()

