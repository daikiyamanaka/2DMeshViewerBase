#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <Eigen/Core>

#include "GLWidget.hpp"
#include "View.hpp"
#include "Model.hpp"


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(Model& model, View& view, QWidget *parent = 0);
    ~MainWindow();
    

private:
    Model &model;
    View &view;
    GLWidget *glwidget;



signals:
    void updated(void);

private slots:
    void fileDropped(QString str);
    void mouseDragged(float x, float y);
    void wheelSpined(float x, float y, float step);
};

#endif // MAINWINDOW_H
