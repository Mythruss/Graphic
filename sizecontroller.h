#ifndef EDGESIZECONTROLLER_H
#define EDGESIZECONTROLLER_H

#include "edge.h"
#include "node.h"

#include <QObject>
#include <QDoubleSpinBox>

class SizeController : QObject

{
    Q_OBJECT
public:
    SizeController(Edge * anEdge, QDoubleSpinBox * aBox);
    SizeController(Node * aNode, QDoubleSpinBox * diamBox,
                   QDoubleSpinBox *thicknessBox);


private slots:
    void setEdgeSize(double value);
    void setNodeSize(double value);
    void setNodeSize2(double value);
    void deletedEdgeBox();
    void deletedNodeBoxes();

private:
    Edge * edge;
    Node * node;
    QDoubleSpinBox * box1;
    QDoubleSpinBox * box2;
};

#endif // EDGESIZECONTROLLER_H
