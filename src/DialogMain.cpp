#include "DialogMain.hpp"
#include "DialogAbout.hpp"
#include "ui_DialogMain.h"
#include "Settings.hpp"

#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QStandardPaths>

DialogMain::DialogMain(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogMain)
    , settings(new Settings(this))
{
#define ENABLE_BUTTONS \
    reset->setEnabled(true); \
    save->setEnabled(true)

#define DISABLE_BUTTONS \
    reset->setEnabled(false); \
    save->setEnabled(false)

    ui->setupUi(this);
    ui->list->setFixedWidth(ui->list->sizeHintForColumn(0) + 2 * ui->list->frameWidth());
    ui->cbxCursorThemeName->addItems(findThemes(QStringLiteral("icons"), QStringLiteral("cursors")));
    ui->cbxIconThemeName->addItems(findThemes(QStringLiteral("icons"), QStringLiteral("16x16"), QStringLiteral("scalable"), QStringLiteral("Adwaita")));
    ui->cbxThemeName->addItems(findThemes(QStringLiteral("themes"), QStringLiteral("/gtk-3.0/gtk.css"), QStringLiteral("Default")));

    QPushButton* reset = ui->buttonBox->button(QDialogButtonBox::Reset);
    QPushButton* save  = ui->buttonBox->button(QDialogButtonBox::Save);
    DISABLE_BUTTONS;

    settings->load();
    connect(settings, &Settings::propertiesChanged, [this, reset, save](){
        QMessageBox::warning(this, tr("Settings changed"),
            tr("Settings was changed by a different application.\n\n"
               "You can reload the new settings by pressing the Reset button"
               "or use Save if you want to keep the current ones.")
            );
        ENABLE_BUTTONS;
    });
    updateUi();

#define CONNECT_CHECKBOX(NAME) \
    connect(ui->chk##NAME, &QCheckBox::toggled, [this, reset, save]() { \
        settings->set##NAME(ui->chk##NAME->isChecked()); \
        ENABLE_BUTTONS; \
    })
#if 0
#define CONNECT_CHECKBOX_TRISTATE(NAME) \
    connect(ui->chk##NAME, &QCheckBox::clicked, [this, reset, save]() { \
        settings->set##NAME(fromCheckState(ui->chk##NAME->checkState())); \
        ENABLE_BUTTONS; \
    })
#endif
#define CONNECT_COMBOBOX(NAME) \
    connect(ui->cbx##NAME, &QComboBox::currentTextChanged, [this, reset, save]() { \
        settings->set##NAME(ui->cbx##NAME->currentText()); \
        ENABLE_BUTTONS; \
    })
#define CONNECT_SPINBOX(NAME) \
    connect(ui->sbx##NAME, QOverload<int>::of(&QSpinBox::valueChanged), \
            [this, reset, save] { \
                settings->set##NAME(ui->sbx##NAME->value()); \
                ENABLE_BUTTONS; \
            })
    connect(ui->gbxEnableRecentFiles, &QGroupBox::toggled, [this, reset, save]() { \
        settings->setEnableRecentFiles(ui->gbxEnableRecentFiles->isChecked()); \
        ENABLE_BUTTONS;
    });
    connect(ui->fbnDefaultFont, &FontButton::changed, [this, reset, save]() { \
        settings->setFontName(ui->fbnDefaultFont->text()); \
        ENABLE_BUTTONS;
    });
    connect(reset, &QPushButton::clicked, [this, reset, save]() {
        settings->load();
        updateUi();
        DISABLE_BUTTONS;
    });
    connect(ui->buttonBox, &QDialogButtonBox::accepted, [this, reset, save]() {
        settings->save();
        DISABLE_BUTTONS;
    });
    connect(ui->pbnAbout, &QPushButton::clicked, [this](){
        Qtilities::DialogAbout about;
        about.exec();
    });
    CONNECT_CHECKBOX(EnableEventSounds);
    CONNECT_CHECKBOX(EnableInputFeedbackSounds);
    CONNECT_CHECKBOX(OverlayScrolling);
#if 0
    CONNECT_CHECKBOX(PreferDarkTheme);
    CONNECT_CHECKBOX(WarpSlider);
    CONNECT_CHECKBOX_TRISTATE(XftAntialias);
    CONNECT_CHECKBOX_TRISTATE(XftHinting);
#endif
    CONNECT_COMBOBOX(ColorScheme);
    CONNECT_COMBOBOX(CursorThemeName);
    CONNECT_COMBOBOX(FontAntialiasing);
    CONNECT_COMBOBOX(IconThemeName);
    CONNECT_COMBOBOX(ThemeName);
    CONNECT_COMBOBOX(XftHintStyle);
    CONNECT_COMBOBOX(XftRgba);
    CONNECT_SPINBOX(CursorThemeSize);
    CONNECT_SPINBOX(RecentFilesMaxAge);

#undef CONNECT_CHECKBOX
#undef CONNECT_CHECKBOX_TRISTATE
#undef CONNECT_COMBOBOX
#undef CONNECT_SPINBOX
#undef DISABLE_BUTTONS
#undef ENABLE_BUTTONS
}

DialogMain::~DialogMain()
{
    delete ui;
}

void DialogMain::updateUi()
{
    ui->cbxColorScheme->setCurrentText(settings->colorScheme());
//  ui->chkPreferDarkTheme->setChecked(settings->preferDarkTheme());
    ui->cbxCursorThemeName->setCurrentText(settings->cursorThemeName());
    ui->sbxCursorThemeSize->setValue(settings->cursorThemeSize());
    ui->chkEnableEventSounds->setChecked(settings->enableEventSounds());
    ui->chkEnableInputFeedbackSounds->setChecked(settings->enableInputFeedbackSounds());
    ui->cbxFontAntialiasing->setCurrentText(settings->fontAntialiasing());
    ui->fbnDefaultFont->setFont(fromName(settings->fontName()));
    ui->cbxIconThemeName->setCurrentText(settings->iconThemeName());
    ui->chkOverlayScrolling->setChecked(settings->overlayScrolling());
//  ui->chkWarpSlider->setChecked(settings->warpSlider());
    ui->gbxEnableRecentFiles->setChecked(settings->enableRecentFiles());
    ui->sbxRecentFilesMaxAge->setValue(settings->recentFilesMaxAge());
    ui->cbxThemeName->setCurrentText(settings->themeName());
//  ui->chkXftAntialias->setCheckState(checkState(settings->xftAntialias()));
//  ui->chkXftDpi_->setCheckState(checkState(settings->xftDpi()));
//  ui->chkXftHinting->setCheckState(checkState(settings->xftHinting()));
    ui->cbxXftHintStyle->setCurrentText(settings->xftHintStyle());
    ui->cbxXftRgba->setCurrentText(settings->xftRgba());
}
#if 0
Qt::CheckState DialogMain::checkState(int state)
{
    switch(state) {
    case -1: return Qt::PartiallyChecked; // System default
    case 1:  return Qt::Checked;
    case 0:
    default: return Qt::Unchecked;
    }
}

int DialogMain::fromCheckState(Qt::CheckState state)
{
    switch(state) {
    case Qt::PartiallyChecked: return -1; // System default
    case Qt::Checked: return 1;
    case Qt::Unchecked:
    default: return 0;
    }
}
#endif
QFont DialogMain::fromName(const QString& fontName)
{
    QFont font;
    int const lastWhiteSpaceIndex = fontName.lastIndexOf(' ');
    QString fontFamily = fontName.mid(0, lastWhiteSpaceIndex);
    QString fontSizeStr = fontName.mid(lastWhiteSpaceIndex, fontName.length());
    bool ok;
    int fontSize = fontSizeStr.toInt(&ok, 10);
    if (ok) {
        font.setFamily(fontFamily);
        font.setPointSize(fontSize);
    }
    return font;
}

QStringList DialogMain::findThemes(const QString& themeDirName, const QString& searchWhat,
                                   const QString& searchWhat2,  const QString& defaultValue) const
{
    QStringList themes, themesPaths;
    QStringList paths = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation);
    paths.removeDuplicates();

    // $HOME/.local/share/themes:/usr/local/share/themes:/usr/share/themes
    for(const QString& path : std::as_const(paths)) {
        QString themesPath = path + '/' + themeDirName;
        if (QDir(themesPath).exists())
            themesPaths.push_back(themesPath);
    }
    // $HOME/.themes if any
    QString homeThemes = QString("%1%2%3").arg(std::getenv("HOME"), QStringLiteral("/."), themeDirName);
    if (!themesPaths.contains(homeThemes) && QDir(homeThemes).exists())
        themesPaths.push_back(homeThemes);

    for(const QString& themesPath : std::as_const(themesPaths)) {
        QDir themesDir(themesPath);
        QStringList themeEntries = themesDir.entryList(QDir::Dirs|QDir::NoDotAndDotDot);
        for (const QString& themeEntry : std::as_const(themeEntries)) {
            if (themeEntry == QStringLiteral("locolor") || themeEntry == QStringLiteral("hicolor"))
                continue;
            QString themePath = themesPath + '/' + themeEntry + '/' + searchWhat;
            if (QFileInfo::exists(themePath)) //TODO: && QFileInfo(themePath).isFile()) ?
                themes.push_back(themeEntry);
            if (!searchWhat2.isNull()) {
                QString themePath = themesPath + '/' + themeEntry + '/' + searchWhat2;
                if (QFileInfo::exists(themePath)) //TODO: && QFileInfo(themePath).isFile()) ?
                    themes.push_back(themeEntry);
            }
        }
    }
    themes.push_front(defaultValue);
    themes.removeDuplicates();
    return themes;
}
