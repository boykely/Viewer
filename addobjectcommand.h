#ifndef ADDOBJECTCOMMAND_H
#define ADDOBJECTCOMMAND_H

#include<QUndoCommand>
#include "Object/object3d.h"
#include "glwidget.h"
#include <QDataStream>

class AddObjectCommand : public QUndoCommand
{
public:
    AddObjectCommand(GlWidget *glwidget, Object3d *object, QUndoCommand *parent=nullptr);
    ~AddObjectCommand();

    void undo() override;
    void redo() override;

private:
    GlWidget *mGlWidget;
    Object3d *mObject = nullptr;
    QDataStream mHistory;
};

#endif // ADDOBJECTCOMMAND_H
