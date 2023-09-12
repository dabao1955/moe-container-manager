import os
import subprocess

def check_c_files(path):
    for root, dirs, files in os.walk(path):
        for file in files:
            if file.endswith(".c"):
                file_path = os.path.join(root, file)
                cmd = f"clang-format -style=file {file_path}"
                result = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                if result.returncode != 0:
                    print(f"check failed: {file_path}")
                    print(result.stderr.decode())
                    
check_c_files(".")
