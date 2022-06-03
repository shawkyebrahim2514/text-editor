#ifndef TEXTWINDOW_H
#define TEXTWINDOW_H

#include <QWidget>

namespace Ui {
class textWindow;
}

class textWindow : public QWidget
{
    Q_OBJECT

public:
    QString fileName = "";
    explicit textWindow(QWidget *parent = nullptr);
    ~textWindow();

public:
    Ui::textWindow *ui;
};

#endif // TEXTWINDOW_H
