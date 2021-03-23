#pragma once

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>

#include "ui_projectsettings.h"

class ProjectSettings : public QWidget
{
	Q_OBJECT

public:
	ProjectSettings(QWidget *parent = Q_NULLPTR);

private:
	Ui::ProjectSettings ui;
	QSpinBox* size;
	QSpinBox* playerX;
	QSpinBox* playerY;

	QPushButton* button;
	QLabel* label;

	void setProjSet();

signals:
	void changed(unsigned int);
};
