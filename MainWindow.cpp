#include "MainWindow.hpp"
#include "ui_mainwindow.h"

#include <QtGui>

MainWindow::MainWindow(Model &_model, View &_view, QWidget *parent) : model ( _model ), view ( _view )
{
    QWidget* widget = new QWidget;
    widget->setContentsMargins ( 5,5,5,5 );
    this->setCentralWidget ( widget );
    this->glwidget = new GLWidget ( this->model,  this->view, widget );
    connect(this->glwidget, SIGNAL(mouseDragged(float, float)), this, SLOT(mouseDragged(float, float)));
    connect(this->glwidget, SIGNAL(fileDropped(QString)), this, SLOT(fileDropped(QString)));
    connect(this->glwidget, SIGNAL(wheelSpined(float, float, float)), this, SLOT(wheelSpined(float, float, float)));
    connect(this, SIGNAL(updated()), this->glwidget, SLOT(updateGL()));

    this->setWindowTitle(tr("Morse Complex"));
    this->setMinimumSize(800, 600);
    this->resize(800, 600);

    QString message = QString(tr("initialized"));
    statusBar()->showMessage(message);
}

MainWindow::~MainWindow()
{

}

void MainWindow::fileDropped(QString str){
    QString message = str + QString(tr("reading ...."));
    statusBar()->showMessage(message);
    if(this->model.openMesh(str)){
        QString message = QFileInfo(str).fileName() + QString(tr(" reading successed."));
        statusBar()->showMessage(message);
        emit update();
    }
}


void MainWindow::mouseDragged(float x, float y){
    QString  message ( tr ( "MouseDragging (" ) );
    QString strx;
    strx.setNum ( x );
    message += strx;
    message += tr ( ", " );
    QString stry;
    stry.setNum ( y );
    message += stry;
    message += tr ( ") " );

    //int alpha , beta , gamma;
    //this->_model.getEulerAngle(alpha , beta , gamma);
    //this->_cameraParameterWidget->setEulerAngle(alpha,beta,gamma);

    //double xpos , ypos , zpos;
    //this->_model.getCameraPosition(xpos,ypos,zpos);
    //this->_cameraParameterWidget->setCameraPosition(xpos,ypos,zpos);
    statusBar()->showMessage ( message );
    return;
}

void MainWindow::wheelSpined(float x, float y, float step){

}
