#!/bin/bash

echo -ne '\E[H\E[J' # Clear
echo -ne '\E[5;10H'
echo -en '\E(0'

echo -en 'l'
for i in {1..8} ;
do
    echo -en 'q'
done
echo -en 'k'

for i in {6..13} ;
do
    echo -en '\E['$i';10Hx'
    echo -en '   aa'
    echo -en '\E['$i';19Hx'
done
echo -ne '\E[13;12Haaaaaa'
echo -ne '\E[6;13Ha'
echo -ne '\E[7;12Haa'


echo -en '\E[14;10H'
echo -en 'm'
for i in {1..8} ;
do
    echo -en 'q'
done
echo -en 'j'

echo -e '\E(B'