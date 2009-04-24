#!/bin/bash

IRRLITCH_DIR=../irrlicht_1.5_svn

echo copying...
for f in $(find . -type f)
do
	if [[ $f != */.svn* ]]
	then
		if [[ $f != ./*.sh ]]
		then
			if [ ! -d ./$IRRLITCH_DIR/$(dirname $f) ]
			then
				echo makedir ./$IRRLITCH_DIR/$(dirname $f)
				mkdir -p ./$IRRLITCH_DIR/$(dirname $f)
			fi
			cp $f $IRRLITCH_DIR/$f
			echo $IRRLITCH_DIR/$f
		fi
	fi
done