#ifndef PROPERTYWIDGET_STYLEFROMSELECTION_H
#define PROPERTYWIDGET_STYLEFROMSELECTION_H

#include "ui_propertywidget_stylefromselection.h"

#include <QToolButton>

class ScribusDoc;

namespace PropertyWidget {

class StyleFromSelection : public QWidget, private Ui::PropertyWidget_StyleFromSelection
{
	Q_OBJECT

public:
	explicit StyleFromSelection(QToolButton* button, ScribusDoc* doc, QWidget *parent = 0);
	~StyleFromSelection() {}

	void setCurrentStyle(std::function<QString(void)> f) { getCurrentStyleName = f; }
	void setStylesList(std::function<QStringList(void)> f) { getStyleNames = f; }

	void showEvent(QShowEvent*);

private:
	QToolButton* clickedButton;
	ScribusDoc* m_doc;
	std::function<QString(void)> getCurrentStyleName;
	std::function<QStringList(void)> getStyleNames;

	QStringList styleNames;

private slots:
	void doEditStyleName();
	void doUpdate();
	void doCreate();
signals:
	void updateStyle();
	void createStyle(QString styleName);
};

} // namespace

#endif // PROPERTYWIDGET_STYLEFROMSELECTION_H
