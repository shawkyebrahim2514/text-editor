#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_tabWidget_tabCloseRequested(int index);

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionClear_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionAligh_center_triggered();

    void on_actionAlign_left_triggered();

    void on_actionAlign_right_triggered();

    void on_actionFont_triggered();

    void on_actionColor_triggered();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionsave_triggered();

    void on_actionSave_as_triggered();

    void on_actionFind_triggered();

    void on_actionTo_lower_triggered();

    void on_actionTo_upper_triggered();

    void on_actionReplace_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
