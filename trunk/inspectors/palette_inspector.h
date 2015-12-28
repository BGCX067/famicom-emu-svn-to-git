#ifndef PALETTE_INSPECTOR_H
#define PALETTE_INSPECTOR_H

#include <QVector>
#include <QRgb>

class QGraphicsView;
class QPixmap;

class Palette_Inspector
{
public:
    Palette_Inspector();
    QGraphicsView* display_palette(QVector<QRgb> palette);

private:
    QPixmap create_square_pixmap(unsigned square_size, unsigned color, QVector<QRgb> palette);
};

#endif // PALETTE_INSPECTOR_H
