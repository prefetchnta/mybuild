/*
    Zint Barcode Generator - the open source barcode generator
    Copyright (C) 2009 Robin Stuart <robin@zint.org.uk>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef EXPORTWINDOW_H
#define EXPORTWINDOW_H

#include "ui_extExport.h"
#include "barcodeitem.h"

class ExportWindow : public QDialog, private Ui::ExportDialog
{
	Q_OBJECT

public:
	ExportWindow();
	~ExportWindow();
	BarcodeItem *barcode;
	QString output_data;

private slots:
	void quit_now();
	void process();
	void get_directory();
};

#endif