#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QMenu>
#include<QMenuBar>
#include <QAction>
#include <QUndoStack>
#include "treeview.h"

class GlWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addObject();
public slots:
    void showMaximized();
    void show();
    void import3dFileDialog(bool checked=false);

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
