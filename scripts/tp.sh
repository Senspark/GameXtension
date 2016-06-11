#!/bin/sh

TP=/usr/local/bin/TexturePacker

# create ipadhd &amp
${TP} --smart-update --scale 1 "$1".tps \
--format cocos2d \
--data ../Resources-gen/resources-ipadhd/"$1".plist \
--sheet ../Resources-gen/resources-ipadhd/"$1".png

# create iphonehd assetss
${TP} --smart-update --scale 0.5 "$1".tps \
--format cocos2d \
--data ../Resources-gen/resources-iphonehd/"$1".plist \
--sheet ../Resources-gen/resources-iphonehd/"$1".png

# create iphone assets
${TP} --smart-update --scale 0.25 "$1".tps \
--format cocos2d \
--data ../Resources-gen/resources-iphone/"$1".plist \
--sheet ../Resources-gen/resources-iphone/"$1".png

# create cocosbuilder assets
${TP} --smart-update --scale 0.25 "$1".tps \
--format cocos2d \
--data ../proj.cocosbuilder/"$1".plist \
--sheet ../proj.cocosbuilder/"$1".png

exit 0