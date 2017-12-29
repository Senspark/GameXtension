#!/bin/sh

#  TP-update.sh
#  gold-miner
#
#  Created by greewoo on 5/30/13.
#

TP=/usr/local/bin/TexturePacker
if [ "${ACTION}" = "clean" ]
then
# remove all files
rm ../Resources-gen/resources-iphone/general-sheet.png
rm ../Resources-gen/resources-iphone/general-sheet.plist
rm ../Resources-gen/resources-iphonehd/general-sheet.png
rm ../Resources-gen/resources-iphonehd/general-sheet.plist
rm ../Resources-gen/resources-ipadhd/general-sheet.png
rm ../Resources-gen/resources-ipadhd/general-sheet.plist
rm ../proj.cocosbuilder/general-sheet.png
rm ../proj.cocosbuilder/general-sheet.plist

else

# GENERAL SHEET

# create ipadhd assetss
${TP} --smart-update --scale 1 general-sheet.tps \
--format cocos2d \
--data ../Resources-gen/resources-ipadhd/general-sheet.plist \
--sheet ../Resources-gen/resources-ipadhd/general-sheet.png

# create iphonehd assetss
${TP} --smart-update --scale 0.5 general-sheet.tps \
--format cocos2d \
--data ../Resources-gen/resources-iphonehd/general-sheet.plist \
--sheet ../Resources-gen/resources-iphonehd/general-sheet.png

# create iphone assetss
${TP} --smart-update --scale 0.25 general-sheet.tps \
--format cocos2d \
--data ../Resources-gen/resources-iphone/general-sheet.plist \
--sheet ../Resources-gen/resources-iphone/general-sheet.png

# create assets for cocosbuilder
${TP} --smart-update --scale 0.25 general-sheet.tps \
--format cocos2d \
--data ../proj.cocosbuilder/general-sheet.plist \
--sheet ../proj.cocosbuilder/general-sheet.png

fi
exit 0