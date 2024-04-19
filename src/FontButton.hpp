/*
 * Copyright (C) 2013 - 2015  Hong Jen Yee (PCMan) <pcman.tw@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
#pragma once

#include <QPushButton>

class FontButton : public QPushButton
{
    Q_OBJECT

public:
    explicit FontButton(QWidget* parent = nullptr);
    ~FontButton() override;

    QFont font() { return font_; }

    void setFont(const QFont&);

Q_SIGNALS:
    void fontChanged(const QFont&);

private Q_SLOTS:
    void onClicked();

private:
    QFont font_;
};
