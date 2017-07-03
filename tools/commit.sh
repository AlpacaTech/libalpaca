#!/bin/bash
cd $VEX
make clean
make -j2
git add -u
cd docs/
./document.sh
cd ..
tools/pdfMaker.sh
cp docs/index.html 709S/content/notebook/programming/_index.html -f
tools/htmlCopy.sh
cd 709S
./deploy.sh
cd ..
git add -u
git rm include/*.swp src/*.swp -f
git rm *.swp -rf
if [ $# -eq 1 ]
  then git commit -m "$1"
else
  git commit
fi
git push
cd docs/
./document.sh
git add -u
cd ..
