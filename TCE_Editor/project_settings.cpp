#include "project_settings.h"

ProjectSettings::ProjectSettings(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("TCastEngine Editor");
	this->setFixedSize(150, 150);

	size = new QSpinBox();
	size->setMinimum(1);
	size->setMaximum(100);

	label = new QLabel("Input world size: ");
	button = new QPushButton("Confirm");

	QHBoxLayout* inputLayout = new QHBoxLayout();
	QVBoxLayout* mainLayout = new QVBoxLayout;

	inputLayout->addWidget(label);
	inputLayout->addWidget(size);

	mainLayout->addLayout(inputLayout);
	mainLayout->addWidget(button);

	setLayout(mainLayout);

	connect(button, &QAbstractButton::released, this, &ProjectSettings::setWorldSize);
}

ProjectSettings::~ProjectSettings()
{
}

void ProjectSettings::setWorldSize()
{
	this->hide();
	emit changed(size->value());
}