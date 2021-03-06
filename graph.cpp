/*
 * File:    graph.cpp
 * Author:  Rachel Bood
 * Date:    2014/11/07 (?)
 * Version: 1.3
 *
 * Purpose:
 *
 * Modification history:
 * July 20, 2020 (IC V1.1)
 *  (a) Fixed setRotation to properly rotate graph items while taking into
 *      account their previous rotation value.
 * August 12, 2020 (IC V1.2)
 *  (a) Reversed the previous change to setRotation since it was only needed
 *      when graphs could be children of other graphs which can no longer
 *      happen.
 * August 20, 2020 (IC V1.3)
 *  (a) Once again changed setRotation back to the July 20 change. The issue
 *      was that the GraphicsItem rotation call at the end of the function
 *      wasn't using the additive rotation value but instead the passed value.
 */

#include "graph.h"
#include "canvasview.h"
#include "node.h"
#include "edge.h"
#include "graphmimedata.h"

#include <QMimeData>
#include <QDrag>
#include <QDebug>
#include <QByteArray>
#include <QGraphicsSceneMouseEvent>
#include <QtAlgorithms>
#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QtMath>

#define MOVED   0

static const bool verbose = false; // used for debugging

/*
 * Name:        Graph()
 * Purpose:     Constructor for the graph object
 * Arguments:   none
 * Output:      none
 * Modifies:    private variables of the graph object
 * Returns:     none
 * Assumptions: none
 * Bugs:        none
 * Notes:       none
 */
Graph::Graph()
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemIsFocusable);
    setCacheMode(DeviceCoordinateCache);
    moved = 0;
    rotation = 0;
    setAcceptHoverEvents(true);
    setZValue(0);
}

/*
 * Name:        isMoved()
 * Purpose:     a flag used to determined if the graph was dropped onto the canvasscene
 * Arguments:   none
 * Output:      none
 * Modifies:    int moved
 * Returns:     none
 * Assumptions: none
 * Bugs:        none
 * Notes:       none
 */
void Graph::isMoved()
{
    moved = 1;
    setHandlesChildEvents(false);
}

/*
 * Name:        mouseReleaseEvent()
 * Purpose:     the event that is triggered after the user releases the mouse click
 * Arguments:   QGraphicsSceneMouseEvent*
 * Output:      none
 * Modifies:    the Cursor icon
 * Returns:     none
 * Assumptions: none
 * Bugs:        none
 * Notes:       none
 */
void Graph::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::CrossCursor);
    QGraphicsItem::mouseReleaseEvent(event);
}

/*
 * Name:        paint()
 * Purpose:     no purpose but required to implement for custom QGraphicsItems
 * Arguments:   QPainter*, QStyleOptionGraphicsItem *, QWidget *
 * Output:      none
 * Modifies:    none
 * Returns:     none
 * Assumptions: none
 * Bugs:        none
 * Notes:       A Graph object is more of a container to house the nodes and edges
 *              therefore nothing is required to be drawn in a graph object
 */
void Graph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_UNUSED(painter);
}

/*
 * Name:        boundingRect()
 * Purpose:     returns the bouding rectangle of the graph
 * Arguments:   none
 * Output:      none
 * Modifies:    none
 * Returns:     boudingRect()
 * Assumptions: none
 * Bugs:        none
 * Notes:       returns the bounding rectangle that surrounds the nodes and edges
 *              of the graph
 */
QRectF Graph::boundingRect() const
{
    return childrenBoundingRect();
}

/*
 * Name:        setRotation()
 * Purpose:     sets the Rotation of the graph
 * Arguments:   qreal
 * Output:      none
 * Modifies:    the graph, node and edge of the graph
 * Returns:     none
 * Assumptions: none
 * Bugs:        none
 * Notes:       the nodes and edge labels need to be rotated in the opposite direction
 *              otherwise the labels of the edges and nodes won't be easily read
 */
void Graph::setRotation(qreal aRotation, bool keepRotation)
{
    QList<QGraphicsItem *> list;
    foreach (QGraphicsItem * gItem, this->childItems())
        list.append(gItem);

    while (!list.isEmpty())
    {
        foreach (QGraphicsItem * child, list)
        {
            if (child != nullptr || child != 0)
            {
                if (child->type() == Graph::Type)
                {
                    list.append(child->childItems());
                }
                else if (child->type() == Node::Type)
                {
                    Node * node = qgraphicsitem_cast<Node*>(child);
                    if (keepRotation)
                        node->setRotation(node->getRotation() + -aRotation);
                    else
                        node->setRotation(-aRotation);
                }
                else if(child->type() == Edge::Type)
                {
                    Edge * edge = qgraphicsitem_cast<Edge*>(child);
                    if (keepRotation)
                        edge->setRotation(edge->getRotation() + -aRotation);
                    else
                        edge->setRotation(-aRotation);
                }
                list.removeOne(child);
            }
        }
    }
    if (keepRotation)
        rotation = getRotation() + aRotation;
    else
        rotation = aRotation;
    QGraphicsItem::setRotation(rotation);
}


/*
 * Name:	getRotation()
 * Purpose:	??
 * Arguments:
 * Output:
 * Modifies:
 * Returns:
 * Assumptions:
 * Bugs:
 * Notes:
 */

qreal
Graph::getRotation()
{
    return rotation;
}


/*
 * Name:        getRootParent()
 * Purpose:     returns the root parent of the graph
 * Arguments:   none
 * Output:      none
 * Modifies:    none
 * Returns:     QGraphicsItem *
 * Assumptions: none
 * Bugs:        none
 * Notes:       none
 */
QGraphicsItem *Graph::getRootParent()
{
    QGraphicsItem * parent = this;
    while (parent->parentItem() != nullptr || parent->parentItem() != 0)
        parent = parent->parentItem();
    return parent;
}

