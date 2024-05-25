import subprocess, os

"""
tests are performed by executing each test file (named after the error that should be caused (i.e. "304.mik"))
the output is then compared to the error being output, if it's a match, the test is considered a success.
"""

if __name__ == "__main__":
    files_list = []
    for root, dirs, files in os.walk(os.getcwd()):
        for file in files:
            files_list.append(os.path.join(root, file))

    files_list = files_list[1:] # removes the python file
    for file in files_list:

        if (b"\x1b[31m\n\r[ERROR " + bytes(file.split("/")[len(file.split("/"))-1][:-4], 'utf-8')) in subprocess.run(['../mic', file], stdout=subprocess.PIPE).stdout:
                   print("Test: " + file.split("/")[len(file.split("/"))-1][:-4] + " -> Succeeded")
        else:
                   print("Test: " + file.split("/")[len(file.split("/"))-1][:-4] + " -> Failed")

