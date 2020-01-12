#include "zoomarea.h"

ZoomArea::ZoomArea(QWidget *parent) : QScrollArea(parent) {}

void ZoomArea::wheelEvent(QWheelEvent *event) {
    emit event->delta() > 0 ? zoomin() : zoomout();
}
