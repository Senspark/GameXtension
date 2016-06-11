#!/usr/bin/python

# define global variables
context = {
"src_dialog_name"   : "undefined",
"dst_dialog_name"   : "undeifned",
"src_dialog_path"   : "undefined",
"dst_dialog_path"   : "undefined",
"background"        : "undefined",
"ok_graphics"       : "undefined",
"close_graphics"    : "undefined",
"script_dir"        : "undefined",
}

import sys
import os, os.path
import json
import shutil

def dumpUsage():
    print "Usage: make_dialog.py -name DIALOG_NAME -directory DIRECTORY -background BACKGROUND -ok OK_BTN_GRAPHICS -close CLOSE_BTN_GRAPHICS"
    print "Options:"
    print "  -name              DIALOG_NAME                 Dialog name, for example: OptionDialog"
    print "  -path              PATH                        Dialog path, for example: ~/my-src-code/my-proj/proj.cocosbuilder/ccb"
    print "  -background        BACKGROUND                  Dialog background image/texture is used in your dest Cocosbuilder project, for example: background.png"
    print "  -ok_graphics       OK_BTN_GRAPHICS             Ok button image/texture is used in your dest Cocosbuilder project, for example: texture-sheet.plist/ok-btn.png"
    print "  -close_graphics    CLOSE_BTN_GRAPHICS          Close button image/texture is used in your dest Cocosbuilder project, for example: texture-sheet.plist/close-btn.png"
    print ""
    print "Sample: ./make_dialog.py -name OptionDialog -directory ~/my-src-code/my-proj/proj.cocosbuilder/ccb -ok_graphics texture-sheet.plist/ok-btn.png -close_graphics texture-sheet.plist/close-btn.png"
    print ""


def checkParams(context):
    # generate our internal params
    context["script_dir"] = os.getcwd() + "/"
    global platforms_list
    
    # invalid invoke, tell users how to input params
    if len(sys.argv) < 5:
        dumpUsage()
        sys.exit()
    
    # find our params
    for i in range(1, len(sys.argv)):
        if "-name" == sys.argv[i]:
            context["dst_dialog_name"] = sys.argv[i+1]
        elif "-path" == sys.argv[i]:
            context["dst_dialog_path"] = sys.argv[i+1]
        elif "-background" == sys.argv[i]:
            context["background"] = sys.argv[i+1]
            if context["background"].endswith(".png") == False:
                context["background"] += ".png"
        elif "-ok_graphics" == sys.argv[i]:
            context["ok_graphics"] = sys.argv[i+1]
        elif "-close_graphics" == sys.argv[i]:
            context["close_graphics"] = sys.argv[i+1]
    
    # pinrt error log our required paramters are not ready
    raise_error = False
    if context["dst_dialog_name"] == "undefined":
        print "Invalid -name parameter"
        raise_error = True
    if context["dst_dialog_path"] == "undefined":
        print "Invalid -path parameter"
        raise_error = True

    if raise_error != False:
        sys.exit()

    context["src_dialog_name"] = "PopupDialog.ccb"
    context["src_dialog_path"] = "../tests/proj.cocosbuilder/ccb"


# end of checkParams(context) function


# -------------- main --------------
# dump argvs

checkParams(context)

print "Start jobs"

destFile = context["dst_dialog_path"] + "/" + context["dst_dialog_name"]+".ccb"

cmd = "cp " + context["src_dialog_path"] + "/" + context["src_dialog_name"] + " " + destFile
print "Copy ccb file to destination path"
print cmd
os.system(cmd)

cmd = "sed -i.bak 's@PopupDialog@" + context["dst_dialog_name"] + "@g' " + destFile
print "Change dialog name..."
print cmd
os.system(cmd)

if context["background"]!="undefined":
    if len(context["background"].split('/')) == 1:
        cmd = "sed -i.bak 's@dialog-background\.png@" + context["background"] + "@g' " + destFile
    else:
        bg1 = context["background"].split('/')[0]
        bg2 = context["background"].split('/')[1]
        cmd = "sed -i.bak -n '1h;1!H;${;g;s@<string></string>\([^a-z]*\)<string>dialog-background\.png</string>@<string>" + bg1 + "</string>\\1<string>" + bg2 + "</string>@g;p;}' " + destFile

    print "Change background..."
    print cmd
    os.system(cmd)

if context["ok_graphics"]!="undefined":
    if len(context["ok_graphics"].split('/')) == 1:
        cmd = "sed -i.bak 's@>btn-[01]\.png<@>" + context["background"] + "<@g' " + destFile
    else:
        ok1 = context["ok_graphics"].split('/')[0]
        ok2 = context["ok_graphics"].split('/')[1]
        cmd = "sed -i.bak -n '1h;1!H;${;g;s@<string></string>\([^a-z]*\)<string>btn-\([01]\)\.png</string>@<string>" + ok1 + "</string>\\1<string>" + ok2 + "-\\2.png</string>@g;p;}' " + destFile

    print "Change ok graphics..."
    print cmd
    os.system(cmd)

if context["close_graphics"]!="undefined":
    if len(context["close_graphics"].split('/')) == 1:
        cmd = "sed -i.bak -e 's@close-btn-[01]\.png@" + context["background"] + "@g' " + destFile
    else:
        close1 = context["close_graphics"].split('/')[0]
        close2 = context["close_graphics"].split('/')[1]
        cmd = "sed -i.bak -n '1h;1!H;${;g;s@<string></string>\([^a-z]*\)<string>close-btn-\([01]\)\.png</string>@<string>" + close1 + "</string>\\1<string>" + close2 + "-\\2.png</string>@g;p;}' " + destFile

    print "Change close graphics..."
    print cmd
    os.system(cmd)

os.system("rm " + destFile + ".bak")



