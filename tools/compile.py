#!/usr/bin/python3
import os
import subprocess

def main():
    projectss = os.listdir(".")
    projects = []
    for i in range(len(projectss)):
        if "." not in projectss[i]:
            projects.append(projectss[i])
    projectss = projects
    projects = []
    for j in range(len(projectss)):
        if os.path.isfile(projectss[j] + "/project.pros"):
            projects.append(projectss[j])
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
