
/*
 * File:	canvasscene.h
 * Author:	Rachel Bood
 * Date:	?
 * Version:	1.3
 *
 * Purpose:
 *
 * Modification history:
 * Feb 3, 2016 (JD V1.0):
 *  (a) Minor formatting changes/cleanups, add header comment.
 * Dec 13, 2019 (JD V1.1)
 *  (a) Remove unused private var numOfNodes.
 * June 19, 2020 (IC V1.2)
 *  (a) Added graphDropped() signal to tell mainWindow to update the edit tab.
 * July 9, 2020 (IC V1.3)
 *  (a) Added graphJoined() signal to tell mainWindow to update the edit tab.
 */

#ifndef CANVASSCENE_H
#define CANVASSCENE_H

#include "mainwindow.h"
#include "node.h"
#include "graph.h"

#include <QGraphicsScene>

class CanvasScene : public QGraphicsScene
{
    Q_OBJECT

public:
    typedef struct undoPositions
    {
        QPointF pos;
        Node * node;
    } undo_Node_Pos;

    CanvasScene();
    void isSnappedToGrid(bool snap);
    void getConnectionNodes();
    int getMode() const;
    void setCanvasMode(int mode);
    void searchAndSeparate(QList<Node *> adjacentNodes);

signals:
    void graphDropped(Graph * graph);
    void graphJoined();
    void itemDeleted();

protected:
    void dragMoveEvent (QGraphicsSceneDragDropEvent * event);
    void dropEvent (QGraphicsSceneDragDropEvent * event);
    void drawBackground(QPainter * painter, const QRectF &rect);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
    void keyReleaseEvent(QKeyEvent * event);

private:
    int modeType;
    bool snapToGrid;
    bool moved = false;
    const QSize mCellSize;		// The size of the cells in the grid.
    QGraphicsItem * mDragged;		// The item being dragged.
    Node * connectNode1a, * connectNode1b; // The first Nodes to be joined.
    Node * connectNode2a, * connectNode2b; // The second Nodes to be joined.
    QPointF mDragOffset;
    QList<undo_Node_Pos *> undoPositions;
    // The distance from the top left of the item to the mouse position.
};

#endif // CANVASSCENE_H
