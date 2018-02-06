#include "addobjectcommand.h"
#include <QDebug>

AddObjectCommand::AddObjectCommand(GlWidget *glwidget,Object3d *object, QUndoCommand *parent):
    QUndoCommand(parent),mGlWidget(glwidget),mObject(object)
{
    //This is for initialization
}

AddObjectCommand::~AddObjectCommand()
{

}

void AddObjectCommand::undo()
{
    mGlWidget->Remove(mObject);
    mGlWidget->update();
}

void AddObjectCommand::redo()
{
    mGlWidget->Append(mObject);
    mGlWidget->update();
}
