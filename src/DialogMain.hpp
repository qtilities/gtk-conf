/*
    SPDX-FileCopyrightText:  2024 Andrea Zanellato <redtid3@gmail.com> and Qtilities team
    SPDX-License-Identifier: GPL-2.0-only

    This file is part of the gtk-conf application project,
    see AUTHORS and COPYING files for further details.
*/
#pragma once

#include "ui_DialogMain.h"

#include <QDialog>

class Settings;

class DialogMain : public QDialog, private Ui::DialogMain
{
    Q_OBJECT

public:
    explicit DialogMain(QWidget* parent = nullptr);
    ~DialogMain();
    
private:
    void updateUi();
    void setupToolTips() ;
    void setupToolTipsGSettings();

    Settings* settings_;
};

