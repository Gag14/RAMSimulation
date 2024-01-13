#include "ramsegment.h"
#include "ramslot.h"
#include "mainwindow.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QVector>
#include <qstring.h>

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGroupBox>

RAMSegment::RAMSegment(const QString& title, QGraphicsScene* scene, QObject* parent)
  : QObject(parent), scene(scene)
{

          // Add RamSlots to the segment
//          for (int i = 0; i < 4; ++i) {
//              RAMSlot* ramSlot = new RAMSlot(0, 0, 50, 20, "Data " + QString::number(i));
//              layout->addWidget(ramSlot);
//              ramSlots.append(ramSlot);
//          }

          layout = new QVBoxLayout();
          // Add a widget containing the QGraphicsView and title
          QWidget* widget = new QWidget();
          QVBoxLayout* widgetLayout = new QVBoxLayout(widget);
          widgetLayout->addWidget(new QGraphicsView(scene));
          widgetLayout->addWidget(new QLabel(title));  // Use QLabel for the title
          widgetLayout->addWidget(new QLabel("Ram Slot"));
          widgetLayout->addWidget(new QLabel("Ram Slot"));
          widgetLayout->addWidget(new QLabel("Ram Slot"));
          widgetLayout->addWidget(new QLabel("Ram Slot"));
          widget->setStyleSheet("border: 2px solid gray; "
                                "border-radius: 5px; "
                                "padding: 5px;");


          layout->addWidget(widget);
}

QVBoxLayout* RAMSegment::getLayout() { return layout; }
void RAMSegment::addSlot(const QString& data)
{
    // Create a new RAMSlot instance
    RAMSlot* ramSlot = new RAMSlot(0, 0, 50, 20, data);

    // Add the RAMSlot to the list
    ramSlots.append(ramSlot);

    // Retrieve the QGraphicsTextItem associated with the RAMSlot
//    QGraphicsTextItem* textItem = ramSlot->getTextItem();

    // Add the text item to the layout
//    layout->addWidget(textItem);
}


RAMSegment::~RAMSegment()
{
  delete layout;
  delete scene;
}
//void RAMSegment::addSlot(const QString& address, const QString& variableType, const QString& variableName, const QString& variableSize)
//{
//  RAMSlot* slot = new RAMSlot(address, variableType, variableName, variableSize);
//  segmentContent.push_back(slot);
//  segment->addItem(slot->getlayout());
//}
//void RAMSegment::addSlot(RAMSlot* slot)
//{
//  segmentContent.push_back(slot);

//}
//int RAMSegment::slotCount() const
//{
//  return segmentContent.size();
//}
//void RAMSegment::setTitle(const QString& title)
//{
////  if(titleBox) delete titleBox;
//  titleBox = new QGroupBox(title, this);
//}
//QVBoxLayout* RAMSegment::getLayout()
//{
//  return segment;
//}
