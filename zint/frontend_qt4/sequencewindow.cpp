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
#include <QFile>
#include <QUiLoader>
#include <QFileDialog>
#include <QMessageBox>

#include "sequencewindow.h"
#include "exportwindow.h"
#include <stdio.h>

SequenceWindow::SequenceWindow()
{
	setupUi(this);
	QValidator *intvalid = new QIntValidator(this);
	
	linStartVal->setValidator(intvalid);
	linEndVal->setValidator(intvalid);
	linIncVal->setValidator(intvalid);
	connect(btnClose, SIGNAL( clicked( bool )), SLOT(quit_now()));
	connect(btnReset, SIGNAL( clicked( bool )), SLOT(reset_preview()));
	connect(btnCreate, SIGNAL( clicked( bool )), SLOT(create_sequence()));
	connect(txtPreview, SIGNAL( textChanged()), SLOT(check_generate()));
	connect(btnImport, SIGNAL( clicked( bool )), SLOT(import()));
	connect(btnExport, SIGNAL( clicked( bool )), SLOT(generate_sequence()));
}

SequenceWindow::~SequenceWindow()
{
}

void SequenceWindow::quit_now()
{
	close();
}

void SequenceWindow::reset_preview()
{
	txtPreview->clear();
}

QString SequenceWindow::apply_format(QString raw_number)
{
	QString adjusted, reversed;
	QString format;
	int format_len, input_len, i, inpos;
	char format_char;
	QChar format_qchar;
	
	format = linFormat->text();
	input_len = raw_number.length();
	format_len = format.length();
	
	inpos = input_len;
	
	for(i = format_len; i > 0; i--) {
		format_qchar = format[i - 1];
		format_char = format_qchar.toAscii();
		switch(format_char) {
			case '#':
				if (inpos > 0) {
					adjusted += raw_number[inpos - 1];
					inpos--;
				} else {
					adjusted += ' ';
				}
				break;
			case '$':
				if (inpos > 0) {
					adjusted += raw_number[inpos - 1];
					inpos--;
				} else {
					adjusted += '0';
				}
				break;
			case '*':
				if (inpos > 0) {
					adjusted += raw_number[inpos - 1];
					inpos--;
				} else {
					adjusted += '*';
				}
				break;
			default:
				adjusted += format_char;
				break;
		}
	}
	
	for(i = format_len; i > 0; i--) {
		reversed += adjusted[i - 1];
	}
	
	return reversed;
}

void SequenceWindow::create_sequence()
{
	QString startval, endval, incval, part, outputtext;
	int start, stop, step, i;
	bool ok;
	
	startval = linStartVal->text();
	endval = linEndVal->text();
	incval = linIncVal->text();
	start = startval.toInt(&ok, 10);
	stop = endval.toInt(&ok, 10);
	step = incval.toInt(&ok, 10);
	
	if((stop <= start) || (step <= 0)) {
		QMessageBox::critical(this, tr("Sequence Error"), tr("One or more of the input values is incorrect."));
		return;
	}
	
	for(i = start; i <= stop; i += step) {
		part = apply_format(QString::number(i, 10));
		part += '\n';
		outputtext += part;
	}
	
	txtPreview->setPlainText(outputtext);
}

void SequenceWindow::check_generate()
{
	QString preview_copy;
	
	preview_copy = txtPreview->toPlainText();
	if(preview_copy.isEmpty()) {
		btnExport->setEnabled(false);
	} else {
		btnExport->setEnabled(true);
	}
}

void SequenceWindow::import()
{
	//QString fileName;
	//QFileDialog fdialog;
	QFile file;
	QString selectedFilter;
	
	//fdialog.setFileMode(QFileDialog::ExistingFile);
	
	//if(fdialog.exec()) {
	//	fileName = fdialog.selectedFiles().at(0);
	//} else {
	//	return;
	//}

	QString fileName = QFileDialog::getOpenFileName(this,
                                 tr("Import File"),
                                 "./",
                                 tr("All Files (*);;Text Files (*.txt)"));
     if (fileName.isEmpty())
         return;
	
	file.setFileName(fileName);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::critical(this, tr("Open Error"), tr("Could not open selected file."));
		return;
	}

	QByteArray outstream = file.readAll();

	txtPreview->setPlainText(QString(outstream));
	file.close();
}

void SequenceWindow::generate_sequence()
{
	int returnval;
	
	ExportWindow dlg;
	dlg.barcode = barcode;
	dlg.output_data = txtPreview->toPlainText();
	returnval = dlg.exec();
}
