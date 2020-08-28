/*
 * File:	defuns.h
 * Author:	Jim Diamond
 * Date:	2019-12-10
 * Version:	1.9
 *
 * Purpose:	Hold definitions that are needed by multiple classes
 *		and yet don't seem to meaningfully fit anywhere else.
 *		OO fanatics will be horrified by this expeditiousness.
 *
 * Modification history:
 * Dec 10, 2019
 *  (a) Initial version.  Define the widget_ID enum, needed to pass
 *	information (about which graph parameter widget changed,
 *	causing a (re)draw) between MainWindow and PreView.
 *	"ALL_WGT" is a special value that indicates all styles should
 *	be applied, rather than just one corresponding to a particular
 *	widget that changed; used when loading a "basic" graph.
 *	"NO_WGT" indicates that no styles should be applied; used when
 * May 25, 2020 (IC V1.1)
 *  (a) Added numLabelStart_WGT
 * Jun 9, 2020 (IC V1.2)
 *  (a) Moved BUTTON_STYLE here so it is not repeated across 3 files.
 * Jul 3, 2020 (IC V1.3)
 *  (a) Added nodeThickness_WGT
 * Aug 5, 2020 (IC V1.4)
 *  (a) Renamed nodeSize_WGT to nodeDiam_WGT and edgeSize_WGT to
 *      edgeThickness_WGT for clarity.
 * Aug 6, 2020 (IC V1.5)
 *  (a) Moved QSettings variable here so that it may be used globally
 *      across the program. It is currently defined at the beginning of
 *      mainwindow.cpp.
 * Aug 12, 2020 (IC V1.6)
 *  (a) Moved the physicalDPI variables here so they may also be used
 *      globally. They are also defined at the beginning of mainwindow.cpp.
 * Aug 18, 2020 (JD V1.7)
 *  (a) Add '#include <QDebug>' when DEBUG is defined, otherwise in some
 *      cases the compiler whines bitterly and pukes on your shoes.
 * Aug 21, 2020 (IC V1.8)
 *  (a) Added edgeNumLabelCheckbox_WGT and edgeNumLabelStart_WGT.
 *  (b) Renamed numLabelCheckbox_WGT to nodeNumLabelCheckbox_WGT
 *      and numLabelStart_WGT to nodeNumLabelStart_WGT for clarity.
 * Aug 24, 2020 (IC V1.9)
 *  (a) Added offsets_WGT
 */

#ifndef DEFUNS_H
#define DEFUNS_H

#include <QSettings>

// Use qDeb() and qDebu() for debugging, and then the statements can
// be turned on and off with a re-compile but no source-code editing.
#ifdef DEBUG
    #include <QDebug>
    static const bool debug = true;
    #define qDeb() qDebug().nospace().noquote() << Qt::fixed	\
        << qSetRealNumberPrecision(4)
    #define qDebu(...) qDebug(__VA_ARGS__)
#else
    static const bool debug = false;
    #define qDeb() if (false) qDebug()
    #define qDebu(...) 
#endif

#define BUTTON_STYLE "border-style: outset; border-width: 2px; " \
	     "border-radius: 5px; border-color: beige; padding: 3px;"

extern QSettings settings;
extern qreal currentPhysicalDPI, currentPhysicalDPI_X, currentPhysicalDPI_Y;

enum widget_ID {NO_WGT, ALL_WGT, nodeDiam_WGT, nodeLabel1_WGT, nodeLabel2_WGT,
		nodeLabelSize_WGT, nodeNumLabelCheckBox_WGT, nodeFillColour_WGT,
		nodeOutlineColour_WGT, edgeThickness_WGT, edgeLabel_WGT,
		edgeLabelSize_WGT, edgeLineColour_WGT, graphRotation_WGT,
		completeCheckBox_WGT, graphHeight_WGT, graphWidth_WGT,
		numOfNodes1_WGT, numOfNodes2_WGT, graphTypeComboBox_WGT,
		nodeNumLabelStart_WGT, nodeThickness_WGT, offsets_WGT,
		edgeNumLabelCheckBox_WGT, edgeNumLabelStart_WGT};

#endif
