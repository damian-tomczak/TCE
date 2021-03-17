#include "tce_editor.h"

TCE_Editor::TCE_Editor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    this->setWindowTitle("TCastEngine");
    this->resize(800, 600);

    createActions();
    createMenus();

    createWidgets();
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

void TCE_Editor::createWidgets()
{
    currentX = new QLabel("Current X: ");
    currentY = new QLabel("Current Y: ");

    info = new QLabel("Change Color: ");
    color = new QComboBox;
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
    scene = new GraphicsScene(900 / WORLD_SIZE, WORLD_SIZE, currentX, currentY);

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

    update();
}

void TCE_Editor::exportWorld()
{
    std::fstream file("main.level", std::ios::out); 
    std::string str = "";

    for (unsigned int y = 0; y < scene->WORLD_SIZE; y++)
    {
        str.append("\n");
        for (unsigned int x = 0; x < scene->WORLD_SIZE; x++)
        {
            str.append(std::to_string(scene->world[y][x]->type));
        }
    }

    file.write(&str[0], str.length());

    std::wstring path = ExePath() + L"\\TCE.exe";
    startup(const_cast<wchar_t*>(path.c_str()));
}

void TCE_Editor::createLayout()
{
    mainLayout = new QHBoxLayout;
    rightLayout = new QVBoxLayout;
    currentLayout = new QHBoxLayout;
    changeLayout = new QHBoxLayout;

    color->addItem("");
    color->addItem("Orange");
    color->addItem("Yellow");
    color->addItem("Green");


    view = new QGraphicsView(this);
    view->setScene(scene);
    view->setGeometry(QRect(0, 33, 600, 567));

    mainLayout->addWidget(view);

    currentLayout->addWidget(currentX);
    currentLayout->addWidget(currentY);

    changeLayout->addWidget(info);
    changeLayout->addWidget(color);

    rightLayout->addLayout(currentLayout);
    rightLayout->addLayout(changeLayout);
    
    rightLayout->addWidget(currentX);

    rightLayout->setAlignment(Qt::AlignRight);

    mainLayout->addLayout(rightLayout);

    mainWidget = new QWidget();
    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);
}


void TCE_Editor::changeWorld(unsigned int WORLD_SIZE)
{
    delete scene;
    scene = new GraphicsScene(900 / WORLD_SIZE, WORLD_SIZE, currentX, currentY);

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

    view->setScene(scene);

    update();
}

void TCE_Editor::startup(LPWSTR lpApplicationName)
{
    STARTUPINFO info = { sizeof(info) };
    PROCESS_INFORMATION processInfo;
    if (CreateProcess(lpApplicationName, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
    {
        WaitForSingleObject(processInfo.hProcess, INFINITE);
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
    }
    else
    {
        qDebug() << "CreateProcess failed " << GetLastError();
    }

}

std::wstring TCE_Editor::ExePath() {
    TCHAR buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\");
    return std::wstring(buffer).substr(0, pos);
}
