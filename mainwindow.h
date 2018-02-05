#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include<QPushButton>
#include <QMenu>
#include<QMenuBar>
#include <QAction>
#include <QUndoStack>

class GlWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addTriangle();
    void addPlane();
public slots:
    void showMaximized();
    void show();

private:
    GlWidget *mGlWidget;
    QHBoxLayout *mLayout;
    QMenu *mFileMenu;
    QMenu *mEditMenu;
    QAction *mUndoAction;
    QAction *mRedoAction;
    QUndoStack *mUndoStack;

    void initMenu();
};

#endif // MAINWINDOW_H
