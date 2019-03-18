/*  FILE     MenuObjects.hh
**  PACKAGE  MenuObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "MenuObjects" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_MENUOBJECTS_HH
#define CoreObjects_MENUOBJECTS_HH
 
/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "MenuObjectsType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/

#define MENUOBJECTS_BASEOBJECT_NAME        "MenuBaseObject"
#define MENUOBJECTS_BASEOBJECT_ID          BASEOBJECTS_BASE_ID + 10
#define MENUOBJECTS_MENUTEXT_NAME          "MenuText"
#define MENUOBJECTS_MENUTEXT_ID            BASEOBJECTS_BASE_ID + 20
#define MENUOBJECTS_MENUTEXTCHOICE_NAME    "MenuTextChoice"
#define MENUOBJECTS_MENUTEXTCHOICE_ID      BASEOBJECTS_BASE_ID + 30
#define MENUOBJECTS_MENUCOMPOSITE_NAME     "MenuComposite"
#define MENUOBJECTS_MENUCOMPOSITE_ID       BASEOBJECTS_BASE_ID + 40
#define MENUOBJECTS_MENUCOMPOSITION_NAME   "MenuComposition"
#define MENUOBJECTS_MENUCOMPOSITION_ID     BASEOBJECTS_BASE_ID + 50
#define MENUOBJECTS_MENUWINDOW_NAME        "MenuWindow"
#define MENUOBJECTS_MENUWINDOW_ID          BASEOBJECTS_BASE_ID + 60
#define MENUOBJECTS_COREOBJECT_NAME        "MenuCoreObject"
#define MENUOBJECTS_COREOBJECT_ID          BASEOBJECTS_BASE_ID + 70
#define MENUOBJECTS_DIRECTEDTREE_NAME      "MenuDirectedTree"
#define MENUOBJECTS_DIRECTEDTREE_ID        BASEOBJECTS_BASE_ID + 80

#define MENU_DIRECT         0
#define MENU_RECURSIVE      1
#define MENU_TRUE           0
#define MENU_FALSE          1

BaseDataMenuTextChoice& NamesToMenuTextChoice(ObjectList<String>& names,
					      String& command);
int MenuChoiceClassesTextChoice(ReactionSystemBase *sys);
int MenuChoiceClassCoreObject(ReactionSystemBase *sys);
int MenuChoiceAttributeCoreObject(ReactionSystemBase *sys);
int MenuChoiceCoreObject(ReactionSystemBase *sys);
int MenuChoiceClassHierarchy(ReactionSystemBase *sys);

#endif
