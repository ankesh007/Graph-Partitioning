#!/bin/bash
direc=ignore
subf=team36
sf=RandomThings
passwd=ACJGynwQ4w

rm $direc/$passwd.zip
rm -r $direc/$subf
cp -r $sf $direc/$subf
cd ignore/$subf
zip -r $passwd.zip *
# rm -r $subf
# zip -r $passwd.zip ../$sf/{*.{cpp,sh},Makefile}