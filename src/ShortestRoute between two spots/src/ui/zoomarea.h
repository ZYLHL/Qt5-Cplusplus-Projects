#ifndef ZOOMAREA_H
#define ZOOMAREA_H

#include "pch.hpp"

class ZoomArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit ZoomArea(QWidget *parent = nullptr);

signals:
    void zoomin();
    void zoomout();

protected:
    void wheelEvent(QWheelEvent * event) override;
};

#endif // ZOOMAREA_H
