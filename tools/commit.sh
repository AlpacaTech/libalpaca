#!/bin/bash
cd /home/ethan/VEX-709S-2018/
pros make
git add * -f
cd docs/
./document.sh
cd ../tools/
doxygen
./pdfMaker.sh
cd ..
git add -u
git rm include/*.swp -f
git rm src/*.swp -f
git rm *.swp -f
git commit
git push
cd ~/VEX-709S-2018/docs
./document.sh
git add docs/*
