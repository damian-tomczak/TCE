#include "project_settings.h"

ProjectSettings::ProjectSettings(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("TCastEngine Editor");
	this->setFixedSize(200, 250);

	this->setAttribute(Qt::WA_QuitOnClose, false);

	size = new QSpinBox();
	size->setMinimum(1);
	size->setMaximum(100);

	playerX = new QSpinBox();
	playerY = new QSpinBox();

	// TODO
	//playerX->setMinimum(1); 
	//playerY->setMinimum(1);

	//playerX->setMaximum(100);
	//playerY->setMaximum(100);

	label = new QLabel("Input world size: ");

	button = new QPushButton("Confirm");

	QHBoxLayout* inputLayout = new QHBoxLayout();
	QVBoxLayout* mainLayout = new QVBoxLayout;

	inputLayout->addWidget(label);
	inputLayout->addWidget(size);

	mainLayout->addLayout(inputLayout);

	mainLayout->addWidget(button);

	setLayout(mainLayout);

	connect(button, &QAbstractButton::released, this, &ProjectSettings::setProjSet);
}

void ProjectSettings::setProjSet()
{
	this->hide();
	emit changed(size->value());
}