#ifndef ADDOBJECTCOMMAND_H
#define ADDOBJECTCOMMAND_H

#include<QUndoCommand>
#include "Object/object3d.h"

class AddObjectCommand : public QUndoCommand
{
public:
    AddObjectCommand(Object3d *object, QUndoCommand *parent=nullptr);
    ~AddObjectCommand();
};

#endif // ADDOBJECTCOMMAND_H
