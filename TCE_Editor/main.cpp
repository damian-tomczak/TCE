#include "tce_editor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TCE_Editor w;
    w.show();
    return a.exec();
}

