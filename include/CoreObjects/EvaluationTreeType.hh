/*  FILE     EvaluationTreeType.hh
**  PACKAGE  EvaluationTree
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "EvaluationTree" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_EVALUATIONTREETYPE_HH
#define CoreObjects_EVALUATIONTREETYPE_HH

 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
class DataEvaluationTreeClass;

/*C BaseDataEvaluationTree  . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the EvaluationTree class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataEvaluationTree : public BaseDataAlgorithmOperation
{  
public:
  BaseDataDirectedTree Tree;

  BaseDataEvaluationTree();
  BaseDataEvaluationTree(const BaseDataEvaluationTree& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataEvaluationTreeClass . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataEvaluationTreeClass : public DataAlgorithmOperationClass
{
public:
  DataDirectedTreeClass TreeClass;
  
  DataEvaluationTreeClass();
  DataEvaluationTreeClass(const DataEvaluationTreeClass& data);
  DataEvaluationTreeClass(const int id, 
		    const String& name,
		    const String& descr);

  STANDARD_VIRTUAL_METHODS_CLASS
};
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
