#! /usr/bin/tcsh -f
#  Script to Sort the elements in 'InstanceNameList'
#
set PROGRAM      = Analysis.exe
set TOOLS        = $ANALYSIS_BASE/tools/programs
set SORT         = $TOOLS/Sorting

if($1 == '--program') then
    shift
    set PROGRAM = $1
    shift
endif

if($#argv < 3) then
    echo $0 'Save SaveCount'
    echo 'Save:       The rootname of the save file'
    echo 'SaveCount:  The count of the current save file'
    echo 'SortParameter: The parameter within the instances to sort by'
    exit(1)
endif

set SAVE               = $1
@ SAVECOUNT            = $2
set SORTPARAMTER       = $3

echo Sort by parameter $SORTPARAMTER

cat <<EOF >! Sort.inp
Sorting  Setup for Sorting with an instance parameter
Attributes:
%% ------------------------------------
%% SortParameter           String
%% ------------------------------------
$SORTPARAMETER
%% ------------------------------------
%%  No extra instance info
END
EOF

   $PROGRAM xxx Operate $SAVE $SAVECOUNT  Read $SORT/SortClass.inp Sort.inp 0
@ SAVECOUNT++
   $PROGRAM xxx Change  $SAVE $SAVECOUNT  RunAlgorithm SortInstances 0

rm Sort.inp
