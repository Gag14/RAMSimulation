// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateSimulation(bool& b);
    void startClicked();
private:
    Ui::MainWindow *ui;
    QWidget *mainWidget;
    QHBoxLayout *mainLayout;
    QTextEdit *codeTextEdit;
    QTextEdit *ramTextEdit;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    QTimer *timer;
    QPushButton *start;
    int currentRow;
};

#endif // MAINWINDOW_H
