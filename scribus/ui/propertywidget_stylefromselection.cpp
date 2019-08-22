#include "propertywidget_stylefromselection.h"

PropertyWidget_StyleFromSelection::PropertyWidget_StyleFromSelection(QToolButton* button, QWidget *parent) : QWidget(parent), clickedButton{button}
{
	setupUi(this);
}

void PropertyWidget_StyleFromSelection::showEvent(QShowEvent*)
{
    QPoint p = this->pos();
    QRect geo = clickedButton->geometry();
    this->move(p.x()+geo.width()-this->geometry().width(), p.y());
}
