#! /usr/bin/tcsh -f
#
# FILE     Cobweb.sh
# PACKAGE  Maintenance
# AUTHORS  Edward S. Blurock
#
# CONTENT
#
#c COPYRIGHT (C) 1997 RISC Linz
#set verbose on
set PROGRAM         = $ANALYSIS_BASE/bin/Analysis.exe

if( $#argv <  3) then
echo   " Usage: $0 SaveFileRoot  SaveFileCount [DebugLevel]"
echo   "        CobwebRoot           :  The rootname of the input file where the parameters are defined"
echo   "        SaveFileRoot:           The rootname of the save file"
echo   "        SaveFileCount:          The count of the current save file"
echo   "        DebugLevel:             [optional] Debug Level"
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
                 $ANALYSIS_BASE/tools/programs/Cobweb/Cobweb.class \
                 $PARAMETERSROOT.dat $DEBUGLEVEL

@ SAVECOUNT++

$PROGRAM xxx Change $SAVE $SAVECOUNT RunAlgorithm CobwebClusterAlg     $DEBUGLEVEL

exit(0)
