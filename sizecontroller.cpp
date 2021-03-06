/*
 * File:    sizecontroller.cpp
 * Author:  Rachel Bood
 * Date:    2014/11/07 (?)
 * Version: 1.1
 *
 * Purpose: ?
 *
 * Modification history:
 * July 15, 2020 (IC V1.1)
 *  (a) Updated the node sizecontroller to take two spinboxes as parameters,
 *      one for node penwidth (thickness) and the other for node diameter.
 *  (b) Added setNodeSize2 to handle the new thickness box and a node specific
 *      delete function to delete both boxes.
 */

#include "sizecontroller.h"


SizeController::SizeController(Edge *anEdge, QDoubleSpinBox *aBox)
{
    edge = anEdge;
    box1 = aBox;
    if (box1 != nullptr || box1 != 0)
    {
        box1->setValue(edge->getPenWidth());
        connect(box1, SIGNAL( valueChanged(double)),
                this, SLOT(setEdgeSize(double)));
        connect(anEdge, SIGNAL(destroyed(QObject*)),
                this, SLOT(deletedEdgeBox()));
        connect(anEdge, SIGNAL(destroyed(QObject*)),
                this, SLOT(deleteLater()));
    }
}

SizeController::SizeController(Node * aNode, QDoubleSpinBox *diamBox,
                               QDoubleSpinBox *thicknessBox)
{
    node = aNode;
    box1 = diamBox;
    box2 = thicknessBox;
    if ((box1 != nullptr || box1 != 0) && (box2 != nullptr || box2 != 0))
    {
        box1->setValue(node->getDiameter());
        box1->setSingleStep(0.05);
        box2->setValue(node->getPenWidth());
        connect(box1, SIGNAL(valueChanged(double)),
                this, SLOT(setNodeSize(double)));
        connect(box2, SIGNAL(valueChanged(double)),
                this, SLOT(setNodeSize2(double)));
        connect(aNode, SIGNAL(destroyed(QObject*)),
                this, SLOT(deletedNodeBoxes()));
        connect(aNode, SIGNAL(destroyed(QObject*)),
                this, SLOT(deleteLater()));
    }
}

void SizeController::setEdgeSize(double value)
{
    if (edge != nullptr || edge != 0)
    edge->setPenWidth(value);
}

void SizeController::setNodeSize(double value)
{
    if (node != nullptr || node != 0)
        node->setDiameter(value);
}

void SizeController::setNodeSize2(double value)
{
    if (node != nullptr || node != 0)
        node->setPenWidth(value);
}

void SizeController::deletedEdgeBox()
{
    delete box1;
}

void SizeController::deletedNodeBoxes()
{
    delete box1;
    delete box2;
}

