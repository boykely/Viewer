#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include<QPushButton>

class GlWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void showMaximized();
    void show();

private:
    GlWidget *mGlWidget;
    QHBoxLayout *mLayout;
};

#endif // MAINWINDOW_H
