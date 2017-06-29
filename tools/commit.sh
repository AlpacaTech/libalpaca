#!/bin/bash
cd $VEX
make -j2
git add -u
cd docs/
./document.sh
cd ..
tools/pdfMaker.sh
cp docs/index.html 709S/content/Notebook/Programming.html -f
tools/htmlCopy.sh
cd 709S
./deploy.sh
cd ..
git add -u
git rm include /*.swp -f
git rm src/*.swp -f
git rm *.swp -rf
if [ $# -eq 1 ]
  then git commit -m "$1"
else
  git commit
fi
git push
cd ~/VEX-709S-2018/iuyte.github.io/
./document.sh
git add -u
