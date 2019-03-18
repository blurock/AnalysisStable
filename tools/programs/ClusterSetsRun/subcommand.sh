#! /bin/tcsh -f
#

set HERE = $ANALYSIS_BASE/tools/programs/ClusterSetsRun


set MATRIX        = $1
set DECNUM        = $2
set CRITICALPROTO = $3
set OUTFILE       = $4
set REGIONSFILE   = $5

#set CRITICALPROTO   = $HERE/CriticalPointPairs.proto
set CRITICALDAT     = CriticalPointPairs.dat

sed "s/XXXX/$DECNUM/g"\
		$CRITICALPROTO >! $CRITICALDAT

cat <<EOF > commands.prg
Read $REACTION_BASE/data/initialize/StandardAlgorithmsClass.inp $REACTION_BASE/data/initialize/StandardAlgorithms.inp 0
SetGoalClass TestGoalRun
SetAlgorithmClass TestGoalRun
Read $REACTION_BASE/data/initialize/StandardLogicClass.inp $REACTION_BASE/data/initialize/StandardLogic.inp 0
Flame $MATRIX 0.000001
MakeInstanceFromMatrix MatrixObject
Read $HERE/SetUpAttributesClass.inp $HERE/SetUpAttributes.inp 0
RunAlgorithm AttributeByNameAlg 0
Read $HERE/CriticalPointsClass.inp $HERE/CriticalPoints.inp 0
RunGoal PartitionsFromCriticalPoints 0
Read $HERE/InstanceSetClass.inp $HERE/InstanceSet.inp 0
RunAlgorithm InstanceSetUpAlg 0
Read $HERE/CobwebClusteringClass.inp $HERE/CobwebClustering.inp 0
RunAlgorithm CobwebClusterAlg 0
Read $HERE/RegionsClass.inp $HERE/Regions.inp 0
RunAlgorithm ClusterSetsAlg 0
RunAlgorithm SortInstances 0
RunAlgorithm FindConsecutive 0
WindowObject Attribute CobwebClusterTree
WindowObject Attribute
WindowObject Attribute ConsecutiveSet
END

EOF
/home/reaction/cvs/AnalysisBinaries/Flame.exe xxx Initial tst 0 < commands.prg >& $OUTFILE
java -classpath /home/reaction/react.jar blurock.CobwebCluster.CobwebRegionFinder $OUTFILE $REGIONSFILE






