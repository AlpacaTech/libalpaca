import sys, jsonpickle
from commit import Commit, printCommit, saveList

style = """<link href="https://fonts.googleapis.com/css?family=Open+Sans" rel="stylesheet">
<style>
    .body {
        align: center;
        background-color: #bfbfdf;
        width: 100%;
        margin: 0px;
        font-family: 'Open Sans', sans-serif;
    }

    .link {
       color: black;
       text-decoration: none;
       word-wrap: break-word;
    }

    .link:visited {
       color: black;
       text-decoration: none;
       cursor: auto;
    }

    .link:hover {
       color: #0000EE;
       text-decoration: underline;
       cursor: pointer;
    }

    .commit {
        background-color: #efefef;
        width: 50%;
        align: center;
        align-self: center;
        align-content: center;
        align-items: center;
        border-color: #454585;
        border-style: groove inset;
        border-radius: 25px;
        padding: 20px;
        margin-left: 25%;
        margin-right: 25%;
        box-shadow: 10px 10px 5px #777777;
    }

    .em {
        cursor: pointer;
    }

    .spacer {
        height: 5%;
    }

    .bcon {
       width: 8%;
    }

    .browse {
       background-color: #454585;
       color: white;
       border: 2px solid #454585;
       border-radius: 4px;
       position: absolute;
       right: 25%;
       display: none;
    }

    .browse:hover {
       background-color: #bfbfdf;
       border-color: #9d9dbf;
       color: black;
    }

    h1 {
       font-size: 275%;
    }

    h2 {
       font-size: 170%;
    }

    .centered {
       text-align: center;
    }

</style>
"""
script="""
<script>
    window.onload = function() {
       if (window.location.href[0] == "f") {
           var elements = document.querySelectorAll('h1');
            for(var i=0; i<elements.length; i++){
                elements[i].style.font-size = "188%";
            }
            elements = document.querySelectorAll('h2');
            for(var ii=0; i<elements.length; i++){
                elements[i].style.font-size = "117%";
            }
       }
    }
</script>
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
    out += "<p><b style='cursor: pointer;' onclick='window.open(\"https://github.com/iuyte/VEX-709s/commit/" + commit.commitkey + "\")'>Commit:</b> <a class='link' href='https://iuyte.github.io/VEX-709s/2017/Planning/tools/git.html#" + commit.commitkey + "'>" + commit.commitkey + "</a></p>"
    out += "<p><b>Date:</b> " + commit.date + "</p>\n"
    out += "<p><b>Author:</b> " + commit.author + "</p>\n"
    out += "<p><b>Description:</b><br>" + commit.description + "</p>\n"
    if len(commit.filesAdded) > 0:
        out += "<b>Files added:</b>\n<ul>\n"
        for i in range(len(commit.filesAdded)):
            out += "<li><span class='link' onclick='window.open(\"https://github.com/iuyte/VEX-709s/tree/" + commit.commitkey + "/" + commit.filesAdded[i] + "\")'>" + commit.filesAdded[i] + "</span></li>\n"
        out += "</ul>"
    if len(commit.filesModified) > 0:
        out += "<b>Files modified:</b>\n<ul>\n"
        for i in range(len(commit.filesModified)):
            out += "<li><span class='link' onclick='window.open(\"https://github.com/iuyte/VEX-709s/tree/" + commit.commitkey + "/" + commit.filesModified[i] +"\")'>" + commit.filesModified[i] + "</span></li>\n"
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
    out = "<html>\n<head>\n" + style + "<title>Git Commit history</title>\n</head>\n<body style='background-color: #bfbfdf;' class='body'>"
    count = 0
    commits = content.split("commit ")
    out += "<div class='commit' id='top'>\n<h1 class='centered'>VEX Robotics Competition</h1>\n<h2 class='centered'>Team 709S Programming Log / Notebook<h2>\n</div>\n<br>\n"
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
            if ". M" in lines[aline]:
                filesModified.append(lines[aline][39:])
            elif ". A" in lines[aline]:
                filesAdded.append(lines[aline][39:])
            elif ". D" in lines[aline]:
                filesDeleted.append(lines[aline][39:])
        tcommit = Commit(date, commitkey, author, description, filesModified, filesAdded, filesDeleted)
        lcommits.append(tcommit)
        out += styleContent(tcommit) + "<div class='spacer'></div>"
    saveList(lcommits)
    out += script + "</body>\n</html>\n"
    lcom = commitkey
    return out
