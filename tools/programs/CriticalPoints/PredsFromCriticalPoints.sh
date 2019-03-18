#!/bin/csh
#
# FILE     runit.sh
# PACKAGE  PredsFromCriticalPoints.sh
# AUTHORS  Edward S. Blurock
#
# CONTENT
#   Generic run of predicate generation from critical points
#
#c COPYRIGHT (C) 1997 RISC Linz
#set verbose on
set PROGRAM         = Analysis.exe
set CLASSFILE       = $ANALYSIS_BASE/tools/programs/CriticalPoints/CriticalPointsParameters.class

if($1 == '--program') then
    shift
    set PROGRAM = $1
    shift
endif

if( $#argv <  3) then
echo   " Usage: $0 RootName  SaveFileRoot  SaveFileCount [DebugLevel]"
echo   "        RootName:              The rootname of the input file where the parameters are defined"
echo   "        SaveFileRoot:          The rootname of the save file"
echo   "        SaveFileCount:         The count of the current save file"
echo   "        DebugLevel:            [optional] Debug Level"
exit(1)
endif

set  PARAMETERSROOT     = $1
set  SAVE               = $2
@ SAVECOUNT             = $3
if($#argv > 3) then
set DEBUGLEVEL          = $4
else
set DEBUGLEVEL          = 0
endif

$PROGRAM xxx Operate $SAVE $SAVECOUNT Read \
                 $CLASSFILE \
                 $PARAMETERSROOT.dat $DEBUGLEVEL
@ SAVECOUNT++
$PROGRAM xxx Change $SAVE $SAVECOUNT RunGoal PartitionsFromCriticalPoints $DEBUGLEVEL
