#pragma once

#include <QDir>
#include <QFileInfo>
#include <QFont>
#include <QStandardPaths>
#include <QString>

namespace Utils {

static Qt::CheckState checkState(int state)
{
    switch(state) {
    case -1: return Qt::PartiallyChecked; // System default
    case 1:  return Qt::Checked;
    case 0:
    default: return Qt::Unchecked;
    }
}

static int fromCheckState(Qt::CheckState state)
{
    switch(state) {
    case Qt::PartiallyChecked: return -1; // System default
    case Qt::Checked: return 1;
    case Qt::Unchecked:
    default: return 0;
    }
}
#if 0
static QFont fromName(const QString& fontName)
{
    QFont font;
    int const lastWhiteSpaceIndex = fontName.lastIndexOf(' ');
    QString fontFamily = fontName.mid(0, lastWhiteSpaceIndex);
    QString fontSizeStr = fontName.mid(lastWhiteSpaceIndex, fontName.length());
    bool ok;
    int fontSize = fontSizeStr.toInt(&ok);
    if (ok) {
        font.setFamily(fontFamily);
        font.setPointSize(fontSize);
    }
    return font;
}
#endif

static QStringList findThemes(const QString& themeDirName,
                              const QString& searchFilter,
                              const QString& searchFilter2 = QString(),
                              const QString& defaultValue  = QString())
{
    QStringList paths, themes, themesPaths;
    paths = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation);
    paths.removeDuplicates(); // QStandardPaths seems to add duplicates

    // $HOME/.themes - priority to local themes
    themesPaths.push_back(QString("%1%2%3").arg(std::getenv("HOME"), QStringLiteral("/."), themeDirName));

    // .local/share/themes:/usr/local/share/themes:/usr/share/themes
    for(const QString& path : std::as_const(paths)) {
        QString themesPath = path + '/' + themeDirName;
        themesPaths.push_back(themesPath);
    }
    for(const QString& themesPath : std::as_const(themesPaths)) {
        QDir themesDir(themesPath);
        QStringList themeEntries = themesDir.entryList(QDir::Dirs|QDir::NoDotAndDotDot);
        for (const QString& themeEntry : std::as_const(themeEntries)) {
            if (themeEntry == QStringLiteral("locolor") || themeEntry == QStringLiteral("hicolor"))
                continue;
            QString themePath = themesPath + '/' + themeEntry + '/' + searchFilter;
            if (QFileInfo::exists(themePath)) //TODO: && QFileInfo(themePath).isFile()) ?
                themes.push_back(themeEntry);
            if (!searchFilter2.isNull()) {
                QString themePath = themesPath + '/' + themeEntry + '/' + searchFilter2;
                if (QFileInfo::exists(themePath)) //TODO: && QFileInfo(themePath).isFile()) ?
                    themes.push_back(themeEntry);
            }
        }
    }
    themes.push_front(defaultValue);
    themes.removeDuplicates();
    return themes;
}
} // namespace Utils
