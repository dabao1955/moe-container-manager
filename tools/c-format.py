import os
import subprocess

def check_c_files():
    cmd = "find . -name \"*.c\" -o -name \"*.h\" | xargs clang-format -style=file"
    result = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode != 0:
        print("check failed")
        print(result.stderr.decode())
                    
check_c_files()
