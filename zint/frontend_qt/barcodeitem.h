/***************************************************************************
 *   Copyright (C) 2008 by BogDan Vatra                                    *
 *   bogdan@licentia.eu                                                    *
 *   Copyright (C) 2009-2023 by Robin Stuart <rstuart114@gmail.com>        *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/
/* vim: set ts=4 sw=4 et : */

#ifndef BARCODEITEM_H
#define BARCODEITEM_H

#include <QGraphicsItem>
#include <qzint.h>

/**
 @author BogDan Vatra <taipan@licentia.eu>
*/

class BarcodeItem : public QGraphicsItem
{
public:
    BarcodeItem();
    ~BarcodeItem();

    void setSize(int width, int height);
    void setColor(const QColor& color); /* Set colour of bounding rect */
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    int w, h;
    QColor m_color;

public:
    mutable Zint::QZint bc;
};

#endif
