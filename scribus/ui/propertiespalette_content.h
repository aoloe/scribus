/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#ifndef PROPERTIESPALETTE_CONTENT_H
#define PROPERTIESPALETTE_CONTENT_H

#include <QStackedWidget>

#include "ui_propertiespalette_contentbase.h"

#include "scribusapi.h"
#include "scrpalettebase.h"

#include "scguardedptr.h"
// #include "sctextstruct.h"

class PageItem;
// class PropertyWidget_Advanced;
class ScribusDoc;
class ScribusMainWindow;
class Selection;

class SCRIBUS_API PropertiesPalette_Content : public QStackedWidget, public Ui::PropertiesPalette_ContentBase
{
	Q_OBJECT

public:
	PropertiesPalette_Content(QWidget* parent);
	~PropertiesPalette_Content() {}

	virtual void changeEvent(QEvent *e);
	
	/** @brief Returns true if there is a user action going on at the moment of call. */
	bool userActionOn(); // not yet implemented!!! This is needed badly.
                         // When user releases the mouse button or arrow key, changes must be checked
                         // and if in ScribusView a groupTransaction has been started it must be also
                         // commmited
protected:

	bool   m_haveDoc;
	bool   m_haveItem;
	double m_unitRatio;
	int    m_unitIndex;

	PageItem *m_item;
	ScribusMainWindow*       m_ScMW;
	ScGuardedPtr<ScribusDoc> m_doc;

private:
	PageItem* currentItemFromSelection();
	
public slots:
	void setMainWindow(ScribusMainWindow *mw);
	
	void setDoc(ScribusDoc *d);
	void setCurrentItem(PageItem *i);
	void unsetDoc();
	void unsetItem();

	void handleSelectionChanged();
	void handleUpdateRequest(int);

	void languageChange();
	void unitChange();
	void changeLang(int id);

	// update widget layout
	// void updateTreeLayout();

protected:
    // add here the text and image palettes
	// PropertyWidget_Advanced* advancedWidgets;
	// int advancedWidgetsItem;
};

#endif
