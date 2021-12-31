#!/bin/sh

picom &
# redshift -P -O 4500
dunst &
# brightnessctl set 75

# set background
~/.fehbg
# launch installed bar
~/.dwm/launchbar.sh &

sxhkd -c ~/.config/sxhkd/sxhkdrc &
dwm