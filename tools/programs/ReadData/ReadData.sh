#! /bin/tcsh -f
#
# FILE     ReadData.sh
# PACKAGE  System
# AUTHORS  Edward S. Blurock
#
# CONTENT
#   Reading in a Data file
#       The input is:
#                1. The current directory    .
#                2. The history name         test
#                3. The current level        0
#                4. The Debug Level          1
#         What is created:
#                data/ReadData.dat The data file with input file specification
#                out/read.l.1.out: The output of the reading of the ReadData files
#                out/read.l.2.out: The output of the reading of the actual data files
#               saves/history.l.saves  is updated by one
#
#c COPYRIGHT (C) 1998 ANALYSIS++ Project Edward S. Blurock

#set verbose on

set PROGRAM         = $ANALYSIS_BASE/bin/Analysis.exe
if($#argv > 0) then
    if($1 == '--program') then
	shift
	set PROGRAM = $1
	shift
    endif
endif

if($#argv < 5) then
    echo    " Usage:  $0 RootName DebugLevel"
    echo    "         Directory:  The data directory"
    echo    "         RootName:   The rootname of the history file"
    echo    "         Level:      The current level (will be incremented)"
    echo    "         Debug:      The debug level to use"
    echo    "         Files:      A list of class and data filename pairs"
    exit(1)
endif

set CURRENTDIR      = $1
shift
set HISTORY         = $1
shift
set LEVEL           = $1
shift
set DEBUGLEVEL      = $1
shift
set FILES =
while($#argv > 0)
    set FILES = "$FILES $1"
    shift
end

echo $FILES

set CLASSFILE       = $ANALYSIS_BASE/tools/programs/ReadData/ReadData.class
set DATAFILE        = $CURRENTDIR/data/ReadData.dat
set OUTPUT1         = $CURRENTDIR/out/read.$LEVEL.1.out
set OUTPUT2         = $CURRENTDIR/out/read.$LEVEL.2.out

cat <<EOF > $DATAFILE
% **********************************************************
% The Attributes and Instances to be read in
% **********************************************************
%
The Set Of Read In Instances
%
% ----------------------------------------------------------
%  The set of attributes (as specified by the class)
% ----------------------------------------------------------
Attributes:
% GoalDebug
$DEBUGLEVEL
% (ClassFile, DataFile) pairs
$FILES
END
% ----------------------------------------------------------
%  The set of attributes (as specified by the class)
%  None given
% ----------------------------------------------------------
END
EOF
@ SAVECOUNT = $LEVEL
$PROGRAM xxx Operate $HISTORY $SAVECOUNT Read $CLASSFILE $DATAFILE $DEBUGLEVEL >&! $OUTPUT1
@ SAVECOUNT++
$PROGRAM xxx Change  $HISTORY $SAVECOUNT RunGoal ReadInstances >&! $OUTPUT2

exit(0)
