#ifndef CONTENTPALETTE_H
#define CONTENTPALETTE_H

#include "scdockpalette.h"
#include "scribusapi.h"

class ScribusMainWindow;
class QStackedWidget;

class SCRIBUS_API ContentPalette : public ScDockPalette
{
	Q_OBJECT

	public:
		ContentPalette(QWidget* parent);
		~ContentPalette() {}
	public slots:
		void setMainWindow(ScribusMainWindow *mw);
		void AppModeChanged();
		void addPalette(ScDockPalette* palette);
	protected:
		ScribusMainWindow *m_ScMW;
	private:
		QStackedWidget* stackedWidget;
};

#endif
