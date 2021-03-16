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
	~ProjectSettings();

private:
	Ui::ProjectSettings ui;
	QSpinBox* size;
	QPushButton* button;
	QLabel* label;

	void setWorldSize();

signals:
	void changed(unsigned int);
};
