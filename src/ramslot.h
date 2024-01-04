#ifndef RAMSLOT_H
#define RAMSLOT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
//#include <QGraphicsTextItemWidget>
class RAMSlot : public QGraphicsRectItem
{


public:
    RAMSlot(qreal x, qreal y, qreal width, qreal height, const QString& data);
    virtual QGraphicsTextItem* getLayout();
//    QGraphicsTextItem *getTextItem();
//    QGraphicsTextItemWidget* getWidget() const;
    ~RAMSlot();
private:
    QGraphicsTextItem* textItem;
};

#endif // RAMSLOT_H

