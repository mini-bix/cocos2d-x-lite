cp -f anysdk_appstore/src/* /Applications/CocosCreator.app/Contents/Resources/static/build-templates/anysdk
cp -rf anysdk_appstore/protocols_libc++/include/* external/ios/include/anysdk
cp -rf anysdk_appstore/protocols_libc++/libPluginProtocol.a external/ios/libs
cp -rf anysdk_appstore/js-bindings/* extensions/anysdk/js-bindings
BUILD=`../client/builddir.sh`
cp -rf extensions/anysdk/js-bindings/* ../client/"$BUILD"frameworks/runtime-src/Classes
