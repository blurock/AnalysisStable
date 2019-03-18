#!/bin/csh
#
# FILE     DistCalculate.sh
# PACKAGE  Maintenance
# AUTHORS  Edward S. Blurock
#
# CONTENT
#   This Calculates the Distribution of a set
#    of Numeric variables given a 'MatrixObject'
#    in the attributes.
#
#    The procedure works by 
#      1. From Matrix, compute the distributions of the
#         set of attributes and create new attribute parameter    
#
#c COPYRIGHT (C) 1997 RISC Linz
#set verbose on
set PROGRAM         = $ANALYSIS_BASE/bin/Analysis.exe
set MAT             = $ANALYSIS_BASE/tools/programs/Matrix/MatrixCalculate.sh

if( $#argv <  3) then
echo   " Usage: $0 SaveFileRoot  SaveFileCount [DebugLevel]"
echo   "        DistParameterRootName:  The rootname of the input file where the parameters are defined"
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

$MAT    $PARAMETERSROOT $SAVE $SAVECOUNT $DEBUGLEVEL

@ SAVECOUNT++

$PROGRAM xxx Change $SAVE $SAVECOUNT RunAlgorithm DistributionAlg     $DEBUGLEVEL

exit(0)
