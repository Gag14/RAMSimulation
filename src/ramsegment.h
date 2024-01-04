#ifndef RAMSEGMENT_H
#define RAMSEGMENT_H

#include "ramslot.h"


#include <QWidget>
#include <QVBoxLayout>
#include <QVector>
#include <qstring.h>
#include <QGroupBox>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>

class RAMSegment : public QObject
{
  Q_OBJECT
public:
  RAMSegment(const QString& title, QGraphicsScene* scene, QObject* parent = nullptr);
//  explicit RAMSegment(QWidget *parent, const QString& title);
  ~RAMSegment();
  void addSlot(const QString& address, const QString& variableType, const QString& variableName, const QString& variableSize);
  void addSlot(const QString& data);
  int slotCount() const;
  void setTitle(const QString& title);
  QVBoxLayout* getLayout();
private:
  QVBoxLayout* layout;
  QList<RAMSlot*> ramSlots;
  QGraphicsScene *scene;
signals:

};

#endif // RAMSEGMENT_H
