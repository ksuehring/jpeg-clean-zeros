#!/bin/bash

if [ -n "$1" ] ; then
  target_dir="$1"
else
  target_dir=$PWD
fi

echo 
echo "Warning: this script cleans all trailing zero bytes in JPEG image under the target folder"
echo "by OVERWRITING the source file."
echo 
echo "MAKE SURE, YOU HAVE A BACKUP OF YOUR DATA IN CASE ANYTHING GOES WRONG!"
echo 
echo "Target: \"$target_dir\""
echo 
read -p "Type 'confirm' to confirm cleaning: " confirm
if [ "$confirm" == "confirm" ]
then
  echo Cleaning...
  find "$target_dir" \( -iname \*.jpg -o -name \*.jpeg  \) -exec jpeg-zero-clean {} {} \;
else
  echo Aborting.
fi


