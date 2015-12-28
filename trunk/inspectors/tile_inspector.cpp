#include "tile_inspector.h"
#include "data_bus/ppu/ppu_data_bus.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>

Tile_Inspector::Tile_Inspector(PPU_Data_Bus* _bus) : bus(_bus)
{
}

QGraphicsView*
Tile_Inspector::display_tiles(QVector<QRgb> palette)
{
    unsigned square_size = 8;
    const unsigned squares_per_row = 16;
    QGraphicsScene* scene = new QGraphicsScene;

    unsigned max_tile_index = 512;
    unsigned scale_factor = 4;
    square_size *= scale_factor;
    for (unsigned tile_index = 0; tile_index < max_tile_index; tile_index++)
        {        
        QGraphicsPixmapItem* p = new QGraphicsPixmapItem(create_tile_pixmap(tile_index, palette, scale_factor));
        unsigned item_row = tile_index / squares_per_row;
        unsigned item_col = tile_index % squares_per_row;
        unsigned col_width = square_size;
        unsigned row_height = square_size;
        p->setPos((double) item_col * col_width, (double) item_row * row_height);
        scene->addItem(p);
        }
    QGraphicsView* view = new QGraphicsView(scene);
    return view;
}


QPixmap
Tile_Inspector::create_tile_pixmap(unsigned tile_number, QVector<QRgb> palette, unsigned scale_factor)
{
    unsigned tile_size = 8;

    //Create a square, indexed-color QImage
    QImage tile_image( QSize::QSize(tile_size, tile_size), QImage::Format_Indexed8);
    //Set palette
    tile_image.setColorTable(palette);

    const unsigned tile_bytesize = 16;

    //Paint every pixel
    for (unsigned row = 0; row < tile_size; row++)
    {
        unsigned patt_addr = (tile_number * tile_bytesize) + row;
        unsigned char patt_msb = bus->read(patt_addr);
        unsigned char patt_lsb = bus->read(patt_addr + 8);

        for (unsigned col = 0; col < tile_size; col++)
        {
            unsigned char pixel_color_msb = (patt_msb >> (7 - col)) & 0x1;
            unsigned char pixel_color_lsb = (patt_lsb >> (7 - col)) & 0x1;
            unsigned char pixel_color = (pixel_color_msb << 1) | pixel_color_lsb;
            tile_image.setPixel(col, row, pixel_color + 24);
        }

    }

    //Convert to QPixmap and return
    return (QPixmap::fromImage(tile_image.scaled(tile_size * scale_factor, tile_size * scale_factor)));
}
