#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "textwindow.h"
#include "ui_textwindow.h"
#include <regex>
#include <QFile>
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QInputDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile styleFile(":/essential files/stylesheet.qss");
    styleFile.open(QFile::ReadOnly);
    QString style = styleFile.readAll();
    styleFile.close();
    qApp->setStyleSheet(style);
}

MainWindow::~MainWindow()
{
    while (ui->tabWidget->count()) {
        on_tabWidget_tabCloseRequested(ui->tabWidget->count() - 1);
    }
    delete ui;
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    textWindow *widget = (textWindow*)ui->tabWidget->currentWidget();
    if(!widget->isSaved){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "File exit", "Do you want to save changes?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            if(!on_actionsave_triggered()){
                return;
            }
        }
    }
    ui->tabWidget->removeTab(index);
}


void MainWindow::on_actionCopy_triggered()
{
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Please open a file first");
        return;
    }
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Please open a file first");
        return;
    }
    textWindow *widget = (textWindow*)ui->tabWidget->currentWidget();
    widget->ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Please open a file first");
        return;
    }
    textWindow *widget = (textWindow*)ui->tabWidget->currentWidget();
    widget->ui->textEdit->paste();
}


void MainWindow::on_actionClear_triggered()
{
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Please open a file first");
        return;
    }
    textWindow *widget = (textWindow*)ui->tabWidget->currentWidget();
    widget->ui->textEdit->clear();
}


void MainWindow::on_actionCut_triggered()
{
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Please open a file first");
        return;
    }
    textWindow *widget = (textWindow*)ui->tabWidget->currentWidget();
    widget->ui->textEdit->cut();
}


void MainWindow::on_actionUndo_triggered()
{
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Please open a file first");
        return;
    }
    textWindow *widget = (textWindow*)ui->tabWidget->currentWidget();
    widget->ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Please open a file first");
        return;
    }
    textWindow *widget = (textWindow*)ui->tabWidget->currentWidget();
    widget->ui->textEdit->redo();
}


void MainWindow::on_actionAligh_center_triggered()
{
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Please open a file first");
        return;
    }
    textWindow *widget = (textWindow*)ui->tabWidget->currentWidget();
    widget->ui->textEdit->setAlignment(Qt::AlignCenter);
}


void MainWindow::on_actionAlign_left_triggered()
{
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Please open a file first");
        return;
    }
    textWindow *widget = (textWindow*)ui->tabWidget->currentWidget();
    widget->ui->textEdit->setAlignment(Qt::AlignLeft);
}


void MainWindow::on_actionAlign_right_triggered()
{
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Please open a file first");
        return;
    }
    textWindow *widget = (textWindow*)ui->tabWidget->currentWidget();
    widget->ui->textEdit->setAlignment(Qt::AlignRight);
}


void MainWindow::on_actionFont_triggered()
{
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Please open a file first");
        return;
    }
    textWindow *widget = (textWindow*)ui->tabWidget->currentWidget();
    bool *ok;
    QFont font = QFontDialog::getFont(ok,widget->ui->textEdit->currentFont(),this);
    widget->ui->textEdit->setCurrentFont(font);
}


void MainWindow::on_actionColor_triggered()
{
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Please open a file first");
        return;
    }
    textWindow *widget = (textWindow*)ui->tabWidget->currentWidget();
    QColor color = QColorDialog::getColor(widget->ui->textEdit->textColor(),this,"Choose font color");
    if(!color.isValid()){
        QMessageBox::warning(this,"Error","Please enter valid color");
        return;
    }
    widget->ui->textEdit->setTextColor(color);

}


void MainWindow::on_actionNew_triggered()
{
    textWindow *widget = new textWindow;
    ui->tabWidget->addTab(widget,"Untitled");
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
}


void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "open the file","","Text (*.txt)");
    QFileInfo fileInfo(filePath);
    QFile file(filePath);
    if(file.open(QFile::ReadOnly | QFile::Text)){
        textWindow *widget = new textWindow;
        widget->ui->textEdit->setText(file.readAll());
        widget->fileName = filePath;
        ui->tabWidget->addTab(widget,fileInfo.fileName());
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    }
    file.close();
}


bool MainWindow::on_actionsave_triggered()
{
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Please open a file first");
        return 0;
    }
    textWindow *widget = (textWindow*)ui->tabWidget->currentWidget();
    if(widget->fileName.isEmpty()){
        return on_actionSave_as_triggered();
    }
    QFile file(widget->fileName);
    if(file.open(QFile::WriteOnly | QFile::Text)){
        QTextStream out(&file);
        out << widget->ui->textEdit->toHtml();
    }
    file.flush();
    file.close();
    widget->isSaved = true;
    return 1;
}


bool MainWindow::on_actionSave_as_triggered()
{
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Please open a file first");
        return 0;
    }
    textWindow *widget = (textWindow*)ui->tabWidget->currentWidget();
    QString filePath = QFileDialog::getSaveFileName(this, "open the file","","Text (*.txt)");
    if(filePath.isEmpty()){
        QMessageBox::warning(this,"Error","File name can not be empty!");
        return 0;
    }
    QFileInfo fileInfo(filePath);
    for(auto& val : fileInfo.fileName()){
        if(val != '.' && val != ' ' && !val.isLetterOrNumber()){
            QMessageBox::warning(this,"Error","Enter valid file name!");
            return 0;
        }
    }
    QFile file(filePath);
    if(file.open(QFile::WriteOnly | QFile::Text)){
        QTextStream out(&file);
        out << widget->ui->textEdit->toHtml();
    }
    file.flush();
    file.close();
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),fileInfo.fileName());
    widget->fileName = filePath;
    widget->isSaved = true;
    return 1;
}

void MainWindow::on_actionFind_triggered()
{
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Please open a file first");
        return;
    }
    QString tarWord = QInputDialog::getText(this,"Word searching","Enter target word");
    if(tarWord.isEmpty()){
        QMessageBox::warning(this,"Error","Word can not be empty");
        return;
    }
    textWindow *widget = (textWindow*)ui->tabWidget->currentWidget();
    widget->ui->textEdit->moveCursor(QTextCursor::Start);
    while(widget->ui->textEdit->find(tarWord)){
        QMessageBox::information(this, "Word searching","Word was found");
        return;
    }
    QMessageBox::information(this, "Word searching","Word was not found");
}


void MainWindow::on_actionTo_lower_triggered()
{
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Please open a file first");
        return;
    }
    textWindow *widget = (textWindow*)ui->tabWidget->currentWidget();
    QTextCursor cursor = widget->ui->textEdit->textCursor();
    if(cursor.hasSelection())
    {
        cursor.insertText(cursor.selectedText().toLower());
    }
}


void MainWindow::on_actionTo_upper_triggered()
{
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Please open a file first");
        return;
    }
    textWindow *widget = (textWindow*)ui->tabWidget->currentWidget();
    QTextCursor cursor = widget->ui->textEdit->textCursor();
    if(cursor.hasSelection())
    {
        cursor.insertText(cursor.selectedText().toUpper());
    }
}


void MainWindow::on_actionReplace_triggered()
{
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Please open a file first");
        return;
    }
    QString oldWord = QInputDialog::getText(this,"Word replacing","Enter old word");
    if(oldWord.isEmpty()){
        QMessageBox::warning(this,"Error","Word can not be empty");
        return;
    }
    QString newWord = QInputDialog::getText(this,"Word replacing","Enter new word");
    if(newWord.isEmpty()){
        QMessageBox::warning(this,"Error","Word can not be empty");
        return;
    }
    textWindow *widget = (textWindow*)ui->tabWidget->currentWidget();
    widget->ui->textEdit->moveCursor(QTextCursor::Start);
    while(widget->ui->textEdit->find(oldWord)){
        widget->ui->textEdit->textCursor().insertText(newWord);
    }
}


void MainWindow::on_actionpage_counting_triggered()
{
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Please open a file first");
        return;
    }
    int n_words = 0,n_charsSpace,n_lines,n_chars = 0;
    textWindow *widget = (textWindow*)ui->tabWidget->currentWidget();
    QString text = widget->ui->textEdit->toPlainText();
    n_charsSpace = text.size();
    QStringList s_lines = text.split('\n');
    n_lines = s_lines.size();
    n_charsSpace -= (n_lines - 1);
    for(auto& item : s_lines){
        QStringList s_words = item.split(' ');
        for(auto& word : s_words){
            n_chars += word.size();
        }
        n_words += s_words.size();
    }
    QMessageBox::information(this,"Page counting","The number of characters without spaces: " + QString::number(n_chars) + "\nThe number of characters with spaces: " + QString::number(n_charsSpace) + "\nThe number of words: " + QString::number(n_words) + "\nThe number of lines: " + QString::number(n_lines));
}

