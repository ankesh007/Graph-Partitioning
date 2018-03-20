#!/bin/bash
direc=ignore
subf=team36
sf=SrcSerial
passwd=ACJGynwQ4w

rm $direc/$passwd.zip
cp -r $sf $direc/$subf
cd ignore/
zip -r $passwd.zip $subf
rm -r $subf
# zip -r $passwd.zip ../$sf/{*.{cpp,sh},Makefile}