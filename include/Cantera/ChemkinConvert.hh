/*  FILE     ChemkinConvert.hh
**  PACKAGE  ChemkinConvert
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "ChemkinConvert" package in the Cantera environment
**
**  COPYRIGHT (C) 2000 Edward S. Blurock
*/
 
#ifndef Cantera_CHEMKINCONVERT_HH
#define Cantera_CHEMKINCONVERT_HH

#define CHEMKINCONVERT_READCHEMKIN_ID    CHEMKINCONVERT_BASE_ID + 10
#define CHEMKINCONVERT_READCHEMKIN_NAME  "ReadChemkin"

#define DEFAULT_CHEMKIN_EXT        ".ckm"
#define DEFAULT_THERMO_EXT         ".thm"
#define CHEMKINREAD_FILEROOT       "FileRoot"
#define DATABASE_NAME_PARAMETER    "DBaseName"
#define MOLECULE_CLASS_PARAMETER      "MoleculeClass"
#define REACTION_CLASS_PARAMETER      "ReactionClass"
#define MECHANISM_CLASS_PARAMETER     "MechanismClass"
#define CHEMKIN_CLASS_PARAMETER    "ChemkinClass"
#define THERMO_NAME_PARAMETER      "ThermoNameInInstance"
#define CHEMKIN_NAME_PARAMETER     "ChemkinNameInInstance"
#define MOLECULE_SUMMARY_PARAMETER "MoleculeSummaryName"
#define REACTION_RATE_NAME         "ReactionRate"


/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "ChemkinConvertType.hh"



/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
void InitialChemkinConvertDecodeFunctions();
void AddChemkinConvertClasses(DataSetOfObjectsClass& set);

#endif
