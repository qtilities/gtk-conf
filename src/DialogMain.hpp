#pragma once

#include <QDialog>

namespace Ui {
class DialogMain;
}
class Settings;

class DialogMain : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogMain(QWidget* parent = nullptr);
    ~DialogMain();
    
private:
    void updateUi();

    // TODO: Probably to remove if using gsettings
#if 0
    Qt::CheckState checkState(int);
    int            fromCheckState(Qt::CheckState);
#endif
    QFont fromName(const QString&);

    QStringList findThemes(
        const QString& themeDirName, const QString& searchFilter,
        const QString& searchFilter2 = QString(), const QString& defaultValue = QString()
    ) const;

    Ui::DialogMain* ui;
    Settings* settings;
};

