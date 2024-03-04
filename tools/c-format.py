import os
import subprocess

def check_c_files():
    cmd = "find . -name \"*.c\" -o -name \"*.h\" | xargs clang-tidy --checks=-clang-analyzer-security.insecureAPI.strcpy,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling  -fix"
    result = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode != 0:
        print("check failed")
        print(result.stderr.decode())
check_c_files()
