#include "scribus.h" // ScribusMainWindow
#include "contentpalette.h"

#include <QStackedWidget>

#include "appmodehelper.h" // for AppModeChanged (if needed)

ContentPalette::ContentPalette(QWidget* parent) :
	ScDockPalette(parent, "ContentPalette", nullptr)
{
}

void ContentPalette::setMainWindow(ScribusMainWindow *mw)
{
	m_ScMW = mw;

	stackedWidget = new QStackedWidget(this);
	setWidget(stackedWidget);

	connect(m_ScMW->appModeHelper, SIGNAL(AppModeChanged(int,int)), this, SLOT(AppModeChanged()));
}

void ContentPalette::AppModeChanged()
{
}

void ContentPalette::addPalette(ScDockPalette *palette)
{
	stackedWidget->addWidget(palette);
}
