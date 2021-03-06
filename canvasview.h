/*
 * File:    canvasview.h
 * Author:  Rachel Bood
 * Date:    2014/11/07 (?)
 * Version: 1.6
 *
 * Purpose: Define the CanvasView class.
 *
 * Modification history:
 * Oct 11, 2019 (JD V1.1):
 *  (a) Added this header comment.
 *  (b) Minor formatting changes.
 * Nov 29, 2019 (JD V1.2):
 *  (a) Deleted unused and undefined isSnappedToGrid(bool snap);
 *  (b) Rename "none" mode to "drag" mode, for less confusion.
 *  (c) Added getModeName() declaration.
 * June 19, 2020 (IC V1.3)
 *  (a) Added nodeCreated() and edgeCreated() signals to tell mainWindow to
 *      update the edit tab.
 * July 24, 2020 (IC V1.4)
 *  (a) Added clearCanvas() function that removes all items from the canvas.
 * August 5, 2020 (IC V1.5)
 *  (a) Added nodeThickness to nodeParams, setUpNodeParams, and createNode.
 * August 11 (IC V1.6)
 *  (a) Added scaleView, wheelEvent, zoomIn, and zoomOut as well as updated
 *      keyPressEvent to allow for zooming on the canvas, similar to the zoom
 *      from preview.cpp, using either a key press or mouse wheel scroll.
 */


#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#include "canvasscene.h"
#include "graph.h"

#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

class Node;
class Edge;

class CanvasView: public QGraphicsView
{
    Q_OBJECT
  public:

    // If this enum is edited, also edit getModeName() in canvasview.cpp
    enum mode {drag, join, del, edit, freestyle};

    typedef struct nParams
    {
        qreal diameter;
        bool isNumbered;
        QString label;
        qreal labelSize;
        QColor fillColour;
        QColor outlineColour;
        qreal nodeThickness;
    } Node_Params;

    typedef struct eParams
    {
        qreal size;
        QString label;
        qreal LabelSize;
        QColor color;
        bool isNumbered;
    } Edge_Params;

    CanvasView(QWidget * parent = 0);
    QList<Node *> selectedNodes;
    QList<Edge *> selectedEdges;

    void setUpNodeParams(qreal nodeDiameter, bool numberedLabels,
			 QString label, qreal nodeLabelSize,
			 QColor nodeFillColour, QColor nodeOutLineColour,
			 qreal nodeThickness);
    void setUpEdgeParams(qreal edgeSize, QString edgeLabel,
                         qreal edgeLabelSize, QColor edgeLineColour,
                         bool numberedLabels);

    Node * createNode(QPointF pos);
    Edge * createEdge(Node * source, Node * destination);
    Edge * addEdgeToScene(Node * source, Node * destination);
    int getMode() const;
    static QString getModeName(int mode);
    void setMode(int m);

    public slots:
	void snapToGrid(bool snap);
	void clearCanvas();
	void zoomIn();
	void zoomOut();

  signals:
	void setKeyStatusLabelText(QString text);
	void resetDragMode();
	void nodeCreated();
	void edgeCreated();
	void zoomChanged(QString zoomText);

  protected:
	void dragEnterEvent(QDragEnterEvent * event);
	void mouseDoubleClickEvent(QMouseEvent * event);
	void mousePressEvent(QMouseEvent * event);
	void keyPressEvent(QKeyEvent * event);
	virtual void scaleView(qreal scaleFactor);
	virtual void wheelEvent(QWheelEvent *event);

  private:
	int modeType;
	int timerId;
	CanvasScene * aScene;
	Graph * freestyleGraph;
	Node_Params * nodeParams;
	Edge_Params * edgeParams;
	Node * node1, * node2;
};

#endif // CANVASVIEW_H
