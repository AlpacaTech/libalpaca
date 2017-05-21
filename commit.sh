cd ~/VEX-709S-2018/miniRerun
pros make
cd ~/VEX-709S-2018/cpls
pros make
cd ~/VEX-709S-2018/docs
./document.sh
cd ..
git add *
git commit -m "$@"
git push
cd ~/VEX-709S-2018/docs
./document.sh
