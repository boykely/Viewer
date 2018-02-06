#ifndef REMOVEOBJECTCOMMAND_H
#define REMOVEOBJECTCOMMAND_H

#include <QUndoCommand>
#include "Object/object3d.h"

class RemoveObjectCommand : public QUndoCommand
{
public:
    RemoveObjectCommand(Object3d *object,QUndoCommand *parent=nullptr);
};

#endif // REMOVEOBJECTCOMMAND_H
