#!/bin/bash

ASTYLE_OPTIONS='--style=google -s2 --indent=spaces=2 --convert-tabs --keep-one-line-blocks --add-brackets --align-pointer=type --align-reference=type --pad-header --max-code-length=80 --lineend=linux --suffix=none --recursive'

astyle $ASTYLE_OPTIONS  \
  '*.cpp'     \
  '*.c'       \
  '*.h'       \

find ./ -name '*.cpp' -print -exec perl -pi -e 's/(2012-)201\d( Jan Starke jan.starke@outofbed.org)/\12015\2/' {} \;
find ./ -name '*.c' -print -exec perl -pi -e 's/(2012-)201\d( Jan Starke jan.starke@outofbed.org)/\12015\2/' {} \;
find ./ -name '*.h' -print -exec perl -pi -e 's/(2012-)201\d( Jan Starke jan.starke@outofbed.org)/\12015\2/' {} \;
