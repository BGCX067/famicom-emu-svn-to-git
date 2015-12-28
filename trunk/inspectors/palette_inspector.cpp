#include "palette_inspector.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>


Palette_Inspector::Palette_Inspector()
{
}

QGraphicsView*
Palette_Inspector::display_palette(QVector<QRgb> palette)
{
    const unsigned square_size = 40;
    const unsigned squares_per_row = 8;
    QGraphicsScene* scene = new QGraphicsScene;

    unsigned max_color_index = (unsigned) palette.size();
    for (unsigned color_index = 0; color_index < max_color_index; color_index++)
        {
        QGraphicsPixmapItem* p = new QGraphicsPixmapItem(create_square_pixmap(square_size, color_index, palette));
        unsigned item_row = color_index / squares_per_row;
        unsigned item_col = color_index % squares_per_row;
        unsigned col_width = square_size;
        unsigned row_height = square_size;
        p->setPos((double) item_col * col_width, (double) item_row * row_height);
        scene->addItem(p);
        }
    QGraphicsView* view = new QGraphicsView(scene);
    return view;
}


QPixmap
Palette_Inspector::create_square_pixmap(unsigned square_size, unsigned color_index, QVector<QRgb> palette)
{
    //Create a square, indexed-color QImage
    QImage square_image( QSize::QSize(square_size, square_size), QImage::Format_Indexed8);
    //Set palette
    square_image.setColorTable(palette);

    //Paint every pixel
    for (unsigned row = 0; row < square_size; row++)
        for (unsigned col = 0; col < square_size; col++)
            square_image.setPixel(row, col, color_index);

    //Convert to QPixmap and return
    return (QPixmap::fromImage(square_image));
}
