#ifndef CHECKLIST_H_
# define CHECKLIST_H_

# include <fx.h>

class Checklist : public FXMainWindow
{
	FXDECLARE(Checklist);

public:
	Checklist(FXApp *app);
	virtual ~Checklist();
	virtual void create();

	enum {
		ID_NEWITEM = FXMainWindow::ID_LAST,
		ID_CLEARLIST,
		ID_MARKCOMPLETE,
		ID_MARKINCOMPLETE,
		ID_MAINLIST,
		ID_EDITITEM,
		ID_OPENFILE,
		ID_SAVEFILE,

		ID_LAST
	};

protected:
	Checklist() {}

private:
	FXMenuBar *menubar;
	FXMenuPane *filemenu, *editmenu;
	FXList *list;
	FXPNGIcon *completeIcon, *incompleteIcon,
		  *newlistIcon, *clearlistIcon,
		  *edititemIcon, *markcompleteIcon,
		  *markincompleteIcon, *quitchecklistIcon,
		  *openIcon, *saveIcon;

public:
	long addNewItem(FXObject*, FXSelector, void*);
	long clearItems(FXObject*, FXSelector, void*);
	long markItemComplete(FXObject*, FXSelector, void*);
	long markItemIncomplete(FXObject*, FXSelector, void*);
	long toggleItem(FXObject*, FXSelector, void*);
	long editItem(FXObject*, FXSelector, void*);
	long openChecklist(FXObject*, FXSelector, void*);
	long saveChecklist(FXObject*, FXSelector, void*);
};

#endif	/* !CHECKLIST_H_ */
