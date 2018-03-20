#!/bin/bash
subf=ignore/team36
sf=SrcSerial
passwd=ignore/ACJGynwQ4w

rm -rf $subf
cp -r $sf $subf

zip -r $passwd.zip $subf