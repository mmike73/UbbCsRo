//
// Created by Mihai Moldovan on 21.06.2024.
//

#include "gui.h"


ClickableShape::ClickableShape(const QRect &rect, const QColor &color)
        : rect(rect), color(color) {}

bool ClickableShape::contains(const QPoint &point) const {
    return rect.contains(point);
}

void ClickableShape::draw(QPainter &painter) const {
    painter.setBrush(QBrush(color));
    painter.drawRect(rect);
}

ClickableShapesWidget::ClickableShapesWidget(QWidget *parent)
        : QWidget(parent) {
    shapes.append(ClickableShape(QRect(10, 10, 100, 100), Qt::red));
    shapes.append(ClickableShape(QRect(120, 10, 100, 100), Qt::green));
    shapes.append(ClickableShape(QRect(230, 10, 100, 100), Qt::blue));
}

ClickableShapesWidget::~ClickableShapesWidget() {}

void ClickableShapesWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    for (const auto &shape : shapes) {
        shape.draw(painter);
    }
}

void ClickableShapesWidget::mousePressEvent(QMouseEvent *event) {
    for (const auto &shape : shapes) {
        if (shape.contains(event->pos())) {
            qDebug() << "Shape clicked at:" << event->pos().x();
            // Handle shape click event
        }
    }
}
