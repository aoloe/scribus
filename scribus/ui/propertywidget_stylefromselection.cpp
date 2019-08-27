#include "propertywidget_stylefromselection.h"

#include "scribusdoc.h"
#include "iconmanager.h"

namespace PropertyWidget {

StyleFromSelection::StyleFromSelection(QToolButton* button, ScribusDoc* doc, QWidget *parent)
	: QWidget(parent), clickedButton{button}, m_doc{doc}
{
	setupUi(this);

	connect(newStyleEdit, &QLineEdit::textChanged, this, &StyleFromSelection::doEditStyleName);
	connect(newStyleEdit, &QLineEdit::returnPressed, [this](){
	if (createButton->isEnabled()) this->doCreate();});
	connect(updateButton, &QPushButton::clicked, this, &StyleFromSelection::doUpdate);
	connect(createButton, &QPushButton::clicked, this, &StyleFromSelection::doCreate);
}

/**
 * - Align the popup to the right side of the button.
 * - update the list of styles and the current style.
 * - initialize the edit field and the create button
 */
void StyleFromSelection::showEvent(QShowEvent*)
{
	auto widget = parentWidget();
	QPoint p = widget->pos();
	QRect geo = clickedButton->geometry();
	widget->move(p.x() + geo.width() - this->geometry().width(), p.y());

	styleNames = getStyleNames();
	currentStyleLabel->setText(getCurrentStyleName());
	styleNames = getStyleNames();
	newStyleEdit->setText("");
	newStyleEdit->setFocus();
	createButton->setEnabled(false);
}

/**
 * Warn and disable create if the style name already exists
 */
void StyleFromSelection::doEditStyleName()
{
	if (styleNames.contains(newStyleEdit->text()))
	{
		createButton->setEnabled(false);
		newStyleEdit->setStyleSheet("color: #FF0000");
	}
	else
	{
		createButton->setEnabled(true);
		newStyleEdit->setStyleSheet("color: #000000");
	}
	// TODO: if valid, doUpdate() on return key
}
void StyleFromSelection::doUpdate()
{
	parentWidget()->close();
	emit updateStyle();
}

void StyleFromSelection::doCreate()
{
	parentWidget()->close();
	emit createStyle(newStyleEdit->text());
}

} // namespace
