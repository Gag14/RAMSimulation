// mainwindow.cpp
#include "mainwindow.h"
#include <QApplication>
//#include <QDesktopWidget>
#include <QMainWindow>
#include <QScreen>
#include <QRect>
#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      currentRow(0)
{
  QScreen *primaryScreen = QGuiApplication::primaryScreen();
  QRect screenGeometry = primaryScreen->availableGeometry();
  resize(screenGeometry.size());
  // Create the main widget and layout
  start = new QPushButton("START");
  connect(start, &QPushButton::clicked, this, &MainWindow::startClicked);
  mainWidget = new QWidget(this);
  mainLayout = new QHBoxLayout(mainWidget);
  start->setParent(mainWidget);
  start->move(mainLayout->sizeHint().width()/2, 0);
  mainLayout->addWidget(start);
  // Left part (code)
  leftLayout = new QVBoxLayout();
  QSize layoutsSize(mainLayout->sizeHint().width(), mainLayout->sizeHint().height());

  codeTextEdit = new QTextEdit(mainWidget);
  codeTextEdit->setPlainText("Line 1\nLine 2\nLine 3\nLine 4\nLine 5");

  mainLayout->addWidget(codeTextEdit);

  // Right part (RAM simulation)
  rightLayout = new QVBoxLayout();
  ramTextEdit = new QTextEdit(mainWidget);
  ramTextEdit->setPlainText("Initialize RAM here");
//  mainLayout->addWidget(ramTextEdit);
  leftLayout->addWidget(codeTextEdit);
  rightLayout->addWidget(ramTextEdit);

//  leftLayout->SetMinimumSize(layoutsSize);
  mainLayout->addLayout(leftLayout);
  mainLayout->addLayout(rightLayout);
  setCentralWidget(mainWidget);

  // Connect the timer to update the simulation
}

MainWindow::~MainWindow()
{
    delete mainWidget;
    delete mainLayout;
    delete codeTextEdit;
    delete ramTextEdit;
}
void MainWindow::startClicked()
{
    QPushButton *startButton = qobject_cast<QPushButton*>(sender());
    qDebug() << startButton->windowTitle();
    startButton->setDisabled(true);

    bool success = false;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this, startButton, &success]() {
        updateSimulation(success);
        startButton->setEnabled(true);  // Re-enable the button after the timer completes
        timer->stop();  // Stop the timer
        timer->deleteLater();  // Delete the timer object
    });

    timer->start(1000);  // Start the timer

    // Note: Avoid deleting the timer here as it will not allow the timer to complete its work.
    // delete timer;
}

void MainWindow::updateSimulation(bool& success)
{
    // Check if we reached the end of the code
    QStringList codeLines = codeTextEdit->toPlainText().split('\n');
    if (currentRow >= codeLines.size()) {
        timer->stop();
        return;
    }

    // Update the left part (code)
    QTextCursor cursor(codeTextEdit->document());
    cursor.movePosition(QTextCursor::Start);
    for (int i = 0; i < currentRow; ++i) {
        cursor.movePosition(QTextCursor::NextBlock);
    }
    QTextBlockFormat blockFormat;
    blockFormat.setBackground(QBrush(Qt::green));
    cursor.mergeBlockFormat(blockFormat);
    currentRow++;

    // Update the right part (RAM simulation)
    // You can customize this part based on the logic of your simulation
    ramTextEdit->setPlainText("Update RAM content here for line " + QString::number(currentRow));
    success = true;
}
