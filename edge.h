/*
 * File:    edge.h
 * Author:  Rachel Bood
 * Date:    2014/11/07 (?)
 * Version: 1.8
 *
 * Purpose: creates an edge for the users graph
 * Modification history:
 * Nov 13, 2019 (JD V1.1):
 *  (a) Minor formatting tweaks.
 *  (b) Apply change of name label.h -> html-label.h
 * Nov 13, 2019 (JD V1.2):
 *  (a) Rename (in this order!)
 *	       label -> htmlLabel,
 *	       setWeightLabelSize() -> setLabelSize(),
 *             getWeightLabelSize() -> getLabelSize(),
 *	       setWeight() -> setLabel(), 
 *	       getWeight() -> getLabel(),
 *	       editWeight() -> editLabel(),
 *	       weight -> label,
 *	       esize -> labelSize,
 *     in order to rationalize the naming scheme.
 * Nov 30, 2019 (JD V1.3):
 *  (a) Made offset1 and offset2 local variables in
 *	createSelectionPolygon(), rather than having them as private
 *	class variables.  (Changed edge.cpp accordingly.)
 *  (b) Removed decl for the unused isDigits() function.
 * Dec 12, 2019 (JD V1.4):
 *  (a) Include defuns.h.
 * Dec 15, 2019 (JD V1.5):
 *  (a) Remove (globally) unused "penWidth" private variable.
 * June 18, 2020 (IC V1.6)
 *  (a) Added setEdgeLabel() slot to update label when changes are made on the
 *      canvas in edit mode.
 *  (b) Changed htmlLabel to public for use in labelcontroller.cpp
 * July 29, 2020 (IC V1.7)
 *  (a) Added eventFilter() to receive edit tab events so we can identify
 *      the edge being edited/looked at.
 * August 21, 2020 (IC V1.8)
 *  (a) Added the ability to number edge labels similar to nodes so setLabel
 *      has been replaced with copies of the label functions from node.cpp.
 *  (b) setLabelSize renamed to setEdgeLabelSize for clarity.
 */

#ifndef EDGE_H
#define EDGE_H

#include "defuns.h"
#include "html-label.h"
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QList>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QTextDocument>

class Node;
class CanvasView;
class PreView;

class Edge: public QGraphicsObject
{
    Q_OBJECT

public:
    Edge(Node * sourceNode, Node * destNode);

    void setDestRadius(qreal aRadius);
    qreal getDestRadius();

    void setSourceRadius(qreal aRadius);
    qreal getSourceRadius();

    void setPenWidth(qreal aPenWidth);
    qreal getPenWidth();

    void setRotation(qreal aRotation);
    qreal getRotation();

    void setColour(QColor color);
    QColor getColour();

    void setEdgeLabel(int number);
    void setEdgeLabel(QString aLabel, int number);
    void setEdgeLabel(QString aLabel, QString subscript);
    void setEdgeLabelSize(qreal edgeLabelSize);
    qreal getLabelSize();

    QRectF boundingRect() const;
    QPainterPath shape() const;

    QString getLabel();

    void adjust();
    void setDestNode(Node * node);
    void setSourceNode(Node * node);

    enum { Type = UserType + 2 };
    int type() const { return Type; }

    Node * sourceNode() const;
    Node * destNode() const;

    void editLabel(bool edit);
    QGraphicsItem * getRootParent();

     //~Edge(); deconstructor a WIP

    HTML_Label * htmlLabel;
    int causedConnect;
    int checked;

public slots:
    void setEdgeLabel(QString aLabel);

protected:
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void	createSelectionPolygon();
    Node	* source, * dest;   // Original names based on directed graphs
    QPointF	sourcePoint, destPoint;
    QPolygonF	selectionPolygon;
    qreal	destRadius, sourceRadius, rotation;
    QLineF	edgeLine;
    QString	label;
    int 	penStyle;
    qreal	labelSize, penSize;
    QColor	edgeColour;
    void	labelToHtml();
};

#endif // EDGE_H
