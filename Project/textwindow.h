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
    bool isSaved = true;
    QString fileName = "";
    explicit textWindow(QWidget *parent = nullptr);
    ~textWindow();

public:
    Ui::textWindow *ui;
private slots:
    void on_textEdit_textChanged();
};

#endif // TEXTWINDOW_H
