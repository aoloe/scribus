/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#ifndef CONTENTPALETTE_H
#define CONTENTPALETTE_H

class QCloseEvent;
class QEvent;
class QFocusEvent;
class QWidget;


#include "scdockpalette.h"
#include "scribusapi.h"

class PropertiesPalette_Text;
class ScribusDoc;
class ScribusMainWindow;
class UndoManager;

class SCRIBUS_API ContentPalette : public ScDockPalette
{
	Q_OBJECT

public:
	ContentPalette(QWidget* parent);
	~ContentPalette() {}

	virtual void changeEvent(QEvent *e);
	virtual void closeEvent(QCloseEvent *closeEvent);

	/** @brief Returns true if there is a user action going on at the moment of call. */
	bool userActionOn(); // not yet implemented!!! This is needed badly.
                         // When user releases the mouse button or arrow key, changes must be checked
                         // and if in ScribusView a groupTransaction has been started it must be also
                         // commmited

	PropertiesPalette_Content*  contentPal;

private:

	PageItem* currentItemFromSelection();
	
public slots:
	void setMainWindow(ScribusMainWindow *mw);
	
	void setDoc(ScribusDoc *d);
	void AppModeChanged();
	void setCurrentItem(PageItem *i);
	void unsetDoc();
	void unsetItem();

	void handleSelectionChanged();
	
	void languageChange();

protected:
	ScribusMainWindow *m_ScMW;

	bool      m_haveDoc;
	bool      m_haveItem;
	double    m_unitRatio;
	int       m_unitIndex;
	PageItem* m_item;
	UndoManager *undoManager;
	
	ScGuardedPtr<ScribusDoc> m_doc;
	
	int idTextItem;
};

#endif

