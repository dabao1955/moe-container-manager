import subprocess

def check_script(script: str) -> str:
    """
    Check the shell script using shellcheck and shfmt.
    """
    # Check using shfmt
    shfmt = subprocess.run(["shfmt", "-d", src/rootfstool/rootfstool src/container/container], capture_output=True)
    if shfmt.returncode != 0:
        return "Step 1 Failed."

    # Check using shellcheck
    shellcheck = subprocess.run(["shellcheck", src/rootfstool/rootfstool src/container/container], capture_output=True)
    if shellcheck.returncode != 0:
        return "Step 2 Failed."

    return "All done."
