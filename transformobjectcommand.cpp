#include "transformobjectcommand.h"

TransformObjectCommand::TransformObjectCommand(Object3d *object,QUndoCommand *parent):QUndoCommand(parent)
{
    //This is the current action
}
TransformObjectCommand::~TransformObjectCommand()
{

}
