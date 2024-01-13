// mainwindow.cpp
#include "mainwindow.h"
#include "ramslot.h"

#include <QApplication>
#include <QMainWindow>
#include <QScreen>
#include <QRect>
#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QTextCursor>
#include <QTextBlock>
#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QFileDialog>
#include <QTimer>
#include <QFont>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentRow(0), timer(nullptr), start(nullptr),
      execute(nullptr), stop(nullptr), reset(nullptr), chooseFile(nullptr),
      progressBar(nullptr), codeGroupBox(nullptr), ramGroupBox(nullptr)
{
  QScreen *primaryScreen = QGuiApplication::primaryScreen();
  QRect screenGeometry = primaryScreen->availableGeometry();
  resize(screenGeometry.size());
  this->setStyleSheet("background-color: #343a40;");
//  this->setStyleSheet("background-color: #ffffff;");
  // Initialize UI components
  initializeButtons();
  initializeLayouts();
  initializeGroupBoxes();
  initializeTextEdit();

  // Set up connections
  connectButtons();
  setup();
  // Set the central widget
  setCentralWidget(mainWidget);

  // Connect the timer to update the simulation
  // (Note: This part might be incomplete since the timer creation and start
  // are not present here)
}

void MainWindow::initializeButtons()
{
    start = createStyledButton("EXECUTE 1 LINE", "#4CAF50", 14,  this);
    execute = createStyledButton("EXECUTE ALL LINES", "green", 14,  this);
    reset = createStyledButton("RESET", "yellow", 14, this);
    stop = createStyledButton("STOP", "red", 14, this);
    chooseFile = createStyledButton("Choose File", "forest", 14, this);
    progressBar = new QProgressBar(this);
    progressBar->setMinimum(0);
    progressBar->setValue(0);
}

QPushButton *MainWindow::createStyledButton(const QString &text, const QString &color, int fontSize, QWidget *parent)
{
    QPushButton *button = new QPushButton(text, parent);

    // Define the base style
    QString styleSheet = "QPushButton {"
                        "    background-color: " + color + ";"
                        "    color: white;"
                        "    padding: 8px 16px;"
                        "    border: 2px solid " + darkenColor(color) + ";" // Darken the border color
                        "    border-radius: 4px;"
                        "    font-size: " + QString::number(fontSize) + "px;"
                        "}";

    // Hover state
    styleSheet += "QPushButton:hover {"
                  "    background-color: " + lightenColor(color) + ";" // Lighten the background on hover
                  "}";

    // Pressed state
    styleSheet += "QPushButton:pressed {"
                  "    background-color: " + darkenColor(color) + ";" // Darken the background on press
                  "}";

    button->setStyleSheet(styleSheet);
    return button;
}

QString MainWindow::darkenColor(const QString &color)
{
    // Implement your own color darkening logic here
    // You can use QColor or other methods to manipulate the color
    // For simplicity, let's just make it a bit darker
    return color + "80"; // Adding "80" to the color code to make it darker
}

QString MainWindow::lightenColor(const QString &color)
{
    // Implement your own color lightening logic here
    // You can use QColor or other methods to manipulate the color
    // For simplicity, let's just make it a bit lighter
    return color + "80"; // Adding "80" to the color code to make it lighter
}

void MainWindow::initializeLayouts()
{
    mainWidget = new QWidget(this);
    mainLayout = new QHBoxLayout(mainWidget);
    buttonsLayout = new QVBoxLayout(mainWidget);
    leftLayout = new QVBoxLayout(mainWidget);
    rightLayout = new QVBoxLayout(mainWidget);

}

void MainWindow::initializeGroupBoxes()
{
    codeGroupBox = createStyledGroupBox("Code Layout", "#343a40", "#d35400", this);
    ramGroupBox = createStyledGroupBox("RAM Layout", "#343a40", "#87CEEB", this);
}
QGroupBox *MainWindow::createStyledGroupBox(const QString &title, const QString &borderColor, const QString &backgroundColor, QWidget *parent)
{
    QGroupBox *groupBox = new QGroupBox(title, parent);

    // Define the base style
    QString styleSheet = "QGroupBox {"
                        "    border: 2px solid " + borderColor + ";"
                        "    border-radius: 8px;"
                        "    margin-top: 1ex;"
                        "    background-color: " + backgroundColor + ";"
                        "    height: 100px;"
                        "}";

    // Add title style
    styleSheet += " QGroupBox::title {"
                  "    subcontrol-origin: margin;"
                  "    subcontrol-position: top center;"
                  "    top: 20px;" // Adjust the title position
                  "    color: " +
                  borderColor +
                  ";"
                  "    background-color: " +
                  backgroundColor +
                  ";"
                  "    padding: 0 10px;"
                  "    border: 2px solid " +
                  borderColor +
                  ";"
                  "    border-top-left-radius: 8px;"
                  "    border-top-right-radius: 8px;"
                  "    border-bottom-left-radius: 8px;"
                  "    border-bottom-right-radius: 8px;"
                  "}";

    groupBox->setStyleSheet(styleSheet);
    QFont titleFont;  // Get the current font
    titleFont.setPointSize(26);  // Set the font size
    groupBox->setFont(titleFont);// Apply the updated font

    return groupBox;
}


void MainWindow::initializeTextEdit()
{
    codeTextEdit = new QTextEdit(mainWidget);
    codeTextEdit->setTextColor("white");
    codeTextEdit->setPlainText("Line 1\nLine 2\nLine 3\nLine 4\nLine 5");

//    ramTextEdit = new QTextEdit(mainWidget);
//    ramTextEdit->setPlainText("Initialize RAM here");
}

void MainWindow::connectButtons()
{
    connect(stop, &QPushButton::clicked, this, &MainWindow::stopClicked);
    connect(reset, &QPushButton::clicked, this, &MainWindow::resetClicked);
    connect(execute, &QPushButton::clicked, this, &MainWindow::executeClicked);
    connect(start, &QPushButton::clicked, this, &MainWindow::startClicked);
    connect(chooseFile, &QPushButton::clicked, this, &MainWindow::chooseFileClicked);
}

void MainWindow::setup()
{
  buttonsLayout->addWidget(start);
  buttonsLayout->addWidget(execute);
  buttonsLayout->addWidget(reset);
  buttonsLayout->addWidget(stop);
  buttonsLayout->addWidget(chooseFile);
  leftLayout->addWidget(codeGroupBox);
  leftLayout->addWidget(codeTextEdit);
  leftLayout->addWidget(progressBar);
  rightLayout->addWidget(ramGroupBox);
//  rightLayout->addWidget(ramTextEdit);
  setupRam(rightLayout);
  mainLayout->addLayout(buttonsLayout);
  mainLayout->addLayout(leftLayout);
  mainLayout->addLayout(rightLayout);
}/*
void MainWindow::setupRam(QVBoxLayout* ramLayout)
{
  QGraphicsScene* ramScene = new QGraphicsScene(this);
  QGraphicsView* ramView = new QGraphicsView(ramScene);

  RAMSegment* stack = new RAMSegment("Stack", ramScene, this);
  RAMSegment* heap = new RAMSegment("Heap", ramScene, this);
//  RAMSegment* bss = new RAMSegment("BSS", ramScene, this);
//  RAMSegment* func = new RAMSegment("Function", ramScene, this);

  ramSegments.push_back(stack);
  ramSegments.push_back(heap);
  QScrollArea* ramScrollArea = new QScrollArea();
  ramScrollArea->setWidgetResizable(true);

  QWidget* ramWidget = new QWidget();
  QVBoxLayout *ramWidgetLayout = new QVBoxLayout(ramWidget);

  ramLayout->addLayout(stack->getLayout());
  ramLayout->addLayout(heap->getLayout());
//  ramLayout->addLayout(bss->getLayout());
//  ramLayout->addLayout(func->getLayout());
  ramScrollArea->setWidget(ramWidget);

  ramLayout->addWidget(ramView);
}*/
void MainWindow::setupRam(QVBoxLayout* ramLayout)
{
    QGraphicsScene* ramScene = new QGraphicsScene(this);

    RAMSegment* stack = new RAMSegment("Stack", ramScene, this);
    RAMSegment* heap = new RAMSegment("Heap", ramScene, this);
    RAMSegment* bss = new RAMSegment("BSS", ramScene, this);
    RAMSegment* func = new RAMSegment("Function", ramScene, this);

    ramSegments.push_back(stack);
    ramSegments.push_back(heap);

    // Create a scroll area
    QScrollArea* ramScrollArea = new QScrollArea();
    ramScrollArea->setWidgetResizable(true);

    // Create a widget to contain the QGraphicsView
    QWidget* ramWidget = new QWidget();
    QVBoxLayout* ramWidgetLayout = new QVBoxLayout(ramWidget);

    // Add RAM segments to the layout
    ramWidgetLayout->addLayout(stack->getLayout());
    ramWidgetLayout->addLayout(heap->getLayout());
    ramWidgetLayout->addLayout(bss->getLayout());
    ramWidgetLayout->addLayout(func->getLayout());

    // Set the widget as the scroll area's content
    ramScrollArea->setWidget(ramWidget);

    // Add the scroll area to the ram layout
    ramLayout->addWidget(ramScrollArea);
}

MainWindow::~MainWindow()
{
    disconnectSignalsAndSlots();
    releaseResources();
}

void MainWindow::disconnectSignalsAndSlots()
{
    disconnect(stop, &QPushButton::clicked, this, &MainWindow::stopClicked);
    disconnect(reset, &QPushButton::clicked, this, &MainWindow::resetClicked);
    disconnect(execute, &QPushButton::clicked, this, &MainWindow::executeClicked);
    disconnect(start, &QPushButton::clicked, this, &MainWindow::startClicked);
    disconnect(chooseFile, &QPushButton::clicked, this, &MainWindow::chooseFileClicked);

    if (timer) {
        disconnect(timer, &QTimer::timeout, this, nullptr);
    }
}

void MainWindow::releaseResources()
{
//    delete ui; // Release the UI resources

    // Release dynamically allocated buttons
    if (start) delete start;
    if (execute) delete execute;
    if (stop) delete stop;
    if (reset) delete reset;
    if (chooseFile) delete chooseFile;

    // Release dynamically allocated layouts
    if (mainLayout) delete mainLayout;
    if (buttonsLayout) delete buttonsLayout;
    if (leftLayout) delete leftLayout;
    if (rightLayout) delete rightLayout;

    // Release dynamically allocated progress bar
    if (progressBar) delete progressBar;

    // Release dynamically allocated group boxes
    if (codeGroupBox) delete codeGroupBox;
    if (ramGroupBox) delete ramGroupBox;

    // Release dynamically allocated text edits
    if (codeTextEdit) delete codeTextEdit;
//    if (ramTextEdit) delete ramTextEdit;

    // Release the timer resource, if applicable
    if (timer) {
        timer->stop();
        delete timer;
    }
    for (auto& slot : ramSegments) {
        if(slot) delete slot;
        slot = nullptr;
    }

    ramSegments.clear();

    // Set member variables to nullptr after deletion
    ui = nullptr;
    timer = nullptr;
    start = nullptr;
    execute = nullptr;
    stop = nullptr;
    reset = nullptr;
    chooseFile = nullptr;
    progressBar = nullptr;
    mainLayout = nullptr;
    buttonsLayout = nullptr;
    leftLayout = nullptr;
    rightLayout = nullptr;
    codeGroupBox = nullptr;
    ramGroupBox = nullptr;
    codeTextEdit = nullptr;
//    ramTextEdit = nullptr;
}

void MainWindow::startClicked()
{
    QPushButton *startButton = qobject_cast<QPushButton*>(sender());
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
void MainWindow::executeClicked()
{
  QPushButton *executeButton = qobject_cast<QPushButton*>(sender());
  executeButton->setDisabled(true);
  QStringList codeLines = codeTextEdit->toPlainText().split('\n');
  int initialInterval = (codeLines.isEmpty() || codeLines.first().trimmed().isEmpty()) ? 0 : 1000;

  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &MainWindow::updateSimulationAllRows);

  timer->start(initialInterval);

}
void MainWindow::updateSimulationAllRows()
{
  // Check if we reached the end of the code
      QStringList codeLines = codeTextEdit->toPlainText().split('\n');
      if (currentRow >= codeLines.size()) {
          timer->stop();
          execute->setDisabled(false);
          return;
      }
      progressBar->setMaximum(codeLines.size());
      // Update the left part (code)
      QTextCursor cursor(codeTextEdit->document());
      cursor.movePosition(QTextCursor::Start);

      for (int i = 0; i < currentRow; ++i) {
          QTextBlockFormat blockFormat;
              blockFormat.setBackground(QColor("#222222")); // Set the background color to #222222
              cursor.setBlockFormat(blockFormat);
              cursor.movePosition(QTextCursor::NextBlock);
      }
      QTextBlockFormat blockFormat;
      if (!cursor.block().text().trimmed().isEmpty()) {
          blockFormat.setBackground(QBrush(Qt::green));
          cursor.mergeBlockFormat(blockFormat);

          // Non-empty line, set regular timer interval
          timer->setInterval(1000);
      } else {
          // Empty line, set a shorter timer interval or no interval at all
          timer->setInterval(0); // Set to 0 or adjust as needed
      }
      currentRow++;
      progressBar->setValue(currentRow);
      // Update the right part (RAM simulation)

      ramSegments[0]->getLayout()->insertSpacing(currentRow, 1);
      codeTextEdit->setTextCursor(cursor);
      codeTextEdit->ensureCursorVisible();
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
    progressBar->setMaximum(codeLines.size());

    QTextCursor cursor(codeTextEdit->document());
    cursor.movePosition(QTextCursor::Start);
    for (int i = 0; i < currentRow; ++i) {
        cursor.movePosition(QTextCursor::NextBlock);
    }
    QTextBlockFormat blockFormat;
    blockFormat.setBackground(QBrush(Qt::green));
    cursor.mergeBlockFormat(blockFormat);
    currentRow++;
    progressBar->setValue(currentRow);

//    ramTextEdit->setPlainText("Update RAM content here for line " + QString::number(currentRow));
    success = true;
}

void MainWindow::resetClicked()
{
    // Reset the currentRow counter
    currentRow = 0;

    // Remove the green background from all lines
    QTextCursor cursor(codeTextEdit->document());
    cursor.movePosition(QTextCursor::Start);
    codeTextEdit->setTextCursor(cursor);
    QTextBlockFormat BlockFormat;  // Default block format (no background color)
    do {
        qDebug() << "do";
        BlockFormat.setBackground(QBrush("#343a40"));  // Set the background to the default color

        cursor.mergeBlockFormat(BlockFormat);

    } while (cursor.movePosition(QTextCursor::NextBlock));
    progressBar->setValue(0);
//    ramTextEdit->setPlainText("Initialize RAM here");
}
void MainWindow::stopClicked()
{
  if(timer && timer->isActive())
    {
      timer->stop();
    }
  // Enable the "Execute" button and "Reset" button
        execute->setEnabled(true);
        reset->setEnabled(true);
}
void MainWindow::chooseFileClicked()
{
  resetClicked();
  QString filePath = QFileDialog::getOpenFileName(this, "Choose File", QString(), "Text Files (*.cpp);;All Files (*)");
  if(!filePath.isEmpty()){
    updateCodeText(filePath);
  }

}
void MainWindow::updateCodeText(const QString &filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        codeTextEdit->setPlainText(in.readAll());
        file.close();
    }
}
