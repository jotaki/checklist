#include "icons.h"
#include "checklist.h"
#include "reminder_dialog.h"

FXDEFMAP(Checklist) ChecklistMap[] = {
  FXMAPFUNC(SEL_COMMAND, Checklist::ID_NEWITEM, Checklist::addNewItem),
  FXMAPFUNC(SEL_COMMAND, Checklist::ID_CLEARLIST, Checklist::clearItems),
  FXMAPFUNC(SEL_COMMAND, Checklist::ID_EDITITEM, Checklist::editItem),
  FXMAPFUNC(SEL_COMMAND, Checklist::ID_OPENFILE, Checklist::openChecklist),
  FXMAPFUNC(SEL_COMMAND, Checklist::ID_SAVEFILE, Checklist::saveChecklist),
  FXMAPFUNC(SEL_COMMAND, Checklist::ID_QUIT, Checklist::quitApp),
  FXMAPFUNC(SEL_COMMAND, Checklist::ID_NEWREMINDER, Checklist::newReminder),
  FXMAPFUNC(SEL_COMMAND, Checklist::ID_MARKCOMPLETE,
		  Checklist::markItemComplete),
  FXMAPFUNC(SEL_COMMAND, Checklist::ID_MARKINCOMPLETE,
		  Checklist::markItemIncomplete),
  FXMAPFUNC(SEL_DOUBLECLICKED, Checklist::ID_MAINLIST,
		  Checklist::toggleItem),
  FXMAPFUNC(SEL_TIMEOUT, Checklist::ID_TIMEOUT, Checklist::remind),
};

FXIMPLEMENT(Checklist, FXMainWindow, ChecklistMap, ARRAYNUMBER(ChecklistMap));

Checklist::Checklist(FXApp *app) : 
	FXMainWindow(app, "Checklist", NULL, NULL, DECOR_ALL, 0, 0, 230, 650)
{
	menubar = new FXMenuBar(this, LAYOUT_SIDE_TOP | LAYOUT_FILL_X);
	filemenu = new FXMenuPane(this);
	checklistmenu = new FXMenuPane(this);
	remindermenu = new FXMenuPane(this);
	tab = new FXTabBook(this, NULL, 0, TABBOOK_BOTTOMTABS |
			LAYOUT_FILL_X | LAYOUT_FILL_Y);

	completeIcon = new FXPNGIcon(getApp(), complete);
	markcompleteIcon = new FXPNGIcon(getApp(), markcomplete);
	incompleteIcon = new FXPNGIcon(getApp(), incomplete);
	markincompleteIcon = new FXPNGIcon(getApp(), markincomplete);
	newlistIcon = new FXPNGIcon(getApp(), newlist);
	clearlistIcon = new FXPNGIcon(getApp(), clearlist);
	edititemIcon = new FXPNGIcon(getApp(), edititem);
	quitchecklistIcon = new FXPNGIcon(getApp(), quitchecklist);
	openIcon = new FXPNGIcon(getApp(), openckl);
	saveIcon = new FXPNGIcon(getApp(), saveckl);
	mainIcon = new FXPNGIcon(getApp(), mainicon);
	mainIconSm = new FXPNGIcon(getApp(), mainiconsm);
	reminderIcon = new FXPNGIcon(getApp(), remindericon);
	newreminderIcon = new FXPNGIcon(getApp(), newreminder);
	reminderlistIcon = new FXPNGIcon(getApp(), reminder);

	new FXTabItem(tab, "Checklist", markcompleteIcon);
	checklist = new FXList(tab, this, ID_MAINLIST,
			LAYOUT_FILL_Y | LAYOUT_FILL_X);

	new FXTabItem(tab, "Reminders", reminderIcon);
	reminderlist = new FXList(tab, this, ID_REMINDERLIST,
			LAYOUT_FILL_Y | LAYOUT_FILL_X);

	stateChanged = false;

	setIcon(mainIcon);
	setMiniIcon(mainIconSm);

	new FXMenuCommand(filemenu, "&Open\tCtrl-O",
			openIcon, this, Checklist::ID_OPENFILE);
	new FXMenuCommand(filemenu, "&Save\tCtrl-S",
			saveIcon, this, Checklist::ID_SAVEFILE);
	new FXMenuCommand(filemenu, "&Quit\tCtrl-Q",
			quitchecklistIcon, this, Checklist::ID_QUIT);

	new FXMenuCommand(checklistmenu, "&New\tCtrl-N",
			newlistIcon, this, Checklist::ID_NEWITEM);
	new FXMenuCommand(checklistmenu, "Mark as &Completed\tCtrl-C",
			markcompleteIcon, this, Checklist::ID_MARKCOMPLETE);
	new FXMenuCommand(checklistmenu, "Mark as &Incomplete\tCtrl-I",
			markincompleteIcon, this, Checklist::ID_MARKINCOMPLETE);
	new FXMenuCommand(checklistmenu, "Clear &List\tCtrl-L",
			clearlistIcon, this, Checklist::ID_CLEARLIST);
	new FXMenuCommand(checklistmenu, "&Edit Item\tCtrl-E",
			edititemIcon, this, Checklist::ID_EDITITEM);

	new FXMenuCommand(remindermenu, "New &Reminder\tCtrl-R",
			newreminderIcon, this, Checklist::ID_NEWREMINDER);

	new FXMenuTitle(menubar, "&File", NULL, filemenu);
	new FXMenuTitle(menubar, "&Checklist", NULL, checklistmenu);
	new FXMenuTitle(menubar, "&Reminders", NULL, remindermenu);
}

Checklist::~Checklist()
{
	delete checklistmenu;
	delete remindermenu;
	delete filemenu;
	delete menubar;

	delete completeIcon;
	delete incompleteIcon;
	delete newlistIcon;
	delete clearlistIcon;
	delete edititemIcon;
	delete markcompleteIcon;
	delete markincompleteIcon;
	delete quitchecklistIcon;
	delete openIcon;
	delete saveIcon;
	delete mainIcon;
	delete mainIconSm;
	delete reminderIcon;
	delete newreminderIcon;
	delete reminderlistIcon;

	delete checklist;
	delete reminderlist;
	delete tab;
}

void Checklist::create()
{
	completeIcon->create();
	incompleteIcon->create();
	reminderlistIcon->create();
	FXMainWindow::create();

	show(PLACEMENT_SCREEN);
}

long Checklist::addNewItem(FXObject*, FXSelector, void*)
{
	FXString item;

	if(FXInputDialog::getString(item, this, "Check List",
			"Add New Checklist Item")) {
		checklist->appendItem(item.text(),
				incompleteIcon, (void*)(FXival)0);
		stateChanged = true;
	}
	return 1;
}

long Checklist::clearItems(FXObject*, FXSelector, void*)
{
	checklist->clearItems();
	return 1;
}

long Checklist::markItemComplete(FXObject*, FXSelector, void*)
{
	int item = checklist->getCurrentItem();
	if(item >= 0) {
		checklist->setItemIcon(item, completeIcon);
		checklist->setItemData(item, (void*)(FXival)1);
		stateChanged = true;
	}
	return 1;
}

long Checklist::markItemIncomplete(FXObject*, FXSelector, void*)
{
	int item = checklist->getCurrentItem();
	if(item >= 0) {
		checklist->setItemIcon(item, incompleteIcon);
		checklist->setItemData(item, (void*)(FXival)0);
		stateChanged = true;
	}
	return 1;
}

long Checklist::toggleItem(FXObject *obj, FXSelector sel, void *ptr)
{
	int item = checklist->getCurrentItem();
	if(item >= 0) {
		if(checklist->getItemData(item)) {
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

	item_i = checklist->getCurrentItem();
	if(item_i < 0)
		return 1;

	item = checklist->getItemText(item_i);
	if(FXInputDialog::getString(item, this, "Check List",
			"Edit Checklist Item")) {
		checklist->setItemText(item_i, item.text());
		stateChanged = true;
	}

	return 1;
}

/* YICK */
long Checklist::openChecklist(FXObject*, FXSelector, void*)
{
	FXString path, item;
	FXFileStream stream;
	FXchar type, tmp, checked;

	if(stateChanged && !removeData())
		return 1;
	
	path = FXFileDialog::getOpenFilename(this, "Open Checklist", "",
			"Checklist File (*.ckl)");

	if(path.empty())
		return 1;

	if(!stream.open(path)) {
		FXMessageBox::error(this, MBOX_OK, "Error",
				"Could not open ``%s'' for read", path.text());
		return 1;
	}

	checklist->clearItems();
	while(!stream.eof()) {
		stream >> type;
		stream >> checked;
		checked -= '0';
		item = "";
		do {
			stream >> tmp;
			if(tmp == '\n')
				break;
			item.append(tmp);
		} while(!stream.eof());

		if(!item.empty()) {
			checklist->appendItem(item, checked?
					completeIcon : incompleteIcon,
					(void*)(FXival) checked);
		}
	}
	stream.close();
	stateChanged = false;

	return 1;
}

long Checklist::saveChecklist(FXObject*, FXSelector, void*)
{
	FXString path, str;
	FXFileStream stream;
	FXuint result;
	int i;

	path = FXFileDialog::getSaveFilename(this, "Save Checklist", "",
			"Checklist File (*.ckl)");

	if(path.empty())
		return 1;

	if(FXStat::exists(path)) {
		result = FXMessageBox::question(this, MBOX_YES_NO,
				"File exists", "Are you sure you want to "
				"overwrite ``%s''?", path.text());
		if(result == MBOX_CLICKED_NO)
			return 1;
	}

	if(!stream.open(path, FXStreamSave)) {
		FXMessageBox::error(this, MBOX_OK, "Could not save",
			"The file ``%s'' does not appear writable.",
			path.text());
		return 1;
	}

	for(i = 0; i < checklist->getNumItems(); ++i) {
		stream << 'C';
		stream << (FXchar) ((FXival)checklist->getItemData(i) + '0');

		str = checklist->getItemText(i);
		stream.save(str.text(), str.length());
		stream << '\n';
	}
	stream.close();
	stateChanged = false;

	return 1;
}

bool Checklist::removeData()
{
	FXuint result;

	result = FXMessageBox::question(this, MBOX_YES_NO, "Are you sure?",
		"The contents of this Checklist have changed, are you sure "
		"you want to continue this action?");

	return result == MBOX_CLICKED_YES;
}

long Checklist::quitApp(FXObject*, FXSelector, void*)
{
	if(!stateChanged || (stateChanged && removeData()))
		getApp()->exit();

	return 1;
}

long Checklist::newReminder(FXObject*, FXSelector, void*)
{
	ReminderDialog *dlg;

	dlg = new ReminderDialog(getApp());
	if(dlg->execute()) {
		if(dlg->getTime() == 0) {
			FXMessageBox::error(this, MBOX_OK, "Invalid time",
					"Invalid sleep time entered. (%lu)",
					dlg->getTime());
			goto done;
		}
		reminderlist->appendItem(dlg->getDescription(),
				reminderlistIcon);

		getApp()->addTimeout(this, ID_TIMEOUT, dlg->getTime(),
				new FXString(dlg->getDescription()));
	}

done:
	delete dlg;
	return 1;
}

long Checklist::remind(FXObject*, FXSelector, void *data)
{
	FXString *str = (FXString*) data;

	FXMessageBox::information(this, MBOX_OK, "Checklist Reminder",
			"%s", str->text());

	delete str;
	return 1;
}
