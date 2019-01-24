#ifndef CONTENTPALETTE_H
#define CONTENTPALETTE_H

#include "scribusapi.h"
#include "scdockpalette.h"
#include "scguardedptr.h"

class QStackedWidget;

class ScribusMainWindow;
class ScribusDoc;
class PageItem;

class PropertiesPalette_Text;
class PropertiesPalette_Image;
class PageItem_TextFrame;
class PageItem_ImageFrame;
class ParagraphStyle;
class CharStyle;

class SCRIBUS_API ContentPalette : public ScDockPalette
{
	Q_OBJECT

	public:
		ContentPalette(QWidget* parent);
		~ContentPalette() {}

		void updateColorList();
		bool userActionOn();
		virtual void changeEvent(QEvent *e) override;
		void update(PageItem_ImageFrame* image);
		void update(const ParagraphStyle& style);
		void update(PageItem_TextFrame* image);
		void updateTextStyles();
		void updateTextAlignment(int i);
		void updateTextDirection(int i);
		void updateTextFontSize(int i);
		void updateTextLanguage(const QString& language);

	public slots:
		void setMainWindow(ScribusMainWindow *mw);

		void setDoc(ScribusDoc *doc);
		void unsetDoc();
		void unsetItem();
		void AppModeChanged();
		void setCurrentItem(PageItem *i);
		PageItem* currentItemFromSelection();
		void handleSelectionChanged();

		void update(const CharStyle& style);

		void unitChange();
		void languageChange();

	private:
		ScribusMainWindow *m_ScMW{nullptr};
		ScGuardedPtr<ScribusDoc> m_doc{nullptr};
		PageItem* m_item;

		bool m_haveDoc{false};
		bool m_haveItem{false};
		double m_unitRatio{1.0};
		int m_unitIndex{0};

		QStackedWidget* stackedWidget;
		PropertiesPalette_Text* textPal;
		PropertiesPalette_Image* imagePal;
		
		// the order must match the insertion of the widgets in the constructor
		enum class Panel {
			empty,
			text,
			image
		};
};

#endif
