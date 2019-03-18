#!/bin/csh
#
# FILE     InitializeData.sh
# PACKAGE  Maintenance
# AUTHORS  Edward S. Blurock
#
# CONTENT
#   Initialization of the initial algorithms and classes
#
#c COPYRIGHT (C) 1997 RISC Linz
#set verbose on
set PROGRAM         = $ANALYSIS_BASE/bin/Analysis.exe
set DEBUGLEVEL      = 0
set ROOTNAME        = $1
set SAVEDIRECTORY   = saves
set DATADIRECTORY   = data
set OUTDIRECTORY    = out

if($#argv < 2) then
echo    " Usage:  $0 RootName DebugLevel"
echo    "         RootName:   The rootname of the history file"
echo    "         DebugLevel: [optional] The debug level (default 0)"
echo    "         Program:    [optional] if different from Analysis.exe"
echo    "   Sets up in the current directory:  RootName.0.save as the"
echo    "   initial history file"
exit(1)
endif

if($#argv >= 3) then
    set PROGRAM = $3
endif

if($#argv >= 2) then
    set DEBUGLEVEL = $2
endif

echo start $PROGRAM
#--------------------------------------------------------------------
#  The History Save Directory
#--------------------------------------------------------------------
if(!(-d $SAVEDIRECTORY)) then
    mkdir saves
    echo "Making History Save Directory"
else
    echo "History Save Directory already in place"
endif
#--------------------------------------------------------------------
#  The Initial Data Directory
#--------------------------------------------------------------------
if(!(-d $DATADIRECTORY)) then
    mkdir data
    echo "Making Data Directory: Put the initial class and data files here"
else
    echo "Data Directory already in place"
endif
#--------------------------------------------------------------------
#  The Initial Ouput Directory
#--------------------------------------------------------------------
if(!(-d $OUTDIRECTORY)) then
    mkdir out
    echo "Making Output Directory: For output of scripts"
else
    echo "Output Directory already in place"
endif

#--------------------------------------------------------------------
#  The inital history file is setup with algorithm and goal defs
#--------------------------------------------------------------------
echo  "Start running"
$PROGRAM xxxx Initial $ROOTNAME -1 Read $ANALYSIS_BASE/tools/programs/Initial/algClass.inp\
                                   $ANALYSIS_BASE/tools/programs/Initial/algInstance.inp\
                                   $DEBUGLEVEL >& out/initial.out
$PROGRAM xxxx Change $ROOTNAME  0 SetGoalClass TestGoalRun
$PROGRAM xxxx Change $ROOTNAME 0 SetAlgorithmClass TestGoalRun

echo "Result shown in out/initial.out"

exit(0)
