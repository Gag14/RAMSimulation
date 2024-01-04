#include "ramslot.h"


#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
//#include <QGraphicsTextItemWidget>
RAMSlot::RAMSlot(qreal x, qreal y, qreal width, qreal height, const QString& data)
  : QGraphicsRectItem(x, y, width, height),
    textItem(new QGraphicsTextItem(data, this))
{
  // Customize the appearance of the slot
  setBrush(QBrush(Qt::lightGray));
  textItem->setPos(x + 5, y + 5); // Adjust text position within the slot
}
QGraphicsTextItem* RAMSlot::getLayout() { return textItem; }

RAMSlot::~RAMSlot()
{
  delete textItem;
}
