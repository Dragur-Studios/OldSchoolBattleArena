import platform
import subprocess
import os

def get_os():
    system = platform.system()
    if system == "Windows":
        return "Windows"
    elif system == "Linux":
        return "Linux"
    elif system == "Darwin":
        return "MacOS"
    else:
        return "Unknown"

def run_premake():
    current_os = get_os()
    if current_os == "Windows":
        premake_path = os.path.join( "Windows", "build.bat")
    elif current_os == "Linux":
        premake_path = os.path.join("Scripts", "Linux", "premake5")
    else:
        print("Premake not supported on this OS.")
        return

    error = subprocess.run(premake_path)
    if error != 0:
        print(f"error occured: ${error}")

if __name__ == "__main__":
    run_premake()
