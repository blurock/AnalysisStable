/*  FILE     ChemkinConvertType.hh
**  PACKAGE  ChemkinConvert
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "ChemkinConvert" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 Cantera Project, RISC Linz
*/
 
#ifndef Cantera_CHEMKINCONVERTTYPE_HH
#define Cantera_CHEMKINCONVERTTYPE_HH

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/


/*C RxnDataReadChemkin  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ReadChemkin class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithm
*/
class RxnDataReadChemkin : public BaseDataAlgorithmOperation {
  String chemkinFileNameExtension;
  String thermoFileNameExtension;
  String fileRootNameS;
  String MoleculeClassS;
  String ReactionClassS;
  String MechanismClassS;
  String ChemkinClassS;
  String ReactionRateS;
  String ThirdBodyS;
  String ReactionRateHiLowS;
  String ChemkinThermoNameS;
  String ChemkinNameS;
  String ReferenceS;
  String MoleculeSummaryS;

  RxnSimpleMoleculeClass *MoleculeClass;
  RxnReactionClass *ReactionClass;
  RxnMechanismClass *MechanismClass;
  RxnChemkinThermoClass *ChemkinClass;
  RxnMoleculeSummaryClass *MolSummaryClass;

  RxnReactionRatesClass *ReactionRateClass;
  RxnReactionRatesClass *ThirdBodyClass;
  RxnReactionRatesClass *ReactionRateHiLowClass;

  RxnDataLiteratureReference *Reference;
  String ChemkinName;
  String ChemkinThermoName;

  BaseDataSetOfObjects Chemkin;
  BaseDataSetOfObjects Molecules;
  BaseDataSetOfObjects Reactions;
  BaseDataSetOfObjects *MolSummary;

  RxnDataMechanism *Mechanism;

  BaseDataString *chemkinFileRoot;

  BaseDataKeyWords *ReactionList;

  String chemkinFileName;
  String thermoFileName;
  bool twoFiles;

  int reactionCount;

   void printReactionCoefficients(ckr::Reaction *rxn, ostream& out);
   void addNewSpeciesToInstances(BaseDataSetOfInstances *instances,
				 vector<ckr::RxnSpecies>& species);
  void SetUpMechanismInInstance(BaseDataSetOfInstances *instances);
   String *determineReactionName(ckr::Reaction& rxn);
   void fromReactionSet(vector<ckr::RxnSpecies>& species, String *name);
   BaseDataInstance *MakeNewInstance(String name, BaseDataSetOfInstances *instances);
  void BuildMoleculeData(BaseDataSetOfInstances *instances,
			 DataSetOfInstancesClass *instancesclass,
			 ckr::speciesList specieslist);
  bool StoreThermoInMolecule(RxnDataChemkinThermo *chemkin,
			     RxnDataSimpleMolecule *molecule,
			     BaseDataInstance *instance);
  bool StoreChemkinNameInMolecule(String& name,
				  RxnDataSimpleMolecule *molecule,
				  BaseDataInstance *instance);
  void TransferThermoData(RxnDataChemkinThermo *chemkin,
			  ckr::Species& species);
  void FormFormulaDescriptor(ckr::Species& species,String *full);
  void BuildReactionSet(BaseDataSetOfInstances *instances,
			DataSetOfInstancesClass *instancesclass,
			vector<ckr::Reaction> reactions);
  RxnDataReaction *MakeReaction(String& rxnname, BaseDataInstance *instance);
  void MakeRates(ckr::Reaction &chemkinrxn, 
		 DataSetOfObjectsClass *instanceclasses,
		 RxnDataReaction *rxn, 
		 BaseDataInstance *instance);
  RxnDataReactionRates *formReactionRate(ckr::RateCoeff &chemkinrate, 
					 RxnReactionRatesClass *rateclass,
					 bool forward);

  BaseDataKeySet *getReactionSpecies(vector<ckr::RxnSpecies>& species, 
				  DataKeySetClass *setclass, 
				  RxnDataMoleculeSet *mols,
				  bool forward);
  void AddReactionSummaryToMechanism(String& rxnname,
				     BaseDataInstance *instance,
				     RxnDataReactionRates *forward,
				     RxnDataReactionRates *reverse);
  void FillInThirdBodyCoefficients(RxnDataReactionRates *forward,
				   RxnDataReactionRates *reverse,
				   map<string, double> third);
  void FillInFallOffCoefficients(RxnDataReactionRates *rate,
				 ckr::Reaction &chemkinrxn);
  void AddAtomProperties(ckr::Species& species, 
			 RxnDataSimpleMolecule *simple);

public:
  RxnDataReadChemkin();
  RxnDataReadChemkin(const RxnDataReadChemkin& data);
  
  void setChemkinExtension(String& ext) { chemkinFileNameExtension = ext;};
  void setThermoExtension(String& ext) { thermoFileNameExtension = ext;};
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C RxnReadChemkinClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmClass
*/
class RxnReadChemkinClass : public DataAlgorithmOperationClass
{
public:
  RxnReadChemkinClass();
  RxnReadChemkinClass(const RxnReadChemkinClass& data);
  RxnReadChemkinClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};



#endif
