#!/bin/bash
subf=team36
sf=SrcSerial

rm -rf $subf
cp -r $sf $subf

zip -r $subf.zip $subf