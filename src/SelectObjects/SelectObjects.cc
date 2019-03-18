/*  FILE     SelectObjects.cc
**  PACKAGE  SelectObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "SelectObjects" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
**  Version 1.2
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CoreDataObjects.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"

/*S BaseDataSelections
 */ 
/*F BaseDataSelections()  . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSelections::BaseDataSelections()
{
  Identification = SELECTION_SELECTIONS_ID;
  NameTag = SELECTION_SELECTIONS_NAME;
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  CategoryObjectNames.ChangeTitle("Name-Identification Correspondences");
  CategoryObjectNames.ChangeDelimitor("  ");
} 
/*F BaseDataSelections(data)  . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataSelections::BaseDataSelections(const BaseDataSelections& data)
  : BaseDataObject(data),
    Selections(data.Selections),
    CategoryObjectNames(data.CategoryObjectNames)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . .  Read in BaseDataSelections
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataSelections::Read(istream& in, DataObjectClass* objc)
{
  return BaseDataObject::Read(in,objc);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . .  Read in BaseDataSelections
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataSelections::Read(istream& in, DataObjectClass* objc, const String& name)
{
  return BaseDataObject::Read(in,objc,name);
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . .  BaseDataSelections
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataSelections::print(ostream& out) const
{
  out << "BaseDataSelections: \n";
  BaseDataObject::print(out);
  out << "\nCategory Names\n";
  CategoryObjectNames.print(out);
  out << "\nSelections\n";
  Selections.print(out);
  out << "\n---------------------------\n";

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . .  BaseDataSelections
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataSelections::Clone()
{
  BaseDataSelections *obj = new BaseDataSelections;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . .  BaseDataSelections
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataSelections::CopyClone(Identify * obj)
{
  BaseDataSelections *objfull = (BaseDataSelections *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . .  BaseDataSelections
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSelections::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && Selections.EncodeThis(buffer);
  result = result && CategoryObjectNames.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . .  BaseDataSelections
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSelections::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  result = result && Selections.DecodeThis(buffer);
  result = result && CategoryObjectNames.DecodeThis(buffer);

  return result;
}
/*F ans = AddSelectedObject(name,object)  . . . . .  add object to selections
**
**  DESCRIPTION
**    name: The category name of the object
**    object: The selected object
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSelections::AddSelectedObject(const String& name, BaseDataObject& object)
{
  CategoryObjectNames[name] = object.NameTag;
  bool result = Selections.AddObject(&object);
  return result;
}
 
/*F obj = GetSelectedObject(name) . . . . . . . get object from category name
**
**  DESCRIPTION
**    name: The category of the object
**    obj: The object of this category
**
**  REMARKS
**
*/
BaseDataObject* BaseDataSelections::GetSelectedObject(const String& name)
{
  BaseDataObject *c = (BaseDataObject *) Selections.GetObject(name);
  //BaseDataObject *obj = (BaseDataObject *) c->Clone();
  return c;
}


 
/*F corrs = GetNameCategoryCorrespondences()  . . . . . . name-category pairs
**
**  DESCRIPTION
**    corrs: The name-category pairs (as list accessed by category)
**
**    This gives the name-category pairs of the selected items.  It
**    can be used as to reproduce the selection, i.e. just the
**    names are listed without the actual object.
**
**  REMARKS
**
*/
AlternativeNames& BaseDataSelections::GetNameCategoryCorrespondences()
{
  return CategoryObjectNames;
}
/*F names = GetListOfSelections() . . . . . . . . . . . . . . selection names
**
**  DESCRIPTION
**    names: The list of names of all the selections
**
**  REMARKS
**
*/
ObjectList<String> BaseDataSelections::GetListOfSelections()
{
  return Selections.ListOfObjectNames();
}

/*S DataSelectionsClass
 */
/*F DataSelectionsClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataSelectionsClass::DataSelectionsClass()
{
  NameTag = SELECTION_SELECTIONS_NAME;
  Identification = SELECTION_SELECTIONS_ID;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = SELECTION_SELECTIONS_NAME;
} 
/*F DataSelectionsClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataSelectionsClass::DataSelectionsClass(const DataSelectionsClass& data)
  : DataObjectClass(data)
{
} 
 
/*F DataSelectionsClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataSelectionsClass::DataSelectionsClass(const int id, 
                                         const String& name,
                                         const String& descr)
  : DataObjectClass(id,name,descr)

{
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = SELECTION_SELECTIONS_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataSelectionsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataSelectionsClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  out << NameTag << "  ";
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . . . . . DataSelectionsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataSelectionsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataSelectionsClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataSelectionsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataSelectionsClass::CopyClone(Identify * objc)
{
  DataSelectionsClass *objcfull = (DataSelectionsClass *) objc;
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataSelectionsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataSelectionsClass::Clone()
{
  DataSelectionsClass* id = new DataSelectionsClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataSelectionsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSelectionsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataSelectionsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSelectionsClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
  //  result = result && Decode(buffer,-----);

  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataSelectionsClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataSelections();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataSelectionsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataSelectionsClass*& obj)
{
  obj = new DataSelectionsClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataSelections
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataSelections*& obj)
{
  obj = new BaseDataSelections;
  return obj->DecodeThis(buffer);
}

/*S BaseDataSelectionTree
 */ 
/*F BaseDataSelectionTree()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    This sets up the tree with the root node, 'Initial'.
**  REMARKS
**
*/
BaseDataSelectionTree::BaseDataSelectionTree()
  : ClassDelimitor("#"),
    NextNodeNumber(SELECTION_CATEGORY_OFFSET)
{
  Identification = SELECTION_TREE_ID;
  NameTag = SELECTION_TREE_NAME;
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;

  String rootname("Initial");
  
  BaseDataObject *root = new BaseDataObject;
  root->NameTag = rootname;
  root->Identification = NextNodeNumber;
  NextNodeNumber++;

  SetRootNode(rootname);
  BaseDataDirectedTree::AddNode(root);
} 
/*F BaseDataSelectionTree(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataSelectionTree::BaseDataSelectionTree(const BaseDataSelectionTree& data)
  : BaseDataDirectedTree(data),
    ClassDelimitor(data.ClassDelimitor),
    NextNodeNumber(data.NextNodeNumber)
{
} 
/*f in1 = ReadSet(in,objc)  . . . . . . . . . .  The meat of the read routine
**
**  DESCRIPTION
**    in,in1: The input stream
**    objc: The object class
**
**  REMARKS
**
*/
bool BaseDataSelectionTree::ReadSet(istream& in, 
				    DataObjectClass* objc)
{
  unsigned int debuglevel = objc->getDebugLevel();
  if(debuglevel > 1)
    {
      cout << "Begin reading Selection Tree\n";
    }
  bool result = true;
  
  DataSelectionTreeClass *oclass = (DataSelectionTreeClass *) objc;
  DataSetOfObjectsClass *allowedclasses = 
    oclass->PointerToAllowedClasses();
  
  String EndOfList("END");

  StreamObjectInput inobject(in,' ');
  String name = inobject.ReadNext();
  while(name != EndOfList && result)
    {
      String parentcategory = inobject.ReadNext();
      if(debuglevel > 1)
        {
          cout << "Selection Tree Class and Parent Category: '";
          cout << name << "' and '" << parentcategory << "'" << endl;
        }
      if(allowedclasses->IsInList(name))
        {
          String oname = inobject.ReadNext();
          if(debuglevel > 1)
            {
              cout << "Add Algorithm Class as '" << oname << "'" << endl;
            }
          DataObjectClass *c = allowedclasses->GetObjectClass(name);
          if(c != NULL)
            {
              BaseDataObject *o = c->BaseDataObjectExample();
              o->SetType(c->Identification);
              o->Identification = NextNodeNumber;
              NextNodeNumber++;
              o->NameTag = oname;
	      if(debuglevel > 1)
		{
		  cout << "\n-------------------------------------------\n";
		  o->print(cout);
		  cout << "\n-------------------------------------------\n";
		}
              result = result && o->Read(in,c,oname);
	      if(debuglevel > 1)
		{
		  cout << "\n-------------------------------------------\n";
		  o->print(cout);
		  cout << "\n-------------------------------------------\n";
		}
              if(result)
                AddObject(*o,parentcategory);
              else
                cerr << "Error in reading algorithm information\n";
              
            }
          else
            {
              cerr << "Fatal Error in Reading Selection Tree\n";
              result = false;
              allowedclasses->print(cerr);
              cerr << "----------------------- Fatal Error -----------------\n";
            }
        }
      else
        {
          if(debuglevel > 1) 
            {
              cout << "Add as Category: " << name << endl;
            }
          AddCategory(name,parentcategory);
        }
      name = inobject.ReadNext();
    }
  if(debuglevel > 1)
    {
      cout << "End of reading Selection Tree\n";
    }
  
  return true;
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataSelectionTree
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**    The selection tree is read in.  The end of the object tree is
**    signaled with a 'END'.
**
**    A class name and the parent category (the full name) are read in.  
**    If it is a class in the set of allowed classes (in objc),
**    then the object is a leaf node object. Otherwise it is a Category.
**    If it is an object, then the object itself is read in.
**
**  REMARKS
**
*/
bool BaseDataSelectionTree::Read(istream& in, DataObjectClass* objc)
{
  BaseDataObject::Read(in,objc);

  StreamObjectInput inobject(in,' ');
  NameTag = inobject.ReadNext();
  return ReadSet(in,objc);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataSelectionTree
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataSelectionTree::Read(istream& in, DataObjectClass* objc, const String&)
{
  return ReadSet(in,objc);
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataSelectionTree
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataSelectionTree::print(ostream& out) const
{
  BaseDataDirectedTree::print(out);

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataSelectionTree
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataSelectionTree::Clone()
{
  BaseDataSelectionTree *obj = new BaseDataSelectionTree;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataSelectionTree
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataSelectionTree::CopyClone(Identify * obj)
{
  BaseDataSelectionTree *objfull = (BaseDataSelectionTree *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSelectionTree
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSelectionTree::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataDirectedTree::EncodeThis(buffer);
  result = result && Encode(buffer,ClassDelimitor);
  result = result && Encode(buffer,NextNodeNumber);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSelectionTree
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSelectionTree::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataDirectedTree::DecodeThis(buffer);
  result = result && Decode(buffer,ClassDelimitor);
  result = result && Decode(buffer,NextNodeNumber);

  return result;
}
 
 
/*F fullname = FullNameFromList(path) . . . . . . . . create full string name
**
**  DESCRIPTION
**    path: The path of nodes within the selection tree
**    fullname: The full string name corresponding to the path
**
**    The path is converted to a string name.  The string name is the
**    actual name of the node.  The node names within the list
**    are the simple names (without previous node names separated by 
**    delimitors).
**
**  REMARKS
**
*/
String& BaseDataSelectionTree::FullNameFromList(const ObjectList<String>& path)
{
  ObjectList<String> cpy(path);
  String *fullname = new String(cpy.front());
  cpy.pop_front();
  while(cpy.size() > 0)
    {
      fullname->AppendToEnd(ClassDelimitor);
      fullname->AppendToEnd(cpy.front());
      cpy.pop_front();
    }
  return *fullname;
}
 
/*F plist = PathListFromFullName(fullname)  . . node name list from path name
**
**  DESCRIPTION
**    fullname: The single string name with standard delimitors
**    plist: The list of simple node names (name with path info)
**
**    This is the complementary routine to FullNameFromList.  The node 
**    names are the simple names, i.e. not the actual names on the nodes
**    within the selection tree
**
**  REMARKS
**
*/
ObjectList<String>& BaseDataSelectionTree::PathListFromFullName(const String& fullname)
{
  String name(fullname);
  ObjectList<String> *path = new ObjectList<String>;
  path->ChangeTitle(name);
  
  while(name.size() > 1)
    {
      String node;
      name.IsolateNextWord(node,*(ClassDelimitor.c_str()));
      path->AddObject(node);
    }
  return *path;
}
 
/*F name = FullNameFromCategories(category,node)  . . . . . . . get full name
**
**  DESCRIPTION
**    category: The category full path name
**    node: The next node in the path
**    name: The full name
**
**  REMARKS
**
*/
String& BaseDataSelectionTree::FullNameFromCategories(const String& category, const String& node)
{
  String cpynode(node);
  String *name = new String(category);
  name->AppendToEnd(ClassDelimitor);
  name->AppendToEnd(cpynode);
  return *name;
}
/*F obj = GetNextSelection(in,category)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataObject *BaseDataSelectionTree::GetNextSelection(istream& in, const String& category)
{
  StreamObjectInput inobject(in,' ');
  String last(category);
  ObjectList<String> *choices = GetChoices(category);
  ObjectList<String>::iterator iter;
  while(choices->size() >0)
    {
      String choice = inobject.ReadNext();
      String next = FullNameFromCategories(last,choice);
      iter = find(choices->begin(),choices->end(),next);
      if(iter == choices->end())
        {
          cerr << "\nChoice not found: ";
          cerr << choice;
          cerr << " Using Default: ";
          choice = choices->front();
          cerr << choice << endl;
        }
      last = FullNameFromCategories(last,choice);
      delete choices;
      choices = GetChoices(last);
    }
  return GetSelection(last);
}
 
/*F obj = GetNextSelection(category,inputs) 
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataObject *BaseDataSelectionTree::GetNextSelection(const String& category, ObjectList<String>& inputs)
{
  String last(category);
  ObjectList<String> *choices = GetChoices(category);
  ObjectList<String>::iterator iter;
  while(choices->size() >0)
    {
      String choice = inputs.front();
      inputs.pop_front();
      
      String next = FullNameFromCategories(last,choice);
      iter = find(choices->begin(),choices->end(),next);
      if(iter == choices->end())
        {
          cerr << "Choice not found: ";
          cerr << choice;
          cerr << "Using Default: ";
          choice = choices->front();
          cerr << choice;
        }
      last = FullNameFromCategories(last,choice);
      delete choices;
      choices = GetChoices(last);
    }
  return GetSelection(last);
}
 
/*F selections = GetSelections(in,categories)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSelections& BaseDataSelectionTree::GetSelections(istream& in, const ObjectList<String>& categories)
{
  BaseDataSelections *selections = new BaseDataSelections;
  
  for(ObjectList<String>::const_iterator iter =categories.begin();
      iter != categories.end();
      iter++)
    {
      BaseDataObject *obj = GetNextSelection(in,*iter);
      if(obj == NULL)
        cerr << "\nSelected Object Not Found\n";
      
      selections->AddSelectedObject(*iter,*obj);
    }
  return *selections;
}
/*F selections = GetSelections(categories,choices)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSelections& BaseDataSelectionTree::GetSelections(const ObjectList<String>& categories,
                                                         const ObjectList<String>& choices)
{
  ObjectList<String> inputs(choices);
  
  BaseDataSelections *selections = new BaseDataSelections;
  
  for(ObjectList<String>::const_iterator iter =categories.begin();
      iter != categories.end();
      iter++)
    {
      BaseDataObject *obj = GetNextSelection(*iter,inputs);
      if(obj == NULL)
        {
          cerr << "\nSelected Object Not Found: " << *iter << endl;
        }
      selections->AddSelectedObject(*iter,*obj);
    }
  
  return *selections;
}
/*F ans = AddCategory(category,superclass)  . .  add category to a superclass
**
**  DESCRIPTION
**    category: The name of a new category under a superclass (the simple name)
**    superclass: The superclass of the category (the full name)
**    ans: True if successful
**
**    The category is added as a new node and a connection is
**    made between the superclass and the category
**
**  REMARKS
**
*/
bool BaseDataSelectionTree::AddCategory(const String& category, const String& superclass)
{
  bool success = true;
  if(NodeInTree(superclass))
    {
      String fullname(superclass);
      fullname.AppendToEnd(ClassDelimitor);
      String cat(category);
      fullname.AppendToEnd(cat);
      if(!NodeInTree(fullname))
        {
          BaseDataObject *cat = new BaseDataObject;
          cat->NameTag = fullname;
          cat->Identification = NextNodeNumber;
          NextNodeNumber++;
          AddNode(cat);
          AddConnection(superclass,fullname);
        }
      else
        {
          cerr << "Category already exists: ";
          cerr << category;
          cerr << "\n";
          success = false;
        }
    }
  else
    {
      cerr << "SuperClass does not exist: ";
      cerr << superclass;
      cerr << "\n";
      success = false;
    }
  return success;
}
 
/*F ans = AddObject(data,category)  . . . . . . . . add object under category
**
**  DESCRIPTION
**    data: The data object leaf
**    category: The category under which the data object is to go
**    ans: True if successful
**
**    The object is added as a leaf and a connection is made between the
**    data object and the category
**
**  REMARKS
**
*/
bool BaseDataSelectionTree::AddObject(BaseDataObject& data, const String& category)
{
  bool success = true;
  if(NodeInTree(category))
    {
      String fullname(category);
      fullname.AppendToEnd(ClassDelimitor);
      fullname.AppendToEnd(data.NameTag);
      
      if(!(NodeInTree(fullname)))
        {
          BaseDataObject *obj = (BaseDataObject *)data.Clone();
          obj->Identification = NextNodeNumber;
          NextNodeNumber++;
          obj->NameTag = fullname;
          AddNode(obj);
          AddConnection(category,obj->NameTag);
        }
      else
        {
          cerr << "Object Name already exists: ";
          cerr << data.NameTag;
          cerr << "\n";
          success = false;
        }
    }
  else
    {
      cerr << "Category does not exist: ";
      cerr << category;
      cerr << "\n";
      success = false;
    }
  return success;
}
  
/*F choices = GetChoices(category)  . . . .  get list of choices for category
**
**  DESCRIPTION
**    category: The category
**    choices: The list of choices under this category
**
**  REMARKS
**
*/
ObjectList<String> *BaseDataSelectionTree::GetChoices(const String& category)
{
  return BaseDataDirectedTree::GetSons(category);
}
 
/*F obj = GetObject(node) . . . . . . . . . . . .  get the object on the node
**
**  DESCRIPTION
**    node: The node name
**    obj: The corresponding object
**
**  REMARKS
**
*/
BaseDataObject *BaseDataSelectionTree::GetSelection(const String& node)
{
  return BaseDataDirectedTree::GetNode(node);
}
 
/*S DataSelectionTreeClass
 */
/*F DataSelectionTreeClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataSelectionTreeClass::DataSelectionTreeClass()
{
  Identification = SELECTION_TREE_ID;
  NameTag = SELECTION_TREE_NAME;
  SubClass = DIRECTEDTREE_BASE_NAME;
  EncodeDecodeClass = SELECTION_TREE_NAME;
} 
/*F DataSelectionTreeClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataSelectionTreeClass::DataSelectionTreeClass(const DataSelectionTreeClass& data)
  : DataDirectedTreeClass(data)
{
} 
/*F DataSelectionTreeClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataSelectionTreeClass::DataSelectionTreeClass(const int id, 
                                               const String& name,
                                               const String& descr)
  : DataDirectedTreeClass(id,name,descr)
{
  SubClass = DIRECTEDTREE_BASE_NAME;
  EncodeDecodeClass = SELECTION_TREE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataSelectionTreeClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataSelectionTreeClass::print(ostream& out) const
{
  out << "\nBegin:-----------------------";
  out << " DataSelectionTreeClass: " << NameTag;
  out << "-----------------------" << endl;
  
  DataDirectedTreeClass::print(out);
  out << "\nEnd:  -----------------------";
  out << " DataSelectionTreeClass: " << NameTag;
  out << "-----------------------" << endl;
  
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . . . . . DataSelectionTreeClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataSelectionTreeClass, there is no further information.
**
**  REMARKS
**
*/
bool DataSelectionTreeClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataDirectedTreeClass::Read(in,set);
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataSelectionTreeClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataSelectionTreeClass::CopyClone(Identify * objc)
{
  DataSelectionTreeClass *objcfull = (DataSelectionTreeClass *) objc;
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataSelectionTreeClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataSelectionTreeClass::Clone()
{
  DataSelectionTreeClass* id = new DataSelectionTreeClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataSelectionTreeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSelectionTreeClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataDirectedTreeClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataSelectionTreeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSelectionTreeClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataDirectedTreeClass::DecodeThis(buffer);
  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataSelectionTreeClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataSelectionTree();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataSelectionTreeClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataSelectionTreeClass*& obj)
{
  obj = new DataSelectionTreeClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataSelectionTree
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataSelectionTree*& obj)
{
  obj = new BaseDataSelectionTree;
  bool result = obj->DecodeThis(buffer);
  return result;
}
/*F classes = PointerToAllowedClasses()
**
**  DESCRIPTION
**    This in the default case points to itself (this).  
**    It is meant for the case where the set of standard objects
**    is some external (possibly global) object.
**
**  REMARKS
**
*/
DataSetOfObjectsClass *DataSelectionTreeClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}
/*F ans = WriteAsLine(out)  . . . . . . . . . . . . .  DataSelectionTreeClass
**
**  DESCRIPTION
**    out: The output stream
**    ans: true if successful
**
**    This writes out the object one one line
**
**  REMARKS
**
*/
bool DataSelectionTreeClass::WriteAsLine(ostream& out)
{
  return DataDirectedTreeClass::WriteAsLine(out);
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . . DataSelectionTreeClass
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
bool DataSelectionTreeClass::WriteAsASCII(ostream& out)
{
    return DataDirectedTreeClass::WriteAsASCII(out);
}
/*F ans = WriteAsLatex(out) . . . . . . . . . . . . .  DataSelectionTreeClass
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object prepared for latex
**
**  REMARKS
**
*/
bool DataSelectionTreeClass::WriteAsLatex(ostream& out)
{
    return DataDirectedTreeClass::WriteAsLatex(out);
}


/*S Utility
 */
/*F AddSelectionTreeClasses(set)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void AddSelectionTreeClasses(DataSetOfObjectsClass& set)
{
  String seldescr("Selection Class");
  String treedescr("Selection Tree Class");
  
  DataSelectionsClass selclass(SELECTION_SELECTIONS_ID,SELECTION_SELECTIONS_NAME,seldescr);
  DataSelectionTreeClass treeclass(SELECTION_TREE_ID,SELECTION_TREE_NAME,treedescr);
  
  set.AddObjectClass(selclass);
  set.AddObjectClass(treeclass);
}

/*F InitialSetOfSelectionTreeEncodeDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialSetOfSelectionTreeEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataSelectionsClass,BaseDataSelections,SELECTION_SELECTIONS_NAME);
  EncodeDecodeRegisterClass(DataSelectionTreeClass,BaseDataSelectionTree,SELECTION_TREE_NAME);

//  bool (*toproutine)(CommBuffer&,Identify*&);
//
//  bool (*rout1)(CommBuffer&,DataSelectionsClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout1;
//  SingleDecodeRoutine p1(SELECTION_SELECTIONS_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p1.StructureName] = p1;
//  
//  bool (*rout2)(CommBuffer&,DataSelectionTreeClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout2;
//  SingleDecodeRoutine p2(SELECTION_TREE_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p2.StructureName] = p2;
//  
//  String s1("Object.");
//  String s11(SELECTION_SELECTIONS_NAME);
//  s1.AppendToEnd(s11);
//  bool (*rout11)(CommBuffer&,BaseDataSelections*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout11;
//  SingleDecodeRoutine p11(s1,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p11.StructureName] = p11;
//
//  String s2("Object.");
//  String s21(SELECTION_TREE_NAME);
//  s2.AppendToEnd(s21);
//  bool (*rout21)(CommBuffer&,BaseDataSelectionTree*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout21;
//  SingleDecodeRoutine p21(s2,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p21.StructureName] = p21;
}

