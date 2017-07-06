import sys
import jsonpickle
from commit import Commit, printCommit, saveList

message = \
    """
"""

year = "2018"

style = \
    """+++
date = "2017-06-18T16:20:34-04:00"
description = "A log off all that was programmed"
title = "Programming Engineering Notebook"
+++

<head>
"""

with open("style.css", mode="r") as stylefyle:
    style += stylefyle.read() + "</head>\n"

script = ""
with open("main.js", mode="r") as scriptfile:
    script = scriptfile.read()

commitTemp =\
    """
<div class='commit' id='{1}'>
<p><b style='cursor: pointer;' onclick='window.open(\"https://github.com/iuyte/VEX-709S-{2}/commit/{3}\")'>Commit:</b> <a class='link' href='https://iuyte.github.io/VEX-709S-{2}#{3}'>{3}</a></p>
<p><b>Date:</b> {4}</p>
<p><b>Author:</b> {5}</p>
<p><b>Description:</b><br>{6}</p>
<b>Files added:</b>
<ul>

"""


def indexInStr(index, string):
    out = 0
    for i in range(len(string)):
        if string[i] == index:
            break
        out += 1
    return out


def styleContent(commit):
    out = "<div class='commit' id='" + commit.commitkey + "'>"
    out += "<p><b><a class='link' href='https://github.com/iuyte/VEX-709S-" + year + "/commit/" + commit.commitkey + \
        "/' target='_blank'>Commit:</a></b> <a class='link' href='https://iuyte.github.io/notebook/programming/#" + \
        commit.commitkey + "'>" + commit.commitkey + "</a></p>"
    out += "<p><b>Date:</b> " + commit.date + "</p>\n"
    out += "<p><b>Author:</b> " + commit.author + "</p>\n"
    out += "<p><b>Description:</b><br>" + commit.description + "</p>\n"
    if len(commit.filesAdded) > 0:
        out += "<b>Files added:</b>\n<ul>\n"
        for i in range(len(commit.filesAdded)):
            out += "<li><a class='link' href='https://github.com/iuyte/VEX-709S-" + year + "/tree/" + \
                commit.commitkey + "/" + \
                commit.filesAdded[i] + "'>" + \
                commit.filesAdded[i] + "</a></li>\n"
        out += "</ul>"
    if len(commit.filesModified) > 0:
        out += "<b>Files modified:</b>\n<ul>\n"
        for i in range(len(commit.filesModified)):
            out += "<li><a class='link' href='https://github.com/iuyte/VEX-709S-" + year + "/tree/" + \
                commit.commitkey + "/" + \
                commit.filesModified[i] + "'>" + \
                commit.filesModified[i] + "</a></li>\n"
        out += "</ul>"
    if len(commit.filesDeleted) > 0:
        out += "<b>Files deleted:</b>\n<ul>\n"
        for i in range(len(commit.filesDeleted)):
            out += "<li>" + commit.filesDeleted[i] + "</li>\n"
        out += "</ul>"
    out += "<br></div>\n"
    return out


def removeSpaces(content):
    content = content.split(" ")
    out = ""
    for i in range(len(content)):
        out += content[i]
    return out


def parseContent(content):
    if content == "":
        assert False, "File is empty or does not exist"
    out = style
    count = 0
    commits = content.split("commit ")
    commit = 0
    lcom = ""
    lcommits = []
    for commit in range(1, len(commits)):
        aline = 0
        lines = commits[commit].split("\n")
        try:
            lines[aline]
        except:
            continue
        line = ""
        lline = ""
        date = ""
        commitkey = ""
        author = ""
        description = ""
        filesModified = []
        filesAdded = []
        filesDeleted = []
        try:
            commitkey = lines[aline]
            aline += 1
            author = lines[aline].split("Author:")[1]
            aline += 1
            date = lines[aline].split("Date: ")[1]
            aline += 2
            description = lines[aline][4:]
            aline += 2
        except:
            continue
        filesModified = []
        filesAdded = []
        filesDeleted = []
        for aline in range(aline, len(lines)):
            curline = lines[aline][39:]
            if ". M" in lines[aline]:
                if "docs/index.html" not in curline and "docs/log.txt" not in curline and "docs/log.json" not in curline and "bin/" not in curline and "__pycache__" not in curline and "tools/doxygen" not in curline and "tools/PDFs" not in curline and "tools/LATEX" not in curline and not curline.startswith("doxygen") and not curline.startswith("709S"):
                    filesModified.append(curline)
            elif ". A" in lines[aline] and ".swp" not in curline and "bin/" not in curline and "__pycache__" not in curline and "tools/doxygen" not in curline and "tools/PDFs" not in curline and "tools/LATEX" not in curline and not curline.startswith("doxygen") and not curline.startswith("709S"):
                filesAdded.append(curline)
            elif ". D" in lines[aline] and ".swp" not in curline and "bin/" not in curline and "__pycache__" not in curline and "tools/doxygen" not in curline and "tools/PDFs" not in curline and "tools/LATEX" not in curline and not curline.startswith("doxygen") and not curline.startswith("709S"):
                filesDeleted.append(curline)
        tcommit = Commit(date, commitkey, author, description, filesModified,
                         filesAdded, filesDeleted)
        lcommits.append(tcommit)
        out += styleContent(tcommit) + "<div class='spacer'></div>"
    saveList(lcommits)
    out += script + "</body>\n</html>\n"
    lcom = commitkey
    return out
