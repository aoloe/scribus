#include "scribus.h" // ScribusMainWindow
#include "contentpalette.h"

#include <QWidget>
#include <QStackedWidget>

#include "appmodehelper.h" // for AppModeChanged (if needed)

#include "propertiespalette_image.h"
#include "propertiespalette_text.h"
#include "selection.h"
#include "pageitem_textframe.h"
#include "pageitem_imageframe.h"
#include "pageitem_table.h"
#include "styles/paragraphstyle.h"
#include "styles/charstyle.h"

ContentPalette::ContentPalette(QWidget* parent) :
	ScDockPalette(parent, "ContentPalette", nullptr)
{
	setObjectName(QString::fromLocal8Bit("ContentPalette"));

	QFont f(font());
	f.setPointSize(f.pointSize()-1);
	setFont(f);


	stackedWidget = new QStackedWidget(this);

	auto emptyPal = new QWidget();
	stackedWidget->addWidget(emptyPal);

	textPal = new PropertiesPalette_Text(this);
	stackedWidget->addWidget(textPal);

	imagePal = new PropertiesPalette_Image(this);
	stackedWidget->addWidget(imagePal);

	setWidget(stackedWidget);

	stackedWidget->setCurrentIndex(0);

	languageChange();
}

void ContentPalette::setMainWindow(ScribusMainWindow *mw)
{
	m_ScMW = mw;

	textPal->setMainWindow(mw);
	imagePal->setMainWindow(mw);

	connect(m_ScMW->appModeHelper, &AppModeHelper::AppModeChanged, this, &ContentPalette::AppModeChanged);
}

void ContentPalette::setDoc(ScribusDoc *doc)
{
	if((doc == (ScribusDoc*) m_doc) || (m_ScMW && m_ScMW->scriptIsRunning()))
		return;

	if (m_doc)
	{
		disconnect(m_doc->m_Selection, &Selection::selectionChanged, this, &ContentPalette::handleSelectionChanged);
		disconnect(m_doc, &ScribusDoc::docChanged, this, &ContentPalette::handleSelectionChanged);
	}

	m_doc = doc;
	m_item = nullptr;
	setEnabled(!m_doc->drawAsPreview);

	m_unitRatio = m_doc->unitRatio();
	m_unitIndex = m_doc->unitIndex();
	m_haveDoc = true;
	m_haveItem = false;

	textPal->setDoc(m_doc);
	imagePal->setDoc(m_doc);

	updateColorList();

	connect(m_doc->m_Selection, &Selection::selectionChanged, this, &ContentPalette::handleSelectionChanged);
	connect(m_doc, &ScribusDoc::docChanged, this, &ContentPalette::handleSelectionChanged);

	// Handle properties update when switching document
	handleSelectionChanged();
}

void ContentPalette::unsetDoc()
{
	if (m_doc)
	{
		disconnect(m_doc->m_Selection, &Selection::selectionChanged, this, &ContentPalette::handleSelectionChanged);
		disconnect(m_doc, &ScribusDoc::docChanged, this, &ContentPalette::handleSelectionChanged);
	}

	setEnabled(true);
	m_haveDoc = false;
	m_haveItem = false;
	m_doc=nullptr;
	m_item = nullptr;

	textPal->unsetItem();
	textPal->unsetDoc();
	imagePal->unsetItem();
	imagePal->unsetDoc();

	stackedWidget->setCurrentIndex(0);
}

void ContentPalette::unsetItem()
{
	m_haveItem = false;
	m_item = nullptr;

	imagePal->unsetItem();
	textPal->unsetItem();

	handleSelectionChanged();
}

PageItem* ContentPalette::currentItemFromSelection()
{
	if (m_doc && m_doc->m_Selection->count() > 0)
	{
		return m_doc->m_Selection->itemAt(0);
	}

	return nullptr;
}

void ContentPalette::AppModeChanged()
{
	if (!m_ScMW || m_ScMW->scriptIsRunning())
		return;

	if ((m_haveDoc) && (m_haveItem))
	{
		if (m_item->isTable())
		{
			textPal->setEnabled(m_doc->appMode == modeEditTable);
			if (m_doc->appMode == modeEditTable)
			{
				connect(m_item->asTable(), &PageItem_Table::selectionChanged, this, &ContentPalette::handleSelectionChanged);
			}
			else
			{
				disconnect(m_item->asTable(), &PageItem_Table::selectionChanged, this, &ContentPalette::handleSelectionChanged);
			}
		}
		textPal->handleSelectionChanged();
	}
}

void ContentPalette::setCurrentItem(PageItem *item)
{
	if (!m_ScMW || m_ScMW->scriptIsRunning())
		return;

	if (!item)
	{
		unsetItem();
		return;
	}

	if (!m_doc)
	{
		setDoc(item->doc());
	}

	m_haveItem = true;
	m_item = item;

	// TODO: in PropertiesPalette there is a a funny if for the groups: take care of it when adding the group panel

	if (!sender() || (m_doc->appMode == modeEditTable))
	{
		textPal->handleSelectionChanged();
		imagePal->handleSelectionChanged();
	}
}

void  ContentPalette::handleSelectionChanged()
{
	if (!m_haveDoc || !m_ScMW || m_ScMW->scriptIsRunning())
		return;

	int currentPane = stackedWidget->currentIndex();
	int newPane{currentPane};

	PageItem* currItem = currentItemFromSelection();

	// TODO: should me move this to setCurrentIndex()?
	if (!currItem)
	{
		stackedWidget->setCurrentIndex(0);
		m_haveItem = false;
	} else if (m_doc->m_Selection->count() > 1)
	{
		stackedWidget->setCurrentIndex(0);
	}
	else
	{
		m_haveItem = true;

		switch (currItem->itemType())
		{
		case PageItem::ImageFrame:
			newPane = 2;
			break;
		case PageItem::TextFrame:
			newPane = 1;
			break;
		case PageItem::PathText:
			newPane = 1;
			break;
		case PageItem::Table:
			if (m_doc->appMode == modeEditTable)
			{
				newPane = 1;
			}
			break;
		default:
			break;
		}
		setCurrentItem(currItem);
	}
	if (currentPane != newPane)
	{
		stackedWidget->setCurrentIndex(newPane);
	}
	updateGeometry();
	ScDockPalette::update();
}

void ContentPalette::unitChange()
{
	if (!m_haveDoc)
		return;

	bool tmp = m_haveItem;
	m_haveItem = false;

	m_unitRatio = m_doc->unitRatio();
	m_unitIndex = m_doc->unitIndex();

	textPal->unitChange();
	imagePal->unitChange();

	m_haveItem = tmp;
}

void ContentPalette::updateColorList()
{
	if (!m_haveDoc || !m_ScMW || m_ScMW->scriptIsRunning())
		return;

	textPal->updateColorList();

	assert (m_doc->PageColors.document());
}

bool ContentPalette::userActionOn()
{
	return imagePal->userActionOn();
}

void ContentPalette::changeEvent(QEvent *e)
{
	if (e->type() == QEvent::LanguageChange)
	{
		languageChange();
		return;
	}
	ScDockPalette::changeEvent(e);
}

void ContentPalette::languageChange()
{
	setWindowTitle( tr("Content Properties"));

	textPal->languageChange();
	imagePal->languageChange();
}

void ContentPalette::update(PageItem_ImageFrame* image)
{
	imagePal->showScaleAndOffset(image->imageXScale(), image->imageYScale(), image->imageXOffset(), image->imageYOffset());
}

void ContentPalette::update(const ParagraphStyle& style)
{
	textPal->updateStyle(style);
}

void ContentPalette::update(const CharStyle& style)
{
	textPal->updateCharStyle(style);
}

void ContentPalette::update(PageItem_TextFrame* text)
{
}

void ContentPalette::updateTextStyles()
{
	textPal->updateParagraphStyles();
}

void ContentPalette::updateTextAlignment(int i)
{
	textPal->showAlignment(i);
}

void ContentPalette::updateTextDirection(int i)
{
	textPal->showDirection(i);
}

void ContentPalette::updateTextFontSize(int i)
{
	textPal->showFontSize(i);
}

void ContentPalette::updateTextLanguage(const QString& language)
{
	textPal->showLanguage(language);
}
