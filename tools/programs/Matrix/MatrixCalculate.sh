#!/bin/csh
#
# FILE     MatrixCalculate.sh
# PACKAGE  Maintenance
# AUTHORS  Edward S. Blurock
#
# CONTENT
#   This Calculates the matrix 
#    of Numeric variables.
#
#    The procedure works by 
#      1. Reading in new values for:
#             RootName: The root name of the distribution 
#                       attributes created
#             AttributeSpecs: The list of variables to 
#                       find the distribution of
#      2. Set up list of Attributes
#      3. Create a Matrix of Instances versus Attributes
#
#c COPYRIGHT (C) 1997 RISC Linz
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
                 $ANALYSIS_BASE/tools/programs/Matrix/MatrixNewParameters.class \
                 $PARAMETERSROOT.dat $DEBUGLEVEL
@ SAVECOUNT++

$PROGRAM xxx Change $SAVE $SAVECOUNT RunAlgorithm InstanceSetUpAlg  $DEBUGLEVEL
$PROGRAM xxx Change $SAVE $SAVECOUNT RunAlgorithm AttributeByNameAlg  $DEBUGLEVEL
$PROGRAM xxx Change $SAVE $SAVECOUNT RunAlgorithm MatrixSetUpAlg      $DEBUGLEVEL

exit(0)
