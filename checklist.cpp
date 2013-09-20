#include "icons.h"
#include "checklist.h"

FXDEFMAP(Checklist) ChecklistMap[] = {
  FXMAPFUNC(SEL_COMMAND, Checklist::ID_NEWITEM, Checklist::addNewItem),
  FXMAPFUNC(SEL_COMMAND, Checklist::ID_CLEARLIST, Checklist::clearItems),
  FXMAPFUNC(SEL_COMMAND, Checklist::ID_EDITITEM, Checklist::editItem),
  FXMAPFUNC(SEL_COMMAND, Checklist::ID_MARKCOMPLETE,
		  Checklist::markItemComplete),
  FXMAPFUNC(SEL_COMMAND, Checklist::ID_MARKINCOMPLETE,
		  Checklist::markItemIncomplete),
  FXMAPFUNC(SEL_DOUBLECLICKED, Checklist::ID_MAINLIST,
		  Checklist::toggleItem),
};

FXIMPLEMENT(Checklist, FXMainWindow, ChecklistMap, ARRAYNUMBER(ChecklistMap));

Checklist::Checklist(FXApp *app) : 
	FXMainWindow(app, "Checklist", NULL, NULL, DECOR_ALL, 0, 0, 230, 650)
{
	menubar = new FXMenuBar(this, LAYOUT_SIDE_TOP | LAYOUT_FILL_X);
	filemenu = new FXMenuPane(this);
	editmenu = new FXMenuPane(this);

	list = new FXList(this, this, ID_MAINLIST,
			LAYOUT_FILL_Y | LAYOUT_FILL_X);

	completeIcon = new FXPNGIcon(getApp(), complete);
	markcompleteIcon = new FXPNGIcon(getApp(), markcomplete);
	incompleteIcon = new FXPNGIcon(getApp(), incomplete);
	markincompleteIcon = new FXPNGIcon(getApp(), markincomplete);
	newlistIcon = new FXPNGIcon(getApp(), newlist);
	clearlistIcon = new FXPNGIcon(getApp(), clearlist);
	edititemIcon = new FXPNGIcon(getApp(), edititem);
	quitchecklistIcon = new FXPNGIcon(getApp(), quitchecklist);

	setIcon(completeIcon);

	/*new FXMenuCommand(filemenu, "&Open\tCtrl-O");
	new FXMenuCommand(filemenu, "&Save\tCtrl-S");*/
	new FXMenuCommand(filemenu, "&Quit\tCtrl-Q",
			quitchecklistIcon, getApp(), FXApp::ID_QUIT);
	new FXMenuCommand(editmenu, "&New\tCtrl-N",
			newlistIcon, this, Checklist::ID_NEWITEM);
	new FXMenuCommand(editmenu, "Mark as &Completed\tCtrl-C",
			markcompleteIcon, this, Checklist::ID_MARKCOMPLETE);
	new FXMenuCommand(editmenu, "Mark as &Incomplete\tCtrl-I",
			markincompleteIcon, this, Checklist::ID_MARKINCOMPLETE);
	new FXMenuCommand(editmenu, "Clear &List\tCtrl-L",
			clearlistIcon, this, Checklist::ID_CLEARLIST);
	new FXMenuCommand(editmenu, "&Edit Item\tCtrl-E",
			edititemIcon, this, Checklist::ID_EDITITEM);

	new FXMenuTitle(menubar, "&File", NULL, filemenu);
	new FXMenuTitle(menubar, "&Edit", NULL, editmenu);
}

Checklist::~Checklist()
{
	delete editmenu;
	delete filemenu;
	delete menubar;
	delete completeIcon;
	delete incompleteIcon;
}

void Checklist::create()
{
	completeIcon->create();
	incompleteIcon->create();
	FXMainWindow::create();

	show(PLACEMENT_SCREEN);
}

long Checklist::addNewItem(FXObject*, FXSelector, void*)
{
	FXString item;

	if(FXInputDialog::getString(item, this, "Check List",
			"Add New Checklist Item")) {
		list->appendItem(item, incompleteIcon, (void*)0);
	}
	return 1;
}

long Checklist::clearItems(FXObject*, FXSelector, void*)
{
	list->clearItems();
	return 1;
}

long Checklist::markItemComplete(FXObject*, FXSelector, void*)
{
	int item = list->getCurrentItem();
	if(item >= 0) {
		list->setItemIcon(item, completeIcon);
		list->setItemData(item, (void*)1);
	}
	return 1;
}

long Checklist::markItemIncomplete(FXObject*, FXSelector, void*)
{
	int item = list->getCurrentItem();
	if(item >= 0) {
		list->setItemIcon(item, incompleteIcon);
		list->setItemData(item, (void*)0);
	}
	return 1;
}

long Checklist::toggleItem(FXObject *obj, FXSelector sel, void *ptr)
{
	int item = list->getCurrentItem();
	if(item >= 0) {
		if(list->getItemData(item)) {
			markItemIncomplete(obj, sel, ptr);
		} else {
			markItemComplete(obj, sel, ptr);
		}
	}
	return 1;
}

long Checklist::editItem(FXObject*, FXSelector, void*)
{
	FXString item;
	int item_i;

	item_i = list->getCurrentItem();
	if(item_i < 0)
		return 1;

	item = list->getItemText(item_i);
	if(FXInputDialog::getString(item, this, "Check List",
			"Edit Checklist Item")) {
		list->setItemText(item_i, item);
	}

	return 1;
}
