#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QComboBox>

#include <fstream>
#include <vector>
#include <windows.h>
#include <filesystem>

#include "projectsettings.h"
#include "tile.h"
#include "graphics_scene.h"
#include "ui_tce_editor.h"

class TCE_Editor : public QMainWindow
{
    Q_OBJECT

public:
    TCE_Editor(QWidget *parent = Q_NULLPTR);

private:
    Ui::TCE_EditorClass ui;
    QMenuBar* menu;
    QMenu* helpMenu;

    QAction* aboutAct;
    QAction* helpAct;
    QAction* projSet;
    QAction* exportAct;

    QLabel* currentX;
    QLabel* currentY;
    QLabel* info;
    QComboBox* color;

    QHBoxLayout* mainLayout;
    QVBoxLayout* rightLayout;

    QHBoxLayout* currentLayout;
    QHBoxLayout* changeLayout;

    QGraphicsView* view;
    GraphicsScene* scene;

    QWidget* mainWidget;

    void createMenus();
    void createActions();
    void startup(LPWSTR);
    std::wstring ExePath();

protected:
    void aboutMessage();
    void errorMessage();
    void helpMessage();
    void exportWorld();
    void createLayout();
    void projectSettings();
    void createWorld(unsigned int);
    void changeWorld(unsigned int);
    void createWidgets();

};
