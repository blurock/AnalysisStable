/*  FILE     SystemType.hh
**  PACKAGE  System
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "System" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 STURM Project, RISC Linz
*/
 
#ifndef STURM_SYSTEMTYPE_HH
#define STURM_SYSTEMTYPE_HH

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

/*C StreamObjectInput
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class StreamObjectInput
{
  istream& In;
  String current;
  char Delimitor;
  
public:
  StreamObjectInput(istream& in, char delim);
  char SkipUnUsed(char c);
  char OverAllComments(char c);
  char OverComments(char c);
  bool ExpectAsNextCharacter(char ch);
  String& ReadNext();
};
/*C FileName  . . . . . . . . . . . . . . . . . . . . . . The string filename
**
**  DESCRIPTION
**    This class is to create a file name.  Once created
**    the full ASCII filename is in the position:
**    - FullName
**
**   The different constructors are used to create the file name
**
**  REMARKS
**
*/
class FileName
{
  String Directory;
  String Root;
  String Extension;
     
  void FormName()
    {
      FullName.AppendToEnd(Directory);
      String paren = "/";
      FullName.AppendToEnd(paren);
      FullName.AppendToEnd(Root);
      String dot = ".";
      FullName.AppendToEnd(dot);
      FullName.AppendToEnd(Extension);
    }
public:
     
  String FullName;
  FileName(const String& name);
  FileName(const String& root,
	   const String& ext);
  FileName(const String& dir,
	   const String& root,
	   const String& ext);
};
 
/*C DataBaseFileName  . . . . . . . . . . . puts database in proper directory
**
**  DESCRIPTION
**    Uses the FileName class but with the default database
**    directory and extension (CODEBASEROOT_DATABASE)
**
**  REMARKS
**
*/
class DataBaseFileName : public FileName
{
public:
  DataBaseFileName(const String& directory,
		   const String& root);
  DataBaseFileName(const String& root);     
};
/*C OpenInputFile . . . . . . . . . . . . . . . . . . .  from filename pieces
**
**  DESCRIPTION
**     This class, when instantiated, holds the input stream:
**     - Stream
**
**     The files are specified in a similar fashionn as the FileName class
**
**  REMARKS
**
*/
class OpenInputFile : public FileName
{
  bool Success;
public:
  ifstream Stream;
  OpenInputFile(const String& dir,
		const String& root,
		const String& ext);
  OpenInputFile(const String& root,
		const String& ext);
  OpenInputFile(const String& name);
  
  bool IfOpen();
};
 
/*C OpenOutputFile  . . . . . . . . . . . . . . . . . .  from filename pieces
**
**  DESCRIPTION
**     This class, when instantiated, holds the output stream:
**     - Stream
**
**     The files are specified in a similar fashionn as the FileName class
**
**  REMARKS
**
*/
class OpenOutputFile : public FileName
{
  bool Success;
public:
  ofstream Stream;
  OpenOutputFile(const String& name);
  OpenOutputFile(const String& root,
		 const String& ext);
  OpenOutputFile(const String& dir,
		 const String& root,
		 const String& ext);
  
  bool IfOpen();
};
 
/*C OpenInputDataFile . . . . . . . . . . . . . . . .  from standard data dir
**
**  DESCRIPTION
**     This class, when instantiated, holds the input stream:
**     - Stream
**
**     The files are specified in a similar fashion as the FileName class
**
**  REMARKS
**
*/
class OpenInputDataFile : public FileName
{
  bool Success;
public:
  ifstream Stream;
     
  OpenInputDataFile(const String& root,
		    const String& ext);
  OpenInputDataFile(const String& dir,
		    const String& root,
		    const String& ext);     
  
  bool IfOpen();
};
/*C OpenOutputDataFile  . . . . . . . . . . . . . . .  from standard data dir
**
**  DESCRIPTION
**     This class, when instantiated, holds the output stream:
**     - Stream
**
**     The files are specified in a similar fashionn as the FileName class
**     using the default data directory
**
**  REMARKS
**
*/
class OpenOutputDataFile : public FileName
{
  bool Success;
public:
  ofstream Stream;
     
  OpenOutputDataFile(const String& root,
		     const String& ext);
  OpenOutputDataFile(const String& dir,
		     const String& root,
		     const String& ext);
  
  bool IfOpen();
};
     
/*C ReactionSystemBase  . . . . . . . . . . . . . . . . . . Level Zero System
**
**  DESCRIPTION
**     At this level the set of input string are put into a list of strings:
**     - Inputs
**
**     The following virtual operators:
**     - Initialization(): The initialisation routine to be made upon construction
**     - print(out):
**     - Run(): This routine is to start the system
**     - Exit():
**
**  REMARKS
**
*/
class ReactionSystemBase : public Identify
{
public:
  ObjectList<String> Inputs;
  ReactionSystemBase(int argc, char *argv[]);

  virtual void Initialization();
  virtual ostream& print(ostream& out) const;
  virtual int Run();     
  virtual int Exit();
  virtual String GetNextInput();	// whchange added
					     };
 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
int DefaultSystemCommand(ReactionSystemBase *globvars);
int PrintCommandList(ReactionSystemBase *globvars);


/*C SingleCommandBase . . . . . . . . . . . . . . . doco and name for command
**
**  DESCRIPTION
**    The base routine for a command or function.  The main use of this
**    class is to provide basic support functions:
**    - print(out)
**    - EncodeThis(buffer)
**    - Encode(buffer,command)
**    - DecodeThis(buffer)
**    - Decode(buffer,command)
**    - operator==(command)
**    - operator<<(out,command)
**
**    Two fields hold the Name and Documentation, respectively:
**    - Name: The command (used for comparison)
**    - Documentation: One line description (used on printout)
**
**  REMARKS
**
*/
class SingleCommandBase
{
  String Name;
  String Documentation;
public:
  SingleCommandBase();
  SingleCommandBase(const String& name,
		    const String& doco);
     
  ostream& print(ostream& out) const;
  bool operator==(const SingleCommandBase& command);
  bool EncodeThis(CommBuffer& buffer);
  bool DecodeThis(CommBuffer& buffer);
  String& getName();
};
/*C SingleSystemCommand . . . . . . . . . . . . . . . .  system line commands
**
**  DESCRIPTION
**     This is the single system line command.  The command takes
**     a pointer to ReactionSystemBase as input, performs the command
**     returns a integer (zero for success).
**
**  REMARKS
**     Inheirits:
**     - pointer_to_unary_function<ReactionSystemBase*,int> for the function
**     - SingleCommandBase for default routines (Encode, Decode, print, etc.)
**
*/ 
class SingleSystemCommand
: public pointer_to_unary_function<ReactionSystemBase*,int>,
  public SingleCommandBase
{
public:
  SingleSystemCommand();
  SingleSystemCommand(const String& name,
		      const String& doco,
		      int (*routine)(ReactionSystemBase*));
  SingleSystemCommand(const String& name,
		      int (*routine)(ReactionSystemBase*));
  //ostream& print(ostream& out);
};
	       
/*C StringPropertyFunction  . . . . . . . . . . . . read properties on a line
**
**  DESCRIPTION
**    This is a single command holder for properties.  The string property
**    command takes a binary function as input:
**    - PropertyListByName: Where the resulting property will be stored
**    - String: From where the info will be extracted
**
**    The result is a bool, whether it is successful or not
**
**  REMARKS
**
*/
class StringPropertyFunction
: public pointer_to_binary_function<PropertyListByName*,String,int>,
  public SingleCommandBase
{
public:
  StringPropertyFunction();
  StringPropertyFunction(const String& name,
			 const String& doco,
			 int (*routine)(PropertyListByName*,String));
  StringPropertyFunction(const String& name,
			 int (*routine)(PropertyListByName*,String));
};
ostream& operator<<(ostream& out, const SingleCommandBase& command);
/*C ListOfCommandsBase  . . . . . . . . . . . . list of commands or functions
**
**  DESCRIPTION
**    This is a template class, CommandType, for a list of commands or functions.  The CommandType
**    is assumed to have SingleCommandBase as a subclass.
**     
**    
**  REMARKS
**
*/
template <class CommandType>
class ListOfCommandsBase: public SearchableObjectListFull<String,CommandType>
{
  String Name;
public:
  ListOfCommandsBase(const String& name)
    : Name(name)
    {
      String listname = "List of ";
      listname.AppendToEnd(Name);
    }
};
/*C SystemCommands  . . . . . . . . . . . storing and executing line commands
**
**  DESCRIPTION
**    This class is the list of system commands.  It inheirits 
**    the ListOfCommandsBase<SingleSystemCommand>, i.e. the list
**    of command information.  
**
**    The command 'Execute' pops the first string as the command.
**
**  REMARKS
**
*/
class SystemCommands : public ListOfCommandsBase<SingleSystemCommand>
{
public:
  SystemCommands();
  int ExecuteCommand(int argc, char *argv[], 
		     ReactionSystemBase *globvars);
  int ExecuteCommand(ReactionSystemBase *globvars);
};
/*C StringPropertyFunctions . . . . . . . . . . . .  possible line properties
**
**  DESCRIPTION
**    This is a general class for keeping the list of property
**    reading routines.  The FillInProperty function expects
**    a line with:
**    - Name: The property type name (used to look up property)
**    - Rest: The rest of the line is the property (interpreted by routine)
**
**  REMARKS
**
*/
class StringPropertyFunctions
: public ListOfCommandsBase<StringPropertyFunction>
{
public:
  StringPropertyFunctions(const String& name="Properties")
    : ListOfCommandsBase<StringPropertyFunction>(name)
    {
    }
  //     int FillInProperty(PropertyListByName* plist,
			    //			String& line);

  // INTERNAL COMPILER ERROR IF NEXT ROUTINE IS IN SYSTEM.CPP!

       int FillInProperty(PropertyListByName* plist,
			  String& line)
    {
      String proptype;
      String newline = line;
      newline.IsolateNextWord(proptype,' ');
      StringPropertyFunction command = (*this)[proptype];
      return command.operator()(plist, newline);
    }
};
/*C ReactionSystemLevel1  . . . . . . . . . . . . . . . . Level One of System
**
**  DESCRIPTION
**    The level one initialization of the system.  This includes
**    system line commands (Commands):
**    - Commands: The list of commands
**
**    This is pattern virtual functions:
**    - Initialization()
**    - print(out)
**    - Run()
**    - Exit()
**
**  REMARKS
**
*/
class ReactionSystemLevel1 : public ReactionSystemBase
{
  String HomeDirectory;
  String DataRootDirectory;

public:
  SystemCommands Commands;
     
  ReactionSystemLevel1(int argc, char *argv[]);
  ~ReactionSystemLevel1();

  void setHomeDirectory(const String& name);
  String& getHomeDirectory();
  void setDataRootDirectory(const String& name);
  String& getDataRootDirectory();
  
  virtual void Initialization();
  virtual ostream& print(ostream& out) const;
  virtual int Run();
  
  virtual int Run(int argc, char *argv[]);	// whchange added
						     virtual int Exit();

};

/*C errorHandle  . . . . . . . . . . . . . . . . . . error handling
**
**  DESCRIPTION
**
**  REMARKS
**		flag can be FATAL (=1) or RECOVERABLE (=0)
**
*/
class errorHandle
{
public:
  // Constructors
       errorHandle()
    {
    }
  virtual ~errorHandle() {}

  errorHandle(String message, unsigned short flag)
    {
      cerr << "Error code " << flag << ": " << message << endl;
      if (flag == FATAL)
	errorExit(flag);
    }
  virtual void errorExit(unsigned short ret)
    {
      exit(ret);
    }

}; // class errorHandle

#endif
