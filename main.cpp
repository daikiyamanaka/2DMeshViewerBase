#include <QtGui/QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{   
    Model model;
    View view ( model );
    QApplication app ( argc, argv );

    MainWindow win ( model, view );

    win.show();
    return app.exec();
}
