cd $HOME/VEX-709S-2018/
for q in include/*.h include/*.hpp src/*.cpp
do
  echo "Copying $q..."
  text="+++
title='$q'
description='Code for $q'
type='page'
+++

"
  echo "$text" > 709S/content/source/"$q".md
  echo "\`\`\`Cpp" >> 709S/content/source/"$q".md
  cat "$q" >> 709S/content/source/"$q".md
  echo "\`\`\`" >> 709S/content/source/"$q".md
done
