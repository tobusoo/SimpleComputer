#!/bin/bash

echo -ne '\E[H\E[J' # Clear
echo -ne '\E[5;10H\E[31mНИКИТА'
echo -ne '\E[6;8H\E[32m\E[47mИС-241\E[10;1H\E[0m'
# echo -e '\E[41m'lol'\E[0m' # set background color
# echo -e '\E[?25l\E[?1c' # hide cursor 
# echo -e '\E[?25h\E[?8c' # visible cursor
# echo -e '\E[M' # clear line 