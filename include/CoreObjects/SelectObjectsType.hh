/*  FILE     SelectObjectsType.hh
**  PACKAGE  SelectObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "SelectObjects" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_SELECTOBJECTSTYPE_HH
#define CoreObjects_SELECTOBJECTSTYPE_HH

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
class DataSelectedClass;
class DataSelectionsClass;
class DataSelectionCategoryClass;
class DataSelectionTreeClass;

/*C BaseDataSelections  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the Selections class
**
**    This class manages a list of selected objects.  The objects are
**    kept in a list and are accessed, not by the name of the object but
**    by the selection name.  The philosophy is that the object is a 
**    specific case of the selection category.  It is used by 
**    the SelectionTree class to store the list of specific selections from
**    categories.
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataSelections : public BaseDataObject
{
  BaseDataSetOfObjects Selections;
  AlternativeNames CategoryObjectNames;
  
public:
  BaseDataSelections();
  BaseDataSelections(const BaseDataSelections& data);

  bool AddSelectedObject(const String& name, BaseDataObject& object);
  BaseDataObject* GetSelectedObject(const String& name);
  AlternativeNames& GetNameCategoryCorrespondences();
  ObjectList<String> GetListOfSelections();

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataSelectionsClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataSelectionsClass : public DataObjectClass
{
public:
  DataSelectionsClass();
  DataSelectionsClass(const DataSelectionsClass& data);
  DataSelectionsClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataSelectionTree  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the SelectionTree class
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataSelectionTree : public BaseDataDirectedTree
{
  String ClassDelimitor;
  int NextNodeNumber;
  bool ReadSet(istream& in, DataObjectClass* objc);
  
public:
  BaseDataSelectionTree();
  BaseDataSelectionTree(const BaseDataSelectionTree& data);

  bool AddCategory(const String& category, const String& superclass);
  bool AddObject(BaseDataObject& data, const String& category);
  ObjectList<String> *GetChoices(const String& category);
  BaseDataObject *GetSelection(const String& node);
  String& FullNameFromList(const ObjectList<String>& path);
  String& FullNameFromCategories(const String& category, const String& node);
  ObjectList<String>& PathListFromFullName(const String& fullname);
  BaseDataObject *GetNextSelection(istream& in, const String& category);
  BaseDataObject *GetNextSelection(const String& category, ObjectList<String>& inputs);
  BaseDataSelections& GetSelections(istream& in, const ObjectList<String>& categories);
  BaseDataSelections& GetSelections(const ObjectList<String>& categories,
				    const ObjectList<String>& choices);

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataSelectionTreeClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataSelectionTreeClass : public DataDirectedTreeClass
{
public:
  DataSelectionTreeClass();
  DataSelectionTreeClass(const DataSelectionTreeClass& data);
  DataSelectionTreeClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
  virtual DataSetOfObjectsClass *PointerToAllowedClasses();

  virtual bool WriteAsLine(ostream&);
  virtual bool WriteAsASCII(ostream&);
  virtual bool WriteAsLatex(ostream&);
};
 




#endif
