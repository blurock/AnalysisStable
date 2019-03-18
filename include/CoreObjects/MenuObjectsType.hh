/*  FILE     MenuObjectsType.hh
**  PACKAGE  MenuObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "MenuObjects" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_MENUOBJECTSTYPE_HH
#define CoreObjects_MENUOBJECTSTYPE_HH

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
/*C BaseDataMenuBaseObject  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the MenuBaseObject class definitions
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataMenuBaseObject : public BaseDataObject
{
  String Command;
  String KeyWord;
public:
  BaseDataMenuBaseObject();
  BaseDataMenuBaseObject(const BaseDataMenuBaseObject& data);

  STANDARD_VIRTUAL_METHODS_OBJECT

  String getKeyWord();
  void setKeyWord(String keyword);
  String getCommand();
  void setCommand(String command);
  virtual bool Write(ostream& out, DataObjectClass *objc);
};
/*C DataMenuBaseObjectClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataMenuBaseObjectClass : public DataObjectClass
{
public:
  DataMenuBaseObjectClass();
  DataMenuBaseObjectClass(const DataMenuBaseObjectClass& data);
  DataMenuBaseObjectClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataMenuText  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the MenuText class definitions
**
**  REMARKS
**    Inheirits BaseDataMenuBaseObject
*/
class BaseDataMenuText : public BaseDataMenuBaseObject
{
  String Text;
public:
  BaseDataMenuText();
  BaseDataMenuText(const BaseDataMenuText& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
  String getText();
  void setText(String text);
  virtual bool Write(ostream& out, DataObjectClass *objc);
  };
/*C DataMenuTextClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataMenuBaseObjectClass
*/
class DataMenuTextClass : public DataMenuBaseObjectClass
{
public:
  DataMenuTextClass();
  DataMenuTextClass(const DataMenuTextClass& data);
  DataMenuTextClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataMenuTextChoice  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the MenuTextChoice class definitions
**
**  REMARKS
**    Inheirits BaseDataMenuBaseObject
*/
class BaseDataMenuTextChoice : public BaseDataMenuBaseObject
{
  ObjectList<String> Choice;
public:
  BaseDataMenuTextChoice();
  BaseDataMenuTextChoice(const BaseDataMenuTextChoice& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
  ObjectList<String>& getChoice();
  void setChoice(ObjectList<String>& choice);
  void addChoice(String& choice);
  virtual bool Write(ostream& out, DataObjectClass *objc);
};
/*C DataMenuTextChoiceClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataMenuBaseObjectClass
*/
class DataMenuTextChoiceClass : public DataMenuBaseObjectClass
{
public:
  DataMenuTextChoiceClass();
  DataMenuTextChoiceClass(const DataMenuTextChoiceClass& data);
  DataMenuTextChoiceClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataMenuComposite  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the MenuComposite class definitions
**
**  REMARKS
**    Inheirits BaseDataMenuBaseObject
*/
class BaseDataMenuComposite : public BaseDataMenuBaseObject
{
  BaseDataMenuBaseObject *Object;

  String Gridx,Gridy;
  String Gridwidth,Gridheight;
  unsigned int Weightx,Weighty;
  String Anchor,Fill;

  
public:
  BaseDataMenuComposite();
  BaseDataMenuComposite(const BaseDataMenuComposite& data);

  STANDARD_VIRTUAL_METHODS_OBJECT

  void setGrid(String& gridx, String& gridy,
	       String& gridwidth, String& gridheight);
  void setWeight(unsigned int weightx, 
		 unsigned int weighty);
  void setFill(String& fill);
  void setAnchor(String& anchor);
  void printParameters(ostream& out) const;
  void setObject(BaseDataMenuBaseObject *obj);
  BaseDataMenuBaseObject *getObject();
  virtual bool Write(ostream& out, DataObjectClass *objc);
};
/*C DataMenuCompositeClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataMenuBaseObjectClass
*/
class DataMenuCompositeClass : public DataMenuBaseObjectClass
{
public:
  DataMenuCompositeClass();
  DataMenuCompositeClass(const DataMenuCompositeClass& data);
  DataMenuCompositeClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataMenuComposition  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the MenuComposition class definitions
**
**  REMARKS
**    Inheirits BaseDataMenuBaseObject
*/
class BaseDataMenuComposition : public BaseDataMenuBaseObject
{
  BaseDataSetOfObjects Composites;
public:
  BaseDataMenuComposition();
  BaseDataMenuComposition(const BaseDataMenuComposition& data);
  
  bool AddComposite(BaseDataMenuComposite& composite);
  virtual bool Write(ostream& out, DataObjectClass *objc);

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataMenuCompositionClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataMenuBaseObjectClass
*/
class DataMenuCompositionClass : public DataMenuBaseObjectClass
{
public:
  DataMenuCompositionClass();
  DataMenuCompositionClass(const DataMenuCompositionClass& data);
  DataMenuCompositionClass(const int id, 
		    const String& name,
		    const String& descr);

  DataSetOfObjectsClass *getStandard();

  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataMenuWindow  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the MenuWindow class definitions
**
**  REMARKS
**    Inheirits BaseDataMenuBaseObject
*/
class BaseDataMenuWindow : public BaseDataMenuBaseObject
{
  BaseDataMenuBaseObject *MenuObject;
public:
  BaseDataMenuWindow();
  BaseDataMenuWindow(const BaseDataMenuWindow& data);

  STANDARD_VIRTUAL_METHODS_OBJECT

  BaseDataMenuBaseObject *getMenuObject();
  void setMenuObject(BaseDataMenuBaseObject *obj);
  virtual bool Write(ostream& out, DataObjectClass *objc);
};
/*C DataMenuWindowClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataMenuBaseObjectClass
*/
class DataMenuWindowClass : public DataMenuBaseObjectClass
{
public:
  DataMenuWindowClass();
  DataMenuWindowClass(const DataMenuWindowClass& data);
  DataMenuWindowClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataMenuCoreObject  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the MenuCoreObject class definitions
**
**  REMARK
**    Inheirits BaseDataMenuBaseObject
*/
class BaseDataMenuCoreObject : public BaseDataMenuBaseObject
{
  BaseDataObject *Object;
  bool ClassObject;
public:
  BaseDataMenuCoreObject();
  BaseDataMenuCoreObject(const BaseDataMenuCoreObject& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
  void setAsClassObject(DataObjectClass *obj);
  void setAsAttributeObject(BaseDataObject *obj);
  BaseDataObject *getObject();
  virtual bool Write(ostream& out, DataObjectClass *objc);  
};
/*C DataMenuCoreObjectClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataMenuBaseObjectClass
*/
class DataMenuCoreObjectClass : public DataMenuBaseObjectClass
{
  BaseDataKeyWords Registry;
public:
  DataMenuCoreObjectClass();
  DataMenuCoreObjectClass(const DataMenuCoreObjectClass& data);
  DataMenuCoreObjectClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
  DataSetOfObjectsClass *PointerToAllowedClasses();
  bool registerClass(String& classname);
  bool isInList(String& classname);
};
/*C BaseDataMenuDirectedTreeObject  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the MenuDirectedTreeObject class definitions
**
**  REMARKS
**    Inheirits BaseDataMenuBaseObject
*/
class BaseDataMenuDirectedTreeObject : public BaseDataMenuBaseObject
{
  String RootNode;
  ObjectList<String> Nodes;
  SymmetricPairList<String> Bonds;
public:
  BaseDataMenuDirectedTreeObject();
  BaseDataMenuDirectedTreeObject(const BaseDataMenuDirectedTreeObject& data);

  ObjectList<String>& getNodes();
  SymmetricPairList<String>& getBonds();
  void AddNode(const String& node);
  void AddBond(const String& parent, const String& son);
  virtual bool Write(ostream& out, DataObjectClass *objc);
  void SetRootNode(String& node);
  String GetRootNode();
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataMenuDirectedTreeObjectClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataMenuBaseObjectClass
*/
class DataMenuDirectedTreeObjectClass : public DataMenuBaseObjectClass
{
public:
  DataMenuDirectedTreeObjectClass();
  DataMenuDirectedTreeObjectClass(const DataMenuDirectedTreeObjectClass& data);
  DataMenuDirectedTreeObjectClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
class InstanceSystemMenu : public InstanceSystemSave
{
  String SysMainCommand;
  String SysRoot;
  unsigned int SysLevel;

  String SysMenuCommand;

public:
  InstanceSystemMenu(int argc, char *argv[])
    : InstanceSystemSave(argc,argv)
    {
	setSystemCommandConstants();
    }
  void setSystemCommandConstants()
    {
	if(Inputs.size() < 1)
	    {
		cerr << "Expected at least a menu command script" << endl;
	    }
	else
	    {
		SysMenuCommand = Inputs.front();;      
		Inputs.pop_front();
	    }
    }

  void setSysMenuCommand(String& command)
    {
      SysMenuCommand = command;
    }
  String& getSysMenuCommand()
    {
      return SysMenuCommand;
    }
  void setSysLevel(unsigned int level)
    {
      SysLevel = level;
    }
  unsigned int getSysLevel()
    {
      return SysLevel;
    }
  void setSysRoot(String& root)
    {
      SysRoot = root;
    }
  String& getSysRoot()
    {
      return SysRoot;
    }
  void setSysMainCommand(String& command)
    {
      SysMainCommand = command;
    }
  String& getSysMainCommand()
    {
      return SysMainCommand;
    }

  void EncodeDecodeObjectsSetUp()
    {
      InstanceSystemSave::EncodeDecodeObjectsSetUp();
    }
  void StandardObjectsSetUp()
    {
      InstanceSystemSave::StandardObjectsSetUp();
    }
  void CommandSetUp();  
  virtual void BaseDataObjectOut(String& ptype, 
				 BaseDataObject *obj, 
				 ostream& out);
  virtual void PrintListOfNames(String& ptype, String& prefix,
			ostream& out,
			ObjectList<String>& names);
};



#endif
