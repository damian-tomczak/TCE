#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_tce_editor.h"

class TCE_Editor : public QMainWindow
{
    Q_OBJECT

public:
    TCE_Editor(QWidget *parent = Q_NULLPTR);

private:
    Ui::TCE_EditorClass ui;
};
