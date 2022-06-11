#include "textwindow.h"
#include "ui_textwindow.h"

textWindow::textWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::textWindow)
{
    ui->setupUi(this);
    ui->textEdit->setTextColor(QColor("#454655"));
}

textWindow::~textWindow()
{
    delete ui;
}

void textWindow::on_textEdit_textChanged()
{
    isSaved = false;
}

