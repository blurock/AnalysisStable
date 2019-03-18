/*  FILE     
**  PACKAGE     REACTION    
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    
**
**  REFERENCES
**
**  COPYRIGHT (C) 1995  REACTION Project / Edward S. Blurock 
*/

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#define TEMPLATE_INSTANTIATION
#include "System.hh"

/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
SearchableObjectListSimple<String,SingleDecodeRoutine> *SetOfEncodeDecodeRoutines;
#ifdef _unix
template ostream& operator<<(ostream&, const ListOfCommandsBase<SingleSystemCommand>&);
#endif
/*S StreamObjectInput
 */
 /*F StreamObjectInput(in,delim) . . . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    in: The input stream
**    delim: The delimitor character
**
**  REMARKS
**
*/
StreamObjectInput::StreamObjectInput(istream& in, char delim)
  : In(in),
    Delimitor(delim)
{
}
 
/*F ch = SkipUnUsed(c)  . . . . . . . .  skip over initial blanks and returns
**
**  DESCRIPTION
**    c: The next character
**    ch: The next character that is not a delimitor or return
**
**  REMARKS
**
*/
char StreamObjectInput::SkipUnUsed(char c)
{
  if(c == Delimitor || c == '\n' || c == '\r') {
      while(c == Delimitor || c == '\n' || c == '\r')
	if(In.good()) {
	  In.get(c);
	} else {
	  c = 0;
	}
    }
  return c;
}
 
/*F ch = OverAllComments(c) . . . . . . . . . . . . .  skip over all comments
**
**  DESCRIPTION
**    c: The next character
**    ch: The character after all comments
**
**  REMARKS
**
*/
char StreamObjectInput::OverAllComments(char c)
{
  c = SkipUnUsed(c);
  while(c == '%')
    {
      c = OverComments(c);
      c = SkipUnUsed(c);
    }
  return c;
}
 
/*F ch = OverComments(c)  . . . . . . . . . .  skip over one comment if there
**
**  DESCRIPTION
**    c: The next character
**    ch: The next character after the comment
**
**  REMARKS
**
*/
char StreamObjectInput::OverComments(char c)
{
  if(c == '%')
    {
      while(c != '\n' && c != '\r')
        In.get(c);
      In.get(c);
    }
  if(c == '\r') {
    In.get(c);
    if(c != '\n') {
      In.putback(c);
    }
  }
  return c;
}
 
/*F ans = ExpectAsNextCharacter(ch) . . . . . . . . . .  is next character ch
**
**  DESCRIPTION
**    ch: character to expect
**    ans: true if next character is ch
**
**  REMARKS
**
*/
bool StreamObjectInput::ExpectAsNextCharacter(char ch)
{
  bool result = true;
  char c;
  In.get(c);
      
  c = OverAllComments(c);
      
  if(ch != c)
    result = false;
  return result;
}
 
/*F str = ReadNext()  . . . . . . . . . . . . . . . . . . read next character
**
**  DESCRIPTION
**    str: The next string
**
**  REMARKS
**
*/
String& StreamObjectInput::ReadNext()
{
  current.erase(current.begin(),current.end());
  char c;
  In.get(c);
  c = OverAllComments(c);
  while(c != Delimitor && c != '\n' && c != '\r')
    {
      current.insert(current.end(),c);
      c = Delimitor;
      In.get(c);
    }
  if(c == '\r') {
    In.get(c);
    if(c != '\n') {
      In.putback(c);
    }
  }
  current.insert(current.end(),'\0');
  String *str = new String(current);
  return *str;
}

/*S Constructors
*/ 
/*F SingleCommandBase() . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
SingleCommandBase::SingleCommandBase()
{
} 
/*F SingleCommandBase(name,doco)  . . . . . . . . . . . . . .  initialization
**
**  DESCRIPTION
**    name: The name of the function
**    doco: The documentation ("No Documentation" by default)
**
**  REMARKS
**
*/
SingleCommandBase::SingleCommandBase(const String& name,
                                     const String& doco="No Documentation")
  : Name(name),
    Documentation(doco)
{
}
/*F SingleSystemCommand() . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
SingleSystemCommand::SingleSystemCommand() 
  : pointer_to_unary_function<ReactionSystemBase*,int>(0),
    SingleCommandBase()
{
}
     
 
/*F SingleSystemCommand(name,doco,routine)  . . . . . . . . . . .  initialize
**
**  DESCRIPTION
**    name: The name of the system command
**    doco: Associated Documentation
**    routine: The routine
**
**  REMARKS
**
*/
SingleSystemCommand::SingleSystemCommand(const String& name,
                                         const String& doco,
                                         int (*routine)(ReactionSystemBase*))
  : pointer_to_unary_function<ReactionSystemBase*,int>(routine),
    SingleCommandBase(name,doco)
{
}
 
/*F SingleSystemCommand(name,routine) . . . . . . . . . . . . .  default doco
**
**  DESCRIPTION
**    name: The name of the system command
**    routine: The routine
**    
**  REMARKS
**
*/
SingleSystemCommand::SingleSystemCommand(const String& name,
                                         int (*routine)(ReactionSystemBase*))
  : pointer_to_unary_function<ReactionSystemBase*,int>(routine),
    SingleCommandBase(name)
{
}
 
/*F StringPropertyFunction()  . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
StringPropertyFunction::StringPropertyFunction()
  : pointer_to_binary_function<PropertyListByName*,String,int>(0),
    SingleCommandBase()
{
}
 
/*F StringPropertyFunction(name,doco,routine) . . . . . . . . . .  initialize
**
**  DESCRIPTION
**    name: The name of the property
**    doco: A short documentary string
**    routine: The acutal routine
**
**  REMARKS
**
*/
StringPropertyFunction::StringPropertyFunction(const String& name,
                                               const String& doco,
                                               int (*routine)(PropertyListByName*,String))
  : pointer_to_binary_function<PropertyListByName*,String,int>(routine),
    SingleCommandBase(name,doco)
{
}
 
/*F StringPropertyFunction(name,routine)  . . . . . . . . . . . .  initialize
**
**  DESCRIPTION
**    name: The name of the property
**    routine: The acutal routine
**    
**  REMARKS
**
*/
StringPropertyFunction::StringPropertyFunction(const String& name,
                                               int (*routine)(PropertyListByName*,String))
  : pointer_to_binary_function<PropertyListByName*,String,int>(routine),
    SingleCommandBase(name)
{
}
/*S Utility
*/
/*F SystemCommands()  . . . . . . . . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    Two commands are given as default:
**    - Default:
**    - CommandList: 
**
**  REMARKS
**
*/
SystemCommands::SystemCommands() 
  : ListOfCommandsBase<SingleSystemCommand>("System Commands")
{
  SingleSystemCommand command("Default",&DefaultSystemCommand);
  AddObject(command.getName(),command);
  SingleSystemCommand clist("CommandList",&PrintCommandList);
  AddObject(clist.getName(),clist);
}
/*F ans = ExecuteCommand(argc,argv,globvar) . . . . . .  execute line command
**
**  DESCRIPTION
**    argc: The number of arguments
**    argv: The original arguments
**    globvar: The system class with the commands
**
**  REMARKS
**
*/
int SystemCommands::ExecuteCommand(int argc, char *argv[], 
                                   ReactionSystemBase *globvars)
{
 String name;
  if(argc != 0)
    // whchange   name = *argv[0];
  name = argv[0];
  else
    name = "Reaction";
  return ExecuteCommand(globvars);
}
/*F ans = ExecuteCommand(globvar) . . . . . .  execute line command
**
**  DESCRIPTION
**    globvar: The system class with the commands
**
**  REMARKS
**
*/
int SystemCommands::ExecuteCommand(ReactionSystemBase *globvars)
{
  String strcommand;
  if(globvars->Inputs.size() == 0)
    strcommand = "Default";
  else
    {
      strcommand = globvars->GetNextInput();
    }
  SingleSystemCommand command = (*this)[strcommand];
  int ans;
  
  if(!command.getName().IsEmpty())
    {
      ans = command.operator()(globvars);
    }
  else
    {
      cerr << "Command not found: '" << strcommand << "' " << endl;
      ans = SYSTEM_ERROR_RETURN;
    }
  
  return ans;
}
/*F ans = operator==(command) . . . . . . . . . . . . . . . SingleCommandBase
**
**  DESCRIPTION
**    command: To be compared
**    ans: true if Names are the same
**
**  REMARKS
**
*/
bool SingleCommandBase::operator==(const SingleCommandBase& command)
{
  return Name == command.Name;
}
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
String& GetEnvironmentVariable(const String& name)
{
  String *value;
  char *v = getenv(name.c_str());
  if(v == NULL)
    {
      value = new String("");
    }
  else
    {
      value = new String(v);
    }
  return *value;
}
 
/*F dir = ReadHomeDirectory()
**
**  DESCRIPTION
**    dir: The home directory of the current user
**
**  REMARKS
**
*/
String& ReadHomeDirectory()
{
  String homename(HOME_NAME);
  String *value;
  String v = GetEnvironmentVariable(homename);
  if(v.IsEmpty())
    {
      value = new String(CODEBASEROOT);
      //cerr << "Default Home Directory: " << *value << endl;
    }
  else
    {
      value = new String(v);
      //cerr << "Home Directory: " << *value << endl;
    }
  
  return *value;
}
/*F dir = ReadDataDirectory()
**
**  DESCRIPTION
**    dir: The data directory root
**
**  REMARKS
**
*/
String& ReadDataDirectory()
{
  String homename(DATAHOME_NAME);
  String *value;
  String v = GetEnvironmentVariable(homename);
  if(v.IsEmpty())
    {
      value = new String(CODEBASEROOT_DATA);
      //cerr << "Default Data Directory: " << *value << endl;
    }
  else
    {
      value = new String(v);
      //cerr << "Data Directory: " << *value << endl;
    }
  
  return *value;
}
/*F name = getName()  . . . . . . . . . . . . . . . . . . .  get command name
**
**  DESCRIPTION
**    name: The command name
**
**  REMARKS
**
*/
String& SingleCommandBase::getName()
{
  return Name;
}

/*S IO
*/ 
/*F out = print(out)  . . . . . . . . . . . . . . . . . . . SingleCommandBase
**
**  DESCRIPTION
**    out: The output stream
**
**  REMARKS
**
*/
ostream& SingleCommandBase::print(ostream& out) const
{
  out << Name;
  out << ":  ";
  out << Documentation;
  return out;
}
/*F out = operator<<(out,sys) . . . . . . . . . . . . . .  ReactionSystemBase
**
**  DESCRIPTION
**    out: The output stream
**    sys: The System structure
**
**  REMARKS
**
*/
ostream& operator<<(ostream& out, const ReactionSystemBase& sys)
{
  return sys.print(out);
}
/*F out = operator<<(out,sys) . . . . . . . . . . . . . .  SingleSystemCommand
**
**  DESCRIPTION
**    out: The output stream
**    sys: The SingleSystemCommand structure
**
**  REMARKS
**
*/
ostream& operator<<(ostream& out, const SingleSystemCommand& sys)
{
  return sys.print(out);
}
/*F out = operator<<(out,sys) . . . . . . . . . . . . . .  StringPropertyFunction
**
**  DESCRIPTION
**    out: The output stream
**    sys: The StringPropertyFunction structure
**
**  REMARKS
**
*/
ostream& operator<<(ostream& out, const StringPropertyFunction& sys)
{
  return sys.print(out);
}
/*F out = operator<<(out,sys) . . . . . . . . . . . . . .  SystemCommands
**
**  DESCRIPTION
**    out: The output stream
**    sys: The SystemCommands structure
**
**  REMARKS
**
*/
ostream& operator<<(ostream& out, const SystemCommands& sys)
{
  return sys.print(out);
}

/*S EncodeDecode
*/
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . SingleCommandBase
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool SingleCommandBase::EncodeThis(CommBuffer& buffer)
{
  bool result = Encode(buffer,Name);
  result = result && Encode(buffer,Documentation);
  return result;
}         
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . SingleCommandBase
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**    
**  REMARKS
**
*/
bool SingleCommandBase::DecodeThis(CommBuffer& buffer)
{
  bool result = Decode(buffer,Name);
  result = result && Decode(buffer,Documentation);
  return result;
}         
/*F ans = Encode(buffer,command)  . . . . . . . . . . . . . SingleCommandBase
**
**  DESCRIPTION
**    buffer: the buffer
**    command: The command base
**    ans: true if successful
**
**  REMARKS
**
*/
bool Encode(CommBuffer& buffer, SingleCommandBase& command)
{
  return command.EncodeThis(buffer);
}
/*F ans = Decode(buffer,command)  . . . . . . . . . . . . . SingleCommandBase
**
**  DESCRIPTION
**    buffer: the buffer
**    command: The command base
**    ans: true if successful
**
**  REMARKS
**
*/
bool Decode(CommBuffer& buffer, SingleCommandBase& command)
{
  return command.DecodeThis(buffer);
}

/*S ReactionSystemLevel1
*/
 
/*F ReactionSystemLevel1(argc,argv) . . . . . . . . . . . . initialize system
**
**  DESCRIPTION
**    argc: The number of arguments
**    argv: The arguments of the command line
**
**  REMARKS
**
*/
ReactionSystemLevel1::ReactionSystemLevel1(int argc, char *argv[])
  : ReactionSystemBase(argc,argv),
    HomeDirectory("."),
    DataRootDirectory("."),
    Commands()
{
  Initialization();
}
 
/*F ~ReactionSystemLevel1() . . . . . . . . . . . . . . . . . . .  destructor
**
**  DESCRIPTION
**    Calls the Exit routine and deletes the set of encode-decode routines
**
**  REMARKS
**
*/
ReactionSystemLevel1:: ~ReactionSystemLevel1()
{
  Exit();
  if(SetOfEncodeDecodeRoutines != 0)
    delete SetOfEncodeDecodeRoutines;
  SetOfEncodeDecodeRoutines = 0;
}
     
 
/*F Initialization()  . . . . . . . . . . . . . . . additional initialization
**
**  DESCRIPTION
**    The SetOfEncodeDecodeRoutines is set up and the standard 
**    routines needed for the basic types are included
**
**  REMARKS
**
*/
void ReactionSystemLevel1::Initialization()
{
  ReactionSystemBase::Initialization();
  if(SetOfEncodeDecodeRoutines == 0)
    {
      SetOfEncodeDecodeRoutines =
        new SearchableObjectListSimple<String,SingleDecodeRoutine>;
    }
  setHomeDirectory(ReadHomeDirectory());
  setDataRootDirectory(ReadDataDirectory());
  
  InitialSetOfMixedEncodeDecodeRoutines(SetOfEncodeDecodeRoutines);
}
 
/*F out = print(out)  . . . . . . . . . . . . . . . . .  ReactionSystemLevel1
**
**  DESCRIPTION
**    out: The output buffer
**
**  REMARKS
**
*/
ostream& ReactionSystemLevel1::print(ostream& out) const
{
  ReactionSystemBase::print(out);
  return out;
}
            
 
/*F ans = Run() . . . . . . . . . . . . . . . . . .  The main runtime routine
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int ReactionSystemLevel1::Run()
{
  return 0;
}

/*F ans = Run(argc, argv) . . . . . . . . . . . . . .The main runtime routine
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int ReactionSystemLevel1::Run(int argc, char *argv[])
{
  while ((*this).Inputs.size() > 0)
    Commands.ExecuteCommand(argc, argv, this);
  return 0;
}
/*F Exit()  . . . . . . . . . . . . . The exit routine (called by destructor)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int ReactionSystemLevel1::Exit()
{
  return 0;
}




        
 
/*F homedir = getHomeDirectory()  . . . . . . . . . . . . . . get string name
**
**  DESCRIPTION
**    homedir: The name of the home directory
**
**  REMARKS
**
*/
String& ReactionSystemLevel1::getHomeDirectory()
{
  return HomeDirectory;
}
/*F datadir = getDataRootDirectory()  . . . . . . . . . . . . get string name
**
**  DESCRIPTION
**    datadir: The name of the home directory
**
**  REMARKS
**
*/
String& ReactionSystemLevel1::getDataRootDirectory()
{
  return DataRootDirectory;
}
/*F homedir = setHomeDirectory()  . . . . . . . . . . . .  set to string name
**
**  DESCRIPTION
**    homedir: The name of the home directory
**
**  REMARKS
**
*/
void ReactionSystemLevel1::setHomeDirectory(const String& name)
{
  HomeDirectory = name;
}
/*F datadir = getDataRootDirectory()  . . . . . . . . . .  set to string name
**
**  DESCRIPTION
**    datadir: The name of the home directory
**
**  REMARKS
**
*/
void ReactionSystemLevel1::setDataRootDirectory(const String& name)
{
  DataRootDirectory = name;
}

/*S FileName
*/
 
/*F FileName(dir,root,ext)  . . . . . . . . . . . . . . . . .  form file name
**
**  DESCRIPTION
**    dir: The directory
**    root: The root name
**    ext: The extension
**
**  REMARKS
**
*/
FileName::FileName(const String& dir,
                   const String& root,
                   const String& ext)
  : Directory(dir),
    Root(root),
    Extension(ext)
{
  FormName();
}
 
/*F FileName(root,ext)  . . . . . . . . . . . . . . . . use current directory
**
**  DESCRIPTION
**    root: The root name
**    ext: The extension
**    
**  REMARKS
**
*/
FileName::FileName(const String& root,
                   const String& ext)
  : Directory("."),
    Root(root),
    Extension(ext)
{
  FormName();
}

/*F FileName(name)  . . . . . . . . . . . . . . . . . . . . . full name given
**
**  DESCRIPTION
**    name: The name of the file
**    
**  REMARKS
**
*/
FileName::FileName(const String& name)
  : FullName(name)
{
}



 
/*F DataBaseFileName(directory,root)  . . . . . . .  set up database filename
**
**  DESCRIPTION
**    directory: put in given directory
**    root: The root name
**
**  REMARKS
**
*/
DataBaseFileName::DataBaseFileName(const String& directory,
                                   const String& root)
  : FileName(directory,root,"dbf")             
{
}
 
/*F DataBaseFileName(root)  . . . . . . . . . . . .  set up database filename
**
**  DESCRIPTION
**    root: The rootname of the database
**
**    The default directory and extension are used
**
**  REMARKS
**
*/
DataBaseFileName::DataBaseFileName(const String& root)
  : FileName(CODEBASEROOT_DATABASE,root,"dbf")         
{
}

 
/*F OpenInputFile(dir,root,ext) . . . . . . . . . . . . . . . . . . open file
**
**  DESCRIPTION
**    dir: The directory
**    root: The root name
**    ext: The extension
**    
**  REMARKS
**
*/
OpenInputFile::OpenInputFile(const String& dir,
                             const String& root,
                             const String& ext) 
  : FileName(dir,root,ext),
    Stream(FullName.c_str())
{
  if (!Stream.good()) {
    cerr << "Error: Cannot open file: " << FullName << endl;
    Success = false;
  }
  else {
    Success = true;
  }
}

  
/*F OpenInputFile(root,ext) . . . . . . . . . . . . . . . . . open input file
**
**  DESCRIPTION
**    root: The root name
**    ext: The extension
**    
**  REMARKS
**
*/
OpenInputFile::OpenInputFile(const String& root,
                             const String& ext) 
  : FileName(root,ext),
    Stream(FullName.c_str())
{
  if (!Stream.good()) {
    cerr << "Error: Cannot open file: " << FullName << endl;
    Success = false;
  }
  else
    Success = true;
}
/*F OpenInputFile(name) . . . . . . . . . . . . . . . . . . . open input file
**
**  DESCRIPTION
**    name: The input filename
**
**  REMARKS
**
*/
OpenInputFile::OpenInputFile(const String& name)
  : FileName(name),
    Stream(FullName.c_str())
{
  if (!Stream.good()) {
    cerr << "Error: Cannot open file: " << FullName << endl;
    Success = false;
  }
  else{
    Success = true;
  }
}
/*F IfOpen() 
**
**  DESCRIPTION
**    returns Success, i.e. if the file exists
**
**  REMARKS
**
*/
bool OpenInputFile::IfOpen()
{
  return Success;  
}

 
/*F OpenOutputFile(dir,root,ext)  . . . . . . . . . . . . .  open output file
**
**  DESCRIPTION
**    dir: The directory
**    root: The root name
**    ext: The extension
**    
**  REMARKS
**
*/
OpenOutputFile::OpenOutputFile(const String& dir,
                               const String& root,
                               const String& ext) 
  : FileName(dir,root,ext),
    Stream(FullName.c_str())
{
  if (!Stream.good()) {
    cerr << "Error: Cannot open file: " << FullName << endl;
    Success = false;
  }
  else
    Success = true;
}
 
/*F OpenOutputFile(root,ext)  . . . . . . . . . . . . . . .  open output file
**
**  DESCRIPTION
**    root: The root name
**    ext: The extension
**    
**  REMARKS
**
*/
OpenOutputFile::OpenOutputFile(const String& root,
                               const String& ext) 
  : FileName(root,ext),
    Stream(FullName.c_str())
{
  if (!Stream.good()) {
    cerr << "Error: Cannot open file: " << FullName << endl;
    Success = false;
  }
  else
    Success = true;
}
 
/*F OpenOutputFile(name)  . . . . . . . . . . . . . . . . .  open output file
**
**  DESCRIPTION
**    name: the full name
**
**  REMARKS
**
*/
OpenOutputFile::OpenOutputFile(const String& name)
  : FileName(name),
    Stream(name.c_str())
{
  if (!Stream.good()) {
    cerr << "Error: Cannot open file: " << FullName << endl;
    Success = false;
  }
  else
    Success = true;
}
/*F IfOpen() 
**
**  DESCRIPTION
**    returns Success, i.e. if the file exists
**
**  REMARKS
**
*/
bool OpenOutputFile::IfOpen()
{
  return Success;  
}

 
/*F OpenInputDataFile(root,ext) . . . . . . . . . . . . . . .  open data file
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
OpenInputDataFile::OpenInputDataFile(const String& root,
                                     const String& ext) 
  : FileName(CODEBASEROOT_DATA,root,ext),
    Stream(FullName.c_str())
{
  if (!Stream.good()) {
    cerr << "Error: Cannot open file: " << FullName << endl;
    Success = false;
  }
  else
    Success = true;
}

/*F OpenInputDataFile(root,ext) . . . . . . . . . . . . . . .  open data file
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
OpenInputDataFile::OpenInputDataFile(const String& dir,
                                     const String& root,
                                     const String& ext) 
  : FileName(dir,root,ext),
    Stream(FullName.c_str())
{
  if (!Stream.good()) {
    cerr << "Error: Cannot open file: " << FullName << endl;
    Success = false;
  }
  else
    Success = true;
}
/*F IfOpen() 
**
**  DESCRIPTION
**    returns Success, i.e. if the file exists
**
**  REMARKS
**
*/
bool OpenInputDataFile::IfOpen()
{
  return Success;  
}

 
/*F OpenOutputDataFile(root,ext)  . . . . . . . . . . . . . .  open data file
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
OpenOutputDataFile::OpenOutputDataFile(const String& root,
                                       const String& ext) 
  : FileName(CODEBASEROOT_DATA,root,ext),
    Stream(FullName.c_str())
{
  if (!Stream.good()) {
    cerr << "Error: Cannot open file: " << FullName << endl;
    Success = false;
  }
  else
    Success = true;
}

/*F OpenOutputDataFile(root,ext)  . . . . . . . . . . . . . .  open data file
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
OpenOutputDataFile::OpenOutputDataFile(const String& dir,
                                       const String& root,
                                       const String& ext) 
  : FileName(dir,root,ext),
    Stream(FullName.c_str())
{
  if (!Stream.good()) {
    cerr << "Error: Cannot open file: " << FullName << endl;
    Success = false;
  }
  else
    Success = true;
}
/*F IfOpen() 
**
**  DESCRIPTION
**    returns Success, i.e. if the file exists
**
**  REMARKS
**
*/
bool OpenOutputDataFile::IfOpen()
{
  return Success;  
}
/*S ReactionSystemBase
*/
 
/*F ReactionSystemBase(argc,argv) . . . . . . . . . . . . . . . .  initialize
**
**  DESCRIPTION
**    argc: The number of command arguments
**    argv: The command arguments
**
**    The initialization converts the strings in argv to an
**    ObjectList<String> structure in Inputs
**
**  REMARKS
**
*/
ReactionSystemBase::ReactionSystemBase(int argc, char *argv[])
  : Inputs()
{
  for(int i=1;i<argc;i++)
    {
      String *input = new String(argv[i]);
      Inputs.AddObject(*input);
    }
     
  cerr << "The Inputs are: " << Inputs << endl;
     
  Initialization();
}
 
/*F Initialization()  . . . . . . . . . . . . . . . . . . . .  initialization
**
**  DESCRIPTION
**    Sets up name of job (from first argument, if there is one)
**
**  REMARKS
**
*/
void ReactionSystemBase::Initialization()
{
  Identification = 0;
  if(Inputs.size() >= 1)
    NameTag = Inputs.front();
  else
    NameTag = "Reaction System";
}

 
/*F out = print(out)  . . . . . . . . . . . . . . . . . .  ReactionSystemBase
**
**  DESCRIPTION
**    out: The output stream
**
**  REMARKS
**
*/
ostream& ReactionSystemBase::print(ostream& out) const
{
  Identify::print(out);
  return out;
}

 
/*F Run() . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . The run
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int ReactionSystemBase::Run()
{

  return 0;       
}
 
/*F Exit()  . . . . . . . . . . . . . . . . . . . . . . . . . . final touches
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int ReactionSystemBase::Exit()
{
  return 0;
}


/*F GetNextInput() . . . . . . . . . . . . . . . . . . .

**
**  DESCRIPTION
**    takes the next input from Inputs and returns it
**    
**  REMARKS
**
*/
String ReactionSystemBase::GetNextInput()       // whchange added
{
  String aktinp = Inputs.front();
  Inputs.pop_front();
  return aktinp;
}

/*F DefaultSystemCommand(globvars)  . . . . . . . . . . . . . . . . . default
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int DefaultSystemCommand(ReactionSystemBase *g)
{
  ReactionSystemLevel1 *globvars = (ReactionSystemLevel1 *) g;
  cout << "Possible Commands are:\n";
  cout << globvars->Commands;
  return 1;
}
 
/*F DefaultSystemCommand(globvars)  . . . . . . . . . . . . . . . .  commands
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int PrintCommandList(ReactionSystemBase *g)
{
  ReactionSystemLevel1 *globvars = (ReactionSystemLevel1 *) g;
  cout << "Possible Commands are:\n";
  cout << globvars->Commands;
  return 1;
}
