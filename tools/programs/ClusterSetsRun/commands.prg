Read /home/reaction/cvs/Reaction/data/initialize/StandardAlgorithmsClass.inp /home/reaction/cvs/Reaction/data/initialize/StandardAlgorithms.inp 0
SetGoalClass TestGoalRun
SetAlgorithmClass TestGoalRun
Read /home/reaction/cvs/Reaction/data/initialize/StandardLogicClass.inp /home/reaction/cvs/Reaction/data/initialize/StandardLogic.inp 0
Flame ../../many/logIp10-00a00187-7646tf0298.txt 0.000001
MakeInstanceFromMatrix MatrixObject
Read SetUpAttributesClass.inp SetUpAttributes.inp 0
RunAlgorithm AttributeByNameAlg 0
Read CriticalPointsClass.inp CriticalPoints.inp 0
RunGoal PartitionsFromCriticalPoints 0
Read InstanceSetClass.inp InstanceSet.inp 0
RunAlgorithm InstanceSetUpAlg 0
Read CobwebClusteringClass.inp CobwebClustering.inp 0
RunAlgorithm CobwebClusterAlg 0
Read RegionsClass.inp Regions.inp 0
RunAlgorithm ClusterSetsAlg 0
RunAlgorithm SortInstances 0
RunAlgorithm FindConsecutive 0
WindowObject Attribute CobwebClusterTree
WindowObject Attribute
WindowObject Attribute ConsecutiveSet
END

