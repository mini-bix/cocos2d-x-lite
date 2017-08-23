cp -f anysdk_appstore/src_ori/* /Applications/CocosCreator.app/Contents/Resources/static/build-templates/anysdk
git checkout -- extensions/anysdk/js-bindings
python download-deps.py
BUILD=`../client/builddir.sh`
cp -rf anysdk_appstore/js-bindings_ori/* ../client/"$BUILD"frameworks/runtime-src/Classes
