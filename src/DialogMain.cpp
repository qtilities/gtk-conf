#include "DialogMain.hpp"
#include "DialogAbout.hpp"
#include "Settings.hpp"

#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QStandardPaths>

DialogMain::DialogMain(QWidget *parent)
    : QDialog(parent)
    , settings_(new Settings(this))
{
#define ENABLE_BUTTONS \
    reset->setEnabled(true); \
    save->setEnabled(true)

#define DISABLE_BUTTONS \
    reset->setEnabled(false); \
    save->setEnabled(false)

    setupUi(this);

    list->setFixedWidth(list->sizeHintForColumn(0) + 2 * list->frameWidth());

    gbxScaleFactor->hide();
    chkAllowVolumeAbove100->hide();

    QStringList listXftHintStyle, listXftRgba;

    if (settings_->isWayland()) {
        setupToolTipsGSettings();
        listXftHintStyle = { QStringLiteral("slight"), QStringLiteral("none"), QStringLiteral("medium"), QStringLiteral("full") };
        listXftRgba = { QStringLiteral("rgb"), QStringLiteral("rgba"), QStringLiteral("bgr"), QStringLiteral("vrgb"), QStringLiteral("vbgr") };
        cbxColorScheme->addItems({"default", "prefer-light", "prefer-dark"});
        cbxFontAntialiasing->addItems({"none", "grayscale", "rgba"});
        chkPreferDarkTheme->hide();
        chkWarpSlider->hide();
        chkXftAntialias->hide();
        chkXftHinting->hide();
        sbxXftDpi->hide();
        lblXftDpi->hide();
    } else {
        setupToolTips();
        listXftHintStyle = { QString(), QStringLiteral("hintnone"), QStringLiteral("hintslight"), QStringLiteral("hintmedium"), QStringLiteral("hintfull") };
        listXftRgba = { QString(), QStringLiteral("none"), QStringLiteral("rgb"), QStringLiteral("bgr"), QStringLiteral("vrgb"), QStringLiteral("vbgr") };
        lblColorScheme->hide();
        cbxColorScheme->hide();
        cbxFontAntialiasing->hide();
        lblFontAntialiasing->hide();
    }
    cbxXftHintStyle->addItems(listXftHintStyle);
    cbxXftRgba->addItems(listXftRgba);

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

    cbxCursorThemeName->addItems(cursorThemes);
    cbxIconThemeName->addItems(iconThemes);
    cbxSoundThemeName->addItems(soundThemes);
    cbxThemeName->addItems(gtkThemes);

    QPushButton* reset = buttonBox->button(QDialogButtonBox::Reset);
    QPushButton* save  = buttonBox->button(QDialogButtonBox::Save);
    DISABLE_BUTTONS;

    connect(settings_, &Settings::propertiesChanged, [this, reset, save](){
        QMessageBox::warning(this, tr("Settings changed"),
            tr("Some settings have been changed by a different application.\n\n"
               "You can reload the new settings by pressing the Reset button, "
               "or use Save if you want to keep the current ones.")
            );
        ENABLE_BUTTONS;
    });
    updateUi();

#define CONNECT_CHECKBOX(NAME) \
    connect(chk##NAME, &QCheckBox::toggled, [this, reset, save]() { \
        settings_->set##NAME(chk##NAME->isChecked()); \
        ENABLE_BUTTONS; \
    })
#define CONNECT_CHECKBOX_TRISTATE(NAME) \
    connect(chk##NAME, &QCheckBox::clicked, [this, reset, save]() { \
        settings_->set##NAME(fromCheckState(chk##NAME->checkState())); \
        ENABLE_BUTTONS; \
    })
#define CONNECT_COMBOBOX(NAME) \
    connect(cbx##NAME, &QComboBox::currentTextChanged, [this, reset, save]() { \
        settings_->set##NAME(cbx##NAME->currentText()); \
        ENABLE_BUTTONS; \
    })
#define CONNECT_SPINBOX(NAME) \
    connect(sbx##NAME, QOverload<int>::of(&QSpinBox::valueChanged), \
            [this, reset, save] { \
                settings_->set##NAME(sbx##NAME->value()); \
                ENABLE_BUTTONS; \
            })
#define CONNECT_DOUBLE_SPINBOX(NAME) \
    connect(dsb##NAME, QOverload<qreal>::of(&QDoubleSpinBox::valueChanged), \
            [this, reset, save] { \
                settings_->set##NAME(dsb##NAME->value()); \
                ENABLE_BUTTONS; \
            })
    connect(gbxEnableRecentFiles, &QGroupBox::toggled, [this, reset, save]() { \
        settings_->setEnableRecentFiles(gbxEnableRecentFiles->isChecked()); \
        ENABLE_BUTTONS;
    });
    connect(fbnDefaultFont, &FontButton::changed, [this, reset, save]() { \
        settings_->setFontName(fbnDefaultFont->text()); \
        ENABLE_BUTTONS;
    });
    connect(reset, &QPushButton::clicked, [this, reset, save]() {
        settings_->load();
        updateUi();
        DISABLE_BUTTONS;
    });
    connect(buttonBox, &QDialogButtonBox::accepted, [this, reset, save]() {
        settings_->save();
        DISABLE_BUTTONS;
    });
    connect(pbnAbout, &QPushButton::clicked, [this](){
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
    if (settings_->isWayland()) {
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
}

void DialogMain::updateUi()
{
    if (settings_->isWayland()) {
        cbxColorScheme->setCurrentText(settings_->colorScheme());
        cbxFontAntialiasing->setCurrentText(settings_->fontAntialiasing());
    } else {
        chkPreferDarkTheme->setChecked(settings_->preferDarkTheme());
        chkWarpSlider->setChecked(settings_->warpSlider());
        sbxXftDpi->setValue(settings_->xftDpi());
        chkXftAntialias->setCheckState(checkState(settings_->xftAntialias()));
        chkXftHinting->setCheckState(checkState(settings_->xftHinting()));
    }
    cbxCursorThemeName->setCurrentText(settings_->cursorThemeName());
    sbxCursorThemeSize->setValue(settings_->cursorThemeSize());
    fbnDefaultFont->setFont(fromName(settings_->fontName()));
    chkEnableEventSounds->setChecked(settings_->enableEventSounds());
    chkEnableInputFeedbackSounds->setChecked(settings_->enableInputFeedbackSounds());
    gbxEnableRecentFiles->setChecked(settings_->enableRecentFiles());
    cbxIconThemeName->setCurrentText(settings_->iconThemeName());
    chkOverlayScrolling->setChecked(settings_->overlayScrolling());
    sbxRecentFilesMaxAge->setValue(settings_->recentFilesMaxAge());
    cbxSoundThemeName->setCurrentText(settings_->soundThemeName());
    cbxThemeName->setCurrentText(settings_->themeName());
    cbxXftHintStyle->setCurrentText(settings_->xftHintStyle());
    cbxXftRgba->setCurrentText(settings_->xftRgba());
#if 0
//  chkAllowVolumeAbove100->setChecked(settings_->allowVolumeAbove100());
    sbxScaleFactor->setValue(settings_->scaleFactor());
    dsbTextScaleFactor->setValue(settings_->textScaleFactor());
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
