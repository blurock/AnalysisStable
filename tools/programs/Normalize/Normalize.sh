#! /bin/csh -f
#
# FILE     Normalize.sh
# PACKAGE  Maintenance
# AUTHORS  Edward S. Blurock
#
# CONTENT
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

if( $#argv <  6) then
echo   " Usage: $0  SaveFileRoot SaveFileCount RootName [DebugLevel]"
echo   "        SaveFileRoot:           The rootname of the save file"
echo   "        SaveFileCount:          The count of the current save file"
echo   "        RootName:               The rootname of the input file where the parameters are defined"
echo   "        Offset Type:            ZeroPreserving, MinimumIsZero, AverageOffSet, MeanOffSet"
echo   "        Scale Type:             WidthScale, NoScale "
echo   "        Distribution Params     The list of distribution parameters"
exit(1)
endif

set  PARAMETERSROOT     = $3
set  SAVE               = $1
@ SAVECOUNT             = $2
set OFFSET              = $4
set SCALE               = $5
set DEBUGLEVEL          = 0
set ALGORITHM           = NormalizeAlg
set NORMALIZE           = $PARAMETERSROOT.inp

shift
shift
shift
shift
shift

cat <<EOF > $NORMALIZE
op Definitions ---------------- ParameterizeNormalization Demo ------------------------
Attributes:
%% -------------------------------------------------
%%    NormalizeAlg                   AlgorithmSummary
%% -------------------------------------------------
                                    % The name of the Algorithm
Initial StatisticsAlgs END          % The Algorithm Category
$OFFSET $SCALE END                  % The Algorithm Keywords
NormalizationOps END                % Algorithm Specification
                                    % Algorithm Input Parameters
OperationRoot     String
Distributions     KeyWords
OperationClass    String
ExpressionTreeClass String
END
                                    % Algorithm Output Parameters
OperationList   %%  KeyWords
END
%% ----------------------------------------
%% OperationRoot    String
%% ----------------------------------------
NormOp
%% ----------------------------------------
%% OperationClass    String
%% ----------------------------------------
ParameterizedNormalize
%% ----------------------------------------
%% ExpressionTreeClass String
%% ----------------------------------------
NormalizeParameters
%% ----------------------------------------
%% Distributions       KeyWords
%% ----------------------------------------
EOF

while($#argv > 0)
echo " $1 " >> $NORMALIZE
shift
end

cat <<EOF >> $NORMALIZE
END
%% ----------------------------------------
END

EOF

echo start $PROGRAM
$PROGRAM xxx Operate $SAVE $SAVECOUNT Read \
                 $ANALYSIS_BASE/tools/programs/Normalize/NormalizeClass.inp \
                 $PARAMETERSROOT.inp $DEBUGLEVEL
@ SAVECOUNT++
$PROGRAM xxx Operate $SAVE $SAVECOUNT RunAlgorithm $ALGORITHM  $DEBUGLEVEL

exit(0)
