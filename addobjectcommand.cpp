#include "addobjectcommand.h"

AddObjectCommand::AddObjectCommand(Object3d *object, QUndoCommand *parent):QUndoCommand(parent)
{
    //This is the current action
}

AddObjectCommand::~AddObjectCommand()
{

}
