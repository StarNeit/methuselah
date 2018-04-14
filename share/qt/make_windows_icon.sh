#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/methuselah.png
ICON_DST=../../src/qt/res/icons/methuselah.ico
convert ${ICON_SRC} -resize 16x16 methuselah-16.png
convert ${ICON_SRC} -resize 32x32 methuselah-32.png
convert ${ICON_SRC} -resize 48x48 methuselah-48.png
convert methuselah-16.png methuselah-32.png methuselah-48.png ${ICON_DST}

