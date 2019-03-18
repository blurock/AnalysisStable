#! /usr/bin/tcsh -f
#  Script to Isolate the set of cluster node instances from a ClusterObject
#
set PROGRAM      = Analysis.exe
set TOOLS        = $ANALYSIS_BASE/tools/programs
set CLUSTER      = $TOOLS/ClusterSet

if($1 == '--program') then
    shift
    set PROGRAM = $1
    shift
endif

if($#argv < 4) then
    echo $0 'Save SaveCount'
    echo 'Save:       The rootname of the save file'
    echo 'SaveCount:  The count of the current save file'
    echo 'RootName:   The root name of the generated set of instances'
    echo 'Cluster:    The cluster hierarchy'
    exit(1)
endif

set SAVE               = $1
@ SAVECOUNT            = $2
set ROOTNAME           = $3
set CLUSTER            = $4

echo Isolate Node Cluster Sets

cat <<EOF >! ClusterSets.inp
Distribution  Setup for Flame
Attributes:
%% ------------------------------------
%% RootName    String
%% ------------------------------------
$ROOTNAME
%% ------------------------------------
%% ClusterObject           String
%% ------------------------------------
$CLUSTER
%% ------------------------------------
%% No Additional Instance Info
END
EOF

   $PROGRAM xxx Operate $SAVE $SAVECOUNT  Read $CLUSTERSET/ClusterSetsClass.inp ClusterSets.inp 0
@ SAVECOUNT++
   $PROGRAM xxx Change  $SAVE $SAVECOUNT  RunAlgorithm ClusterSets 0

rm ClusterSet.inp
