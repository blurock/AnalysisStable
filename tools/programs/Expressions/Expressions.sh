#!/bin/csh
#
# FILE     Expressions.sh
# PACKAGE  Maintenance
# AUTHORS  Edward S. Blurock
#
# CONTENT
#   run of several analyses
#
#c COPYRIGHT (C) 1997 RISC Linz
#set verbose on
set PROGRAM         = /home/analysis/Analysis/FullSystem/examples/FullSystem/otest
set DEBUGLEVEL      = 0

if( $#argv <  3) then
echo   " Usage: $0 PCAParameterRootName  SaveFileRoot  SaveFileCount [DebugLevel]"
echo   "        ParameterRootName:     The rootname of the input file where the expressions are defined"
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

echo start $PROGRAM
$PROGRAM xxx Operate $SAVE $SAVECOUNT Read \
                   $PARAMETERSROOT.class\
                   $PARAMETERSROOT.dat \
                   $DEBUGLEVEL
@ SAVECOUNT++

$PROGRAM xxx Change $SAVE $SAVECOUNT RunAlgorithm ExpressionTreeAlg   $DEBUGLEVEL

exit(0)
