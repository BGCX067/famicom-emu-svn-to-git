#ifndef TILE_INSPECTOR_H
#define TILE_INSPECTOR_H

#include <QVector>
#include <QRgb>

class QGraphicsView;
class QPixmap;
class PPU_Data_Bus;

class Tile_Inspector
{
public:
    Tile_Inspector(PPU_Data_Bus* bus);
    QGraphicsView* display_tiles(QVector<QRgb> palette);
private:
    QPixmap create_tile_pixmap(unsigned tile_number, QVector<QRgb> palette, unsigned scale_factor);

private:
    PPU_Data_Bus*   bus;
};

#endif // TILE_INSPECTOR_H
