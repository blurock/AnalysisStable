#!/bin/csh
#
# FILE     InstanceSetCalculate.sh
# PACKAGE  Maintenance
# AUTHORS  Edward S. Blurock
#
# CONTENT
#   This Calculates the training and test sets 
#
#    The procedure works by 
#      1. Set up the InstanceNameList and the TestPercentage (through a Read)
#      2. Run 'InstanceSetUpAlg'
#
#c COPYRIGHT (C) 2000 Edward S. Blurock
#set verbose on

set PROGRAM         = $ANALYSIS_BASE/bin/Analysis.exe
if($#argv > 0) then
    if($1 == '--program') then
	shift
	set PROGRAM = $1
	shift
    endif
endif

if( $#argv <  3) then
echo   " Usage: $0 RootName  SaveFileRoot  SaveFileCount [DebugLevel]"
echo   "        RootName:               The rootname of the input file where the parameters are defined"
echo   "        SaveFileRoot:           The rootname of the save file"
echo   "        SaveFileCount:          The count of the current save file"
echo   "        DebugLevel:             [optional] Debug Level"
exit(1)
endif

set  PARAMETERS         = $1
set  SAVE               = $2
@ SAVECOUNT             = $3
if($#argv > 3) then
set DEBUGLEVEL          = $4
else
set DEBUGLEVEL          = 0
endif

echo start $PROGRAM
$PROGRAM xxx Operate $SAVE $SAVECOUNT Read \
                 $ANALYSIS_BASE/tools/programs/InstanceSets/InstanceSetsClass.inp \
                 $PARAMETERS.inp $DEBUGLEVEL
@ SAVECOUNT++

$PROGRAM xxx Change $SAVE $SAVECOUNT RunAlgorithm InstanceSetUpAlg  $DEBUGLEVEL
exit(0)
