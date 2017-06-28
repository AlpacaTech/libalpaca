#!/bin/bash
cd $HOME/VEX-709S-2018/
make -j4
git add -u
cd docs/
./document.sh
./pdfMaker.sh
cd ..
git add -u
git rm include /*.swp -f
git rm src/*.swp -f
git rm *.swp -rf
git commit
git push
cd ~/VEX-709S-2018/iuyte.github.io/
./document.sh
git add -u
