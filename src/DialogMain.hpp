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

    Qt::CheckState checkState(int);
    int            fromCheckState(Qt::CheckState);

    QFont fromName(const QString&);

    QStringList findThemes(
        const QString& themeDirName, const QString& searchFilter,
        const QString& searchFilter2 = QString(), const QString& defaultValue = QString()
    ) const;

    Settings* settings_;
};

