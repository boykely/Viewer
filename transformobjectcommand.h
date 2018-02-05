#ifndef TRANSFORMOBJECTCOMMAND_H
#define TRANSFORMOBJECTCOMMAND_H

#include <QUndoCommand>
#include "Object/object3d.h"

class TransformObjectCommand : public QUndoCommand
{
public:
    TransformObjectCommand(Object3d *object,QUndoCommand *parent=nullptr);
    ~TransformObjectCommand();
};

#endif // TRANSFORMOBJECTCOMMAND_H
