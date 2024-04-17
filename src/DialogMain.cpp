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

    ui->gbxScaleFactor->hide();
    ui->chkAllowVolumeAbove100->hide();

    QStringList listXftHintStyle, listXftRgba;

    if (settings->isWayland()) {
        listXftHintStyle = { QStringLiteral("slight"), QStringLiteral("none"), QStringLiteral("medium"), QStringLiteral("full") };
        listXftRgba = { QStringLiteral("rgb"), QStringLiteral("rgba"), QStringLiteral("bgr"), QStringLiteral("vrgb"), QStringLiteral("vbgr") };
        ui->chkPreferDarkTheme->hide();
        ui->chkWarpSlider->hide();
        ui->chkXftAntialias->hide();
        ui->chkXftHinting->hide();
        ui->sbxXftDpi->hide();
        ui->lblXftDpi->hide();
    } else {
        listXftHintStyle = { QString(), QStringLiteral("hintnone"), QStringLiteral("hintslight"), QStringLiteral("hintmedium"), QStringLiteral("hintfull") };
        listXftRgba = { QString(), QStringLiteral("none"), QStringLiteral("rgb"), QStringLiteral("bgr"), QStringLiteral("vrgb"), QStringLiteral("vbgr") };
        ui->lblColorScheme->hide();
        ui->cbxColorScheme->hide();
        ui->cbxFontAntialiasing->hide();
        ui->lblFontAntialiasing->hide();
    }
    ui->cbxXftHintStyle->addItems(listXftHintStyle);
    ui->cbxXftRgba->addItems(listXftRgba);

    QStringList cursorThemes = findThemes(QStringLiteral("icons"), QStringLiteral("cursors"));
    QStringList iconThemes   = findThemes(QStringLiteral("icons"), QStringLiteral("16x16"), QStringLiteral("scalable"),
                                          QStringLiteral("Adwaita"));
    QStringList soundThemes  = findThemes(QStringLiteral("sounds"), QString(), QString(),
                                          QStringLiteral("freedesktop"));
    QStringList gtkThemes    = findThemes(QStringLiteral("themes"), QStringLiteral("/gtk-3.0"), QString(),
                                          QStringLiteral("Default"));

    cursorThemes.sort(Qt::CaseInsensitive);
    iconThemes.sort(Qt::CaseInsensitive);
    soundThemes.sort(Qt::CaseInsensitive);
    gtkThemes.sort(Qt::CaseInsensitive);

    ui->cbxCursorThemeName->addItems(cursorThemes);
    ui->cbxIconThemeName->addItems(iconThemes);
    ui->cbxSoundThemeName->addItems(soundThemes);
    ui->cbxThemeName->addItems(gtkThemes);

    QPushButton* reset = ui->buttonBox->button(QDialogButtonBox::Reset);
    QPushButton* save  = ui->buttonBox->button(QDialogButtonBox::Save);
    DISABLE_BUTTONS;

    connect(settings, &Settings::propertiesChanged, [this, reset, save](){
        QMessageBox::warning(this, tr("Settings changed"),
            tr("Some settings have been changed by a different application.\n\n"
               "You can reload the new settings by pressing the Reset button, "
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
#define CONNECT_CHECKBOX_TRISTATE(NAME) \
    connect(ui->chk##NAME, &QCheckBox::clicked, [this, reset, save]() { \
        settings->set##NAME(fromCheckState(ui->chk##NAME->checkState())); \
        ENABLE_BUTTONS; \
    })
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
#define CONNECT_DOUBLE_SPINBOX(NAME) \
    connect(ui->dsb##NAME, QOverload<qreal>::of(&QDoubleSpinBox::valueChanged), \
            [this, reset, save] { \
                settings->set##NAME(ui->dsb##NAME->value()); \
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
    CONNECT_CHECKBOX(AllowVolumeAbove100);
    CONNECT_SPINBOX(ScaleFactor);
    CONNECT_DOUBLE_SPINBOX(TextScaleFactor);
#endif
    if (settings->isWayland()) {
        CONNECT_COMBOBOX(ColorScheme);
        CONNECT_COMBOBOX(FontAntialiasing);
    } else {
        CONNECT_CHECKBOX(PreferDarkTheme);
        CONNECT_CHECKBOX(WarpSlider);
        CONNECT_CHECKBOX_TRISTATE(XftAntialias);
        CONNECT_CHECKBOX_TRISTATE(XftHinting);
        CONNECT_SPINBOX(XftDpi);
    }
    CONNECT_COMBOBOX(CursorThemeName);
    CONNECT_COMBOBOX(IconThemeName);
    CONNECT_COMBOBOX(SoundThemeName);
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
    if (settings->isWayland()) {
        ui->cbxColorScheme->setCurrentText(settings->colorScheme());
        ui->cbxFontAntialiasing->setCurrentText(settings->fontAntialiasing());
    } else {
        ui->chkPreferDarkTheme->setChecked(settings->preferDarkTheme());
        ui->chkWarpSlider->setChecked(settings->warpSlider());
        ui->sbxXftDpi->setValue(settings->xftDpi());
        ui->chkXftAntialias->setCheckState(checkState(settings->xftAntialias()));
        ui->chkXftHinting->setCheckState(checkState(settings->xftHinting()));
    }
    ui->cbxCursorThemeName->setCurrentText(settings->cursorThemeName());
    ui->sbxCursorThemeSize->setValue(settings->cursorThemeSize());
    ui->fbnDefaultFont->setFont(fromName(settings->fontName()));
    ui->chkEnableEventSounds->setChecked(settings->enableEventSounds());
    ui->chkEnableInputFeedbackSounds->setChecked(settings->enableInputFeedbackSounds());
    ui->gbxEnableRecentFiles->setChecked(settings->enableRecentFiles());
    ui->cbxIconThemeName->setCurrentText(settings->iconThemeName());
    ui->chkOverlayScrolling->setChecked(settings->overlayScrolling());
    ui->sbxRecentFilesMaxAge->setValue(settings->recentFilesMaxAge());
    ui->cbxSoundThemeName->setCurrentText(settings->soundThemeName());
    ui->cbxThemeName->setCurrentText(settings->themeName());
    ui->cbxXftHintStyle->setCurrentText(settings->xftHintStyle());
    ui->cbxXftRgba->setCurrentText(settings->xftRgba());
#if 0
//  ui->chkAllowVolumeAbove100->setChecked(settings->allowVolumeAbove100());
    ui->sbxScaleFactor->setValue(settings->scaleFactor());
    ui->dsbTextScaleFactor->setValue(settings->textScaleFactor());
#endif
}

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

QStringList DialogMain::findThemes(const QString& themeDirName,  const QString& searchFilter,
                                   const QString& searchFilter2, const QString& defaultValue) const
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
