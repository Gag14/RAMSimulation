// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ramslot.h"
#include "ramsegment.h"

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QProgressBar>
#include <QVector>
#include <QGroupBox>
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
    void updateSimulationAllRows();
    void startClicked();
    void executeClicked();
    void resetClicked();
    void stopClicked();
    void chooseFileClicked();
    void updateCodeText(const QString &filePath);

private:
    Ui::MainWindow *ui;
    QWidget *mainWidget;
    QHBoxLayout *mainLayout;
    QTextEdit *codeTextEdit;
    QTextEdit* ramTextEdit;
    QVBoxLayout *ramLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    QTimer *timer;
    QPushButton *start;
    QPushButton *execute;
    QPushButton *stop;
    QPushButton *reset;
    QPushButton *chooseFile;
    QVBoxLayout *buttonsLayout;
    QProgressBar *progressBar;
    QGroupBox *codeGroupBox;
    QGroupBox *ramGroupBox;
    int currentRow;

    QVector<RAMSegment*> ramSegments;


    // New functions added based on refactoring
    void initializeButtons();
    QPushButton *createStyledButton(const QString &text, const QString &color, int fontSize = 10, QWidget *parent = nullptr);

    void initializeLayouts();
    void initializeGroupBoxes();
    QGroupBox *createStyledGroupBox(const QString &title, const QString &borderColor, const QString &backgroundColor, QWidget *parent = nullptr);
    void initializeTextEdit();
    void connectButtons();
    QString darkenColor(const QString &color);
    QString lightenColor(const QString &color);
    void disconnectSignalsAndSlots();
    void releaseResources();
    void setupRam(QVBoxLayout* ramLayout);
    void setup();
};

#endif // MAINWINDOW_H
