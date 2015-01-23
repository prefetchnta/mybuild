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

#include <QDebug>
#include <QUiLoader>
#include <QFileDialog>
#include <QMessageBox>

#include "exportwindow.h"
#include <stdio.h>

ExportWindow::ExportWindow()
{
	setupUi(this);
	linDestPath->setText(QDir::toNativeSeparators(QDir::homePath()));
	
	connect(btnCancel, SIGNAL( clicked( bool )), SLOT(quit_now()));
	connect(btnOK, SIGNAL( clicked( bool )), SLOT(process()));
	connect(btnDestPath, SIGNAL( clicked( bool )), SLOT(get_directory()));
}

ExportWindow::~ExportWindow()
{
	
}

void ExportWindow::quit_now()
{
	close();
}

void ExportWindow::get_directory()
{
	QString directory;
	QFileDialog fdialog;
	
	fdialog.setFileMode(QFileDialog::Directory);
	
	if(fdialog.exec()) {
		directory = fdialog.selectedFiles().at(0);
	} else {
		return;
	}
	
	linDestPath->setText(QDir::toNativeSeparators(directory));
}

void ExportWindow::process()
{
	QString fileName;
	QString dataString;
	QString suffix;
	int lines, i, j, inputpos, datalen;
	
	lines = output_data.count(QChar('\n'), Qt::CaseInsensitive);
	inputpos = 0;
	
	switch(cmbFileFormat->currentIndex()) {
		case 0: suffix = ".png"; break;
		case 1: suffix = ".eps"; break;
		case 2: suffix = ".svg"; break;
	}
	
	for(i = 0; i < lines; i++) {
		datalen = 0;
		for(j = inputpos; ((output_data[j] != '\n') && (j < output_data.length())); j++) {
			datalen++;
		}
		dataString = output_data.mid(inputpos, datalen);
		switch(cmbFileName->currentIndex()) {
			case 0: { /* Same as Data (URL Escaped) */
					QString url_escaped;
					int m;
					char name_char;
					QChar name_qchar;
					
					for(m = 0; m < dataString.length(); m++) {
						name_qchar = dataString[m];
						name_char = name_qchar.toAscii();
						
						switch(name_char) {
							case '\\': url_escaped += "%5C"; break;
							case '/': url_escaped += "%2F"; break;
							case ':': url_escaped += "%3A"; break;
							case '*': url_escaped += "%2A"; break;
							case '?': url_escaped += "%3F"; break;
							case '"': url_escaped += "%22"; break;
							case '<': url_escaped += "%3C"; break;
							case '>': url_escaped += "%3E"; break;
							case '|': url_escaped += "%7C"; break;
							case '%': url_escaped += "%25"; break;
							default: url_escaped += name_qchar; break;
						}
					}
					fileName = linDestPath->text() + QDir::separator() + linPrefix->text() + url_escaped + suffix;
				}
				break;
			case 1: { /* Formatted Serial Number */
					QString biggest, this_val, outnumber;
					int number_size, val_size, m;
					
					biggest = QString::number(lines + 1);
					number_size = biggest.length();
					this_val = QString::number(i + 1);
					val_size = this_val.length();
					
					for(m = 0; m < (number_size - val_size); m++) {
						outnumber += QChar('0');
					}
					
					outnumber += this_val;
					
					fileName = linDestPath->text() + QDir::separator() + linPrefix->text() + outnumber + suffix;
				}
				break;
		}
		barcode->bc.setText(dataString.toAscii().data());
		barcode->bc.save_to_file(fileName.toAscii().data());
		inputpos += datalen + 1;
	}
	close();
}