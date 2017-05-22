#!/usr/bin/python3
import os
import subprocess
import sys


def main():
    args = sys.argv[1:]
    msg = ""
    for arg in args:
        msg += arg + " "
    projects = ""
    with open("projects.txt", mode="r") as file:
        projects = file.read().split("\n")
    projects.pop(-1)
    print("PROJECTS TO COMPILE:")
    for project in projects:
        print(project)
    print("")
    for project in projects:
        print("Compiling " + project + ":")
        subprocess.run("./compile.sh " + project, shell=True)
        print("")

if __name__ == "__main__":
    main()
