/*
 * File:    settingsdialog.h
 * Author:  Ian Cathcart
 * Date:    2020/08/05
 * Version: 1.2
 *
 * Purpose: Define the behaviour of the settings dialog window.
 *
 * Modification history:
 * August 6, 2020 (IC V1.1)
 *  (a) Added saveSettings() and loadSettings() to save and load settings
 *      related to the settingsdialog window.
 *  (b) Added a signal to tell mainWindow that the user OK'd the dialog.
 * August 7, 2020 (IC V1.2)
 *  (a) Added on_jpgBgColour_clicked() and on_otherImageBgColour_clicked()
 *      to handle events for the new background colour buttons.
 */

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QtCore>

namespace Ui
{
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget * parent = nullptr);
    ~SettingsDialog();

private slots:
    void on_jpgBgColour_clicked();
    void on_otherImageBgColour_clicked();

public slots:
    void saveSettings();
    void loadSettings();

signals:
    void saveDone();

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
