#!bash
#This script creates a patch of the irrlicht physics from the irrlicth directory in the current (patch) directory

cd ../irrlicht_1.5_svn
EXPORTDIR=../patch
for f in $(find $EXPORTDIR -type f)
do
	if [[ $f != */.svn* ]]
	then
		# TOREMOVE=$TOREMOVE" "$f
		rm $f
		#echo $f
	fi
done
exit
FILES=$(find . -regextype posix-extended -regex "\./(include|source).*PhX.*(cpp|h)")
#FILES=$FILES" "$(find include/ -name PhX*h)
#FILES=$FILES" "$(find source/ -name PhX*cpp)
#FILES=$FILES" "$(find include/ -name PhX*cpp)
FILES=$FILES" "$(find examples/ -wholename *PhysicsMeshViewer/main.cpp)
FILES=$FILES" "$(find examples/ -wholename *PhysicsMeshViewer/save.png)
FILES=$FILES" "$(find examples/ -wholename *Demo/CDemo.h)
FILES=$FILES" "$(find source/ -regextype posix-extended -regex ".*CXMeshFileLoader\.(h|cpp)")
FILES=$FILES" "$(find source/ -regextype posix-extended -regex ".*CSkinnedMesh\.(h|cpp)")
FILES=$FILES" "$(find source/ -regextype posix-extended -regex ".*CSceneNodeAnimatorCameraFPS\.(h|cpp)")
FILES=$FILES" "$(find . -regextype posix-extended -regex "\./(include|source).*SceneManager\.(h|cpp)")
FILES=$FILES" "$(find . -regextype posix-extended -regex "\./(include|source).*SKeyMap\.h")
FILES=$FILES" "./include/irrString.h
FILES=$FILES" "$0
FILES=$FILES" "./media/dwarf.phx
FILES=$FILES" "./media/config.xml
FILES=$FILES" "$(find export/ -iname "*.*x")
FILES=$FILES" "./source/Irrlicht/Makefile
FILES=$FILES" "./source/Irrlicht/SConstruct
FILES=$FILES" "./source/Irrlicht/Irrlicht9.0.vcproj
FILES=$FILES" "./importPhx.sh

for f in $FILES
do
	#echo $(dirname $f)
	mkdir -p ./$EXPORTDIR/$(dirname $f)
	cp $f $EXPORTDIR/$f
done