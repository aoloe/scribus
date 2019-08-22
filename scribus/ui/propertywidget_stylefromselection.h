#ifndef PROPERTYWIDGET_STYLEFROMSELECTION_H
#define PROPERTYWIDGET_STYLEFROMSELECTION_H

#include "ui_propertywidget_stylefromselection.h"

#include <QToolButton>

class PropertyWidget_StyleFromSelection : public QWidget, private Ui::PropertyWidget_StyleFromSelection
{
	Q_OBJECT

public:
	explicit PropertyWidget_StyleFromSelection(QToolButton* button, QWidget *parent = 0);
	~PropertyWidget_StyleFromSelection() {}

	void showEvent(QShowEvent*);

private:
	QToolButton* clickedButton;

};

#endif // PROPERTYWIDGET_STYLEFROMSELECTION_H
