#! /bin/tcsh -f
#
# FILE     ReportGeneration.sh
# PACKAGE  Maintenance
# AUTHORS  Edward S. Blurock
#
# CONTENT
#    This generates a report (graphs and tables) from matrix data
#
#c COPYRIGHT (C) 1997 RISC Linz
set verbose on

set PROGRAM         = $ANALYSIS_BASE/bin/Flame.exe

if( $#argv <  5) then
    echo   " Usage: $0 RootName  SaveFileRoot  SaveFileCount [DebugLevel]"
    echo   "        SaveFileRoot:           The rootname of the save file"
    echo   "        SaveFileCount:          The count of the current save file"
    echo   "        ReportName:             The name of the report (the root of the generated files)"
    echo   "        X coordinate            The name of the X coordinate"
    echo   "        Y coordinates           The rest is the list of Y coordinate names"
    exit(1)
endif

if($1 == '--program') then
    shift
    set PROGRAM = $1
    shift
endif

echo $1
echo $2
echo $3
echo $4

set  SAVE               = $1
@ SAVECOUNT             = $2
set  ROOTNAME           = $3
echo $4
set  XCOORD             = $4
shift
shift
shift
shift
set SETUP               = $ROOTNAME.inp
set SETUPCLASS          = $ANALYSIS_BASE/tools/programs/Report/ReportSetupClass.inp

set DEBUGLEVEL          = 0

cat <<EOF >! $SETUP
$ROOTNAME ------------------- $ROOTNAME Report -------------------------
Attributes:
%%% ------------------------------------
%%% RootName      String
%%% ------------------------------------
$ROOTNAME
%%% ------------------------------------
%%% Xcoordinate   String
%%% ------------------------------------
$XCOORD
%%% ------------------------------------
%%% Ycoordinates  KeyWords
%%% ------------------------------------
EOF

while($#argv > 0)
echo $1 >> $SETUP
shift
end

echo END >> $SETUP

echo END >> $SETUP

if(!(-d plots)) then 
    mkdir plots
endif

$PROGRAM xxx Operate $SAVE $SAVECOUNT Read $SETUPCLASS $SETUP $DEBUGLEVEL
@ SAVECOUNT++
$PROGRAM xxx Change $SAVE $SAVECOUNT RunAlgorithm MatrixPlotAlg $DEBUGLEVEL

pushd plots
gnuplot Report.plt
popd
exit(0)
