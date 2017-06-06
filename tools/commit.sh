#!/bin/bash
cd /home/ethan/VEX-709S-2018/
pros make
git add * -f
cd docs/
./document.sh
cd ../
git add *
git commit -m "$@"
git push
cd ~/VEX-709S-2018/docs
./document.sh
