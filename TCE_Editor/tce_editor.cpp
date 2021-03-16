#include "tce_editor.h"

TCE_Editor::TCE_Editor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    this->setWindowTitle("TCastEngine");
    this->resize(800, 600);

    createActions();
    createMenus();
    createWorld(10);
    createLayout();
}

void TCE_Editor::aboutMessage()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("About Menu");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText("Copyright (C) 2021 <a href='https://damian-tomczak.pl'>Damian Tomczak</a><br>"
        "Did you find a error? <a href='mailto:kontakt@damian-tomczak.pl'>kontakt@damian-tomczak.pl</a>");
    msgBox.exec();
}

void TCE_Editor::helpMessage()
{
    QMessageBox::information(NULL, tr("Help Menu"), tr(
        "The program shows how \"three-dimensional\" fps game engines were desgined at the turn of the 1990s."));
}

void TCE_Editor::errorMessage()
{
    QMessageBox::critical(NULL, tr("Critical Error"),
        tr("Something went wrong..."),
        QMessageBox::Close);
    QApplication::quit();
}

void TCE_Editor::createActions()
{
    aboutAct = new QAction(tr("About"), this);
    connect(aboutAct, &QAction::triggered, this, &TCE_Editor::aboutMessage);

    helpAct = new QAction(tr("Help"), this);
    connect(helpAct, &QAction::triggered, this, &TCE_Editor::helpMessage);

    projSet = new QAction(tr("Project Settings"), this);
    connect(projSet, &QAction::triggered, this, &TCE_Editor::projectSettings);

    exportAct = new QAction(tr("Start"), this);
    connect(exportAct, &QAction::triggered, this, &TCE_Editor::exportWorld);
}

void TCE_Editor::createMenus()
{
    menu = new QMenuBar();
    menu->addAction(projSet);
    menu->addAction(exportAct);
    this->setMenuBar(menu);

    helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(helpAct);
    helpMenu->addAction(aboutAct);
}

void TCE_Editor::projectSettings()
{
    ProjectSettings* wProjSet;
    wProjSet = new ProjectSettings();

    connect(wProjSet, &ProjectSettings::changed, this, &TCE_Editor::changeWorld);
    wProjSet->show();
}

void TCE_Editor::createWorld(unsigned int WORLD_SIZE)
{
    scene = new GraphicsScene(900 / WORLD_SIZE, WORLD_SIZE);

    for (unsigned int y = 0; y < WORLD_SIZE; y++)
    {
        scene->world.push_back(std::vector<Tile*>());
        for (unsigned int x = 0; x < WORLD_SIZE; x++)
        {
            unsigned int positionX = 1 * x * scene->TILE_SIZE;
            unsigned int positionY = 1 * y * scene->TILE_SIZE;
            scene->world[y].push_back(new Tile(positionX, positionY, x, y, scene->TILE_SIZE));

            if (y == 0 || y == WORLD_SIZE-1 
                ||  x == 0 || x == WORLD_SIZE-1)
                scene->world[y][x]->bborder = true;

            scene->addItem(scene->world[y][x]);
            //world[y][x]->rect = scene->addRect(QRectF(1 * x * tileSize, 1 * y * tileSize, tileSize, tileSize));
        }
    }

    view = new QGraphicsView(this);
    view->setScene(scene);
    view->setGeometry(QRect(0, 33, 600, 567));

    update();
}

void TCE_Editor::exportWorld()
{

}

void TCE_Editor::createLayout()
{
    mainLayout = new QVBoxLayout;
    currentLayout = new QHBoxLayout;
    changeLayout = new QHBoxLayout;

    currentX = new QLabel("test");
    currentY = new QLabel("test");
    info = new QLabel("Change Color: ");

    currentLayout->addWidget(currentX);
    currentLayout->addWidget(currentY);

    //color = new QComboBox();
    changeLayout->addWidget(info);
    //changeLayout->addWidget(color);

    mainLayout->addLayout(currentLayout);
    mainLayout->addLayout(changeLayout);

    this->setLayout(mainLayout);
}

/*
void TCE_Editor::changeWorld(unsigned int WORLD_SIZE)
{
    scene = new GraphicsScene(900 / WORLD_SIZE, WORLD_SIZE);

    for (unsigned int y = 0; y < WORLD_SIZE; y++)
    {
        scene->world.push_back(std::vector<Tile*>());
        for (unsigned int x = 0; x < WORLD_SIZE; x++)
        {
            unsigned int positionX = 1 * x * scene->TILE_SIZE;
            unsigned int positionY = 1 * y * scene->TILE_SIZE;
            scene->world[y].push_back(new Tile(positionX, positionY, x, y, scene->TILE_SIZE));

            if (y == 0 || y == WORLD_SIZE - 1
                || x == 0 || x == WORLD_SIZE - 1)
                scene->world[y][x]->bborder = true;

            scene->addItem(scene->world[y][x]);
        }
    }

    view = new QGraphicsView(this);
    view->setScene(scene);
    view->setGeometry(QRect(0, 33, 600, 567));

    update();
}
*/