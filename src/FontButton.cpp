/*
    Copyright (C) 2013 - 2015  Hong Jen Yee (PCMan) <pcman.tw@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "FontButton.hpp"
#include <QFontDialog>

FontButton::FontButton(QWidget* parent): QPushButton(parent)
{
    connect(this, &QPushButton::clicked, this, &FontButton::onClicked);
}

FontButton::~FontButton()
{
}

void FontButton::onClicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok)
        setFont(font);
}

void FontButton::setFont(const QFont& font)
{
    font_ = font;
    QString text = font.family();

    if (font.bold()) {
        text += QStringLiteral(" Bold");
    }
    if (font.italic()) {
        text += QStringLiteral(" Italic");
    }
    text += QStringLiteral(" %1").arg(font.pointSize());
    setText(text);

    Q_EMIT fontChanged(font);
}
