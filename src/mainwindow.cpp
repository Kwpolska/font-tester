/*
 * Font Tester v0.1.0
 * Copyright © 2016-2017, Chris Warrick.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions, and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the author of this software nor the names of
 *    contributors to this software may be used to endorse or promote
 *    products derived from this software without specific prior written
 *    consent.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QFont f = ui->fontBox->currentFont();
    f.setPointSize(ui->sizeBox->currentText().toInt());
    ui->editor->setFont(f);

    ui->boldBtn->setDefaultAction(ui->actionBold);
    ui->italicBtn->setDefaultAction(ui->actionItalic);
    ui->selectFontBtn->setDefaultAction(ui->actionSelectFont);
}

MainWindow::~MainWindow() {
    delete ui;
}

QFont MainWindow::getFont() {
    QPlainTextEdit *editor = this->findChild<QPlainTextEdit *>("editor");
    return editor->font();
}

void MainWindow::setFont(const QFont &f) {
    QFontComboBox *fontBox = this->findChild<QFontComboBox *>("fontBox");
    QAction *actionBold = this->findChild<QAction *>("actionBold");
    QAction *actionItalic = this->findChild<QAction *>("actionItalic");

    fontBox->setCurrentFont(f);
    actionBold->setChecked(f.bold());
    actionItalic->setChecked(f.italic());

    QComboBox *sizeBox = this->findChild<QComboBox *>("sizeBox");
    sizeBox->setCurrentText(QString::number(f.pointSize()));
}

void MainWindow::on_fontBox_currentFontChanged(const QFont &f) {
    QPlainTextEdit *editor = this->findChild<QPlainTextEdit *>("editor");
    editor->setFont(f);
}

void MainWindow::on_sizeBox_editTextChanged(const QString &arg1) {
    QFont f = this->getFont();
    f.setPointSize(arg1.toInt());
    this->setFont(f);
}

void MainWindow::on_actionBold_triggered(bool checked) {
    QFont f = this->getFont();
    f.setBold(checked);
    this->setFont(f);
}

void MainWindow::on_actionItalic_triggered(bool checked) {
    QFont f = this->getFont();
    f.setItalic(checked);
    this->setFont(f);
}

void MainWindow::on_actionSelectFont_triggered() {
    QFont oldFont = this->getFont();
    bool ok;
    QFont newFont = QFontDialog::getFont(&ok, oldFont, this);
    if (ok) {
        this->setFont(newFont);
    }
}
