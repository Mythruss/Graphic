/*
 * File:	mainwindow.h
 * Author:	Rachel Bood
 * Date:	January 25, 2015.
 * Version:	1.16
 *
 * Purpose:	Define the MainWindow class.
 *
 * Modification history:
 * Oct 13, 2019 (JD V1.2)
 *  (a) Minor comment & formatting changes.
 *  (b) Add lookupColour() (for TikZ output routine).
 * Nov 17, 2019 (JD V1.3)
 *  (a) Remove lookupColour() (now a non-class function).
 * Nov 28, 2019 (JD V1.4)
 *  (a) Add dumpGraphIc() and dumpTikZ().
 * Nov 29, 2019 (JD V1.5)
 *  (a) Rename "none" mode to "drag" mode, for less confusion.
 *      This required changes to mainwindow.ui as well.
 *	(Also changed "Complete" to "Draw edges" there.)
 * Dec 6, 2019 (JD V1.6)
 *  (a) Rename generate_Freestyle_{Nodes,Edges} to {node,edge}ParamsUpdated
 *      to better reflect what those functions do.
 *  (b) Modify generate_Graph() to take a parameter.
 *  (c) Add the enum widget_num as the parameter values for generate_Graph().
 * Dec 9, 2019 (JD V1.7)
 *  (a) Add on_numOfNodes1_valueChanged() to follow the actions of
 *	on_numOfNodes2_valueChanged().
 * Dec 12, 2019 (JD V1.8)
 *  (a) #include defuns.h.
 *  (b) Change "changed_widget" from an int to and enum widget_ID.
 *  (c) Move enum widget_ID to defuns.h.
 * May 15, 2020 (IC V1.9)
 *  (a) Renamed set_Font_Label_Sizes() to set_Font_Sizes() to better reflect
 *	what the function does.
 * May 25, 2020 (IC V1.10)
 *  (a) Removed setKeyStatusLabel() in favour of tooltips for each mode.
 * June 6, 2020 (IC V1.11)
 *  (a) Added set_Interface_Sizes() to fix sizing issues on monitors with
 *      different DPIs.
 * June 10, 2020 (IC V1.12)
 *  (a) Added loadSettings(), saveSettings(), and reimplemented closeEvent().
 * June 19, 2020 (IC V1.13)
 *  (a) Added multiple slots for updating edit tab when graphs/nodes/edges are
 *      created.
 * July 31, 2020 (IC V1.14)
 *  (a) Added somethingChanged() slot and bool promptSave that detects if any
 *      change has been made on the canvas since the last save and thus a new
 *      save prompt is needed on exit.
 * August 5, 2020 (IC V1.15)
 *  (a) Added updateDpiAndPreview slot and settingsDialog variable to be used
 *      in conjunction with the new settingsDialog window which allows the user
 *      to use a custom DPI value instead of the system default.
 * August 21, 2020 (IC V1.16)
 *  (a) Added the ability to number edge labels similar to nodes so
 *      on_EdgeNumLabelCheckBox_clicked was added as well.
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGridLayout>
#include <QScrollArea>

#include "defuns.h"
#include "graph.h"
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget * parent = 0);
    ~MainWindow();
    void set_Interface_Sizes();

  protected:
    virtual void closeEvent (QCloseEvent *event);

  private slots:
    bool save_Graph();
    bool load_Graphic_File();
    void load_Graphic_Library();
    void select_Custom_Graph(QString graphName);
    void generate_Graph();
    void generate_Graph(enum widget_ID changed_widget);
    void style_Graph(enum widget_ID changed_widget);
    void generate_Combobox_Titles();
    void dumpGraphIc();
    void dumpTikZ();

    void set_Font_Sizes();
    void on_NodeOutlineColor_clicked();
    void on_NodeFillColor_clicked();
    void on_EdgeLineColor_clicked();

    void on_NodeNumLabelCheckBox_clicked(bool checked);
    void on_EdgeNumLabelCheckBox_clicked(bool checked);
    void on_graphType_ComboBox_currentIndexChanged(int index);
    void on_numOfNodes1_valueChanged(int arg1);
    void on_numOfNodes2_valueChanged(int arg1);

    void nodeParamsUpdated();
    void edgeParamsUpdated();

    void on_deleteMode_radioButton_clicked();

    void on_joinMode_radioButton_clicked();

    void on_editMode_radioButton_clicked();

    void on_dragMode_radioButton_clicked();

    void on_freestyleMode_radioButton_clicked();

    void updateEditTab(int index);
    void updateEditTab();

    void somethingChanged();
    void updateDpiAndPreview();

private:
    void loadSettings();
    void saveSettings();

    Ui::MainWindow * ui;
    QDir dir;
    QString fileDirectory;
    QGridLayout * gridLayout;
    QScrollArea * scroll;
    QList<Graph *> graphList;
    bool promptSave = false;
    SettingsDialog * settingsDialog;
};

#endif // MAINWINDOW_H
