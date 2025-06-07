//
// Created by Mihai Moldovan on 21.06.2024.
//

#ifndef SELECTABLE_PAINTER_GUI_H
#define SELECTABLE_PAINTER_GUI_H
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

class GUI: public QWidget {
public:

private:

};

#include <QWidget>
#include <QVector>
#include <QRect>
#include <QColor>

class ClickableShape {
public:
    ClickableShape(const QRect &rect, const QColor &color);

    bool contains(const QPoint &point) const;
    void draw(QPainter &painter) const;

private:
    QRect rect;
    QColor color;
};

class ClickableShapesWidget : public QWidget {
Q_OBJECT

public:
    ClickableShapesWidget(QWidget *parent = nullptr);
    ~ClickableShapesWidget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QVector<ClickableShape> shapes;
};


#endif //SELECTABLE_PAINTER_GUI_H
