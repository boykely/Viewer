#include "removeobjectcommand.h"

RemoveObjectCommand::RemoveObjectCommand(Object3d *object,QUndoCommand *parent):
    QUndoCommand(parent)
{

}
