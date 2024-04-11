#include "Settings.hpp"
#if 1
#include <QSettings>
#endif
namespace Default {
static constexpr bool enableEventSounds         { true };
static constexpr bool enableInputFeedbackSounds { true };
static constexpr bool enableRecentFiles         { true };
static constexpr bool overlayScrolling          { true };
static constexpr bool preferDarkTheme           { false };
static constexpr bool primaryButtonWarpSlider   { true };
static constexpr int  cursorThemeSize           {  0 };
static constexpr int  recentFilesMaxAge         { 30 };
static constexpr int  xftAntialias              { -1 };
static constexpr int  xftHinting                { -1 };
static constexpr int  xftDpi                    { -1 };
static const QString  fontName                  { "Sans 10" };
static const QString  iconThemeName             { "Adwaita" };
static const QString  themeName                 { "Default" };
} // namespace Default

Settings::Settings()
    : gsettings(g_settings_new("org.gnome.desktop.interface"))
#if 1
    , enableEventSounds_(Default::enableEventSounds)
    , enableInputFeedbackSounds_(Default::enableInputFeedbackSounds)
    , enableRecentFiles_(Default::enableRecentFiles)
    , overlayScrolling_(Default::overlayScrolling)
    , preferDarkTheme_(Default::preferDarkTheme)
    , warpSlider_(Default::primaryButtonWarpSlider)
    , cursorThemeSize_(Default::cursorThemeSize)
    , recentFilesMaxAge_(Default::recentFilesMaxAge)
    , xftAntialias_(Default::xftAntialias)
    , xftHinting_(Default::xftHinting)
    , xftDpi_(Default::xftDpi)
    , fontName_(Default::fontName)
    , iconThemeName_(Default::iconThemeName)
    , themeName_(Default::themeName)
#endif
{
}

void Settings::load()
{
#if 1
    QString path = QString("%1%2").arg(std::getenv("HOME"), QStringLiteral("/.config/gtk-4.0/settings.ini"));
    QSettings settings(path, QSettings::IniFormat);

    settings.beginGroup("Settings");
    preferDarkTheme_           = settings.value(QStringLiteral("gtk-application-prefer-dark-theme"), Default::preferDarkTheme).toBool();
    cursorThemeName_           = settings.value(QStringLiteral("gtk-cursor-theme-name"), QString()).toString();
    cursorThemeSize_           = settings.value(QStringLiteral("gtk-cursor-theme-size"), Default::cursorThemeSize).toInt();
    enableEventSounds_         = settings.value(QStringLiteral("gtk-enable-event-sounds"), Default::enableEventSounds).toBool();
    enableInputFeedbackSounds_ = settings.value(QStringLiteral("gtk-enable-input-feedback-sounds"), Default::enableInputFeedbackSounds).toBool();
    fontName_                  = settings.value(QStringLiteral("gtk-font-name"), Default::fontName).toString();
    iconThemeName_             = settings.value(QStringLiteral("gtk-icon-theme-name"), Default::iconThemeName).toString();
    overlayScrolling_          = settings.value(QStringLiteral("gtk-overlay-scrolling"), Default::overlayScrolling).toBool();
    warpSlider_                = settings.value(QStringLiteral("gtk-primary-button-warps-slider"), Default::primaryButtonWarpSlider).toBool();
    enableRecentFiles_         = settings.value(QStringLiteral("gtk-recent-files-enabled"), Default::enableRecentFiles).toBool();
    recentFilesMaxAge_         = settings.value(QStringLiteral("gtk-recent-files-max-age"), Default::recentFilesMaxAge).toInt();
    themeName_                 = settings.value(QStringLiteral("gtk-theme-name"), Default::themeName).toString();
    xftAntialias_              = settings.value(QStringLiteral("gtk-xft-antialias"), Default::xftAntialias).toInt();
    xftDpi_                    = settings.value(QStringLiteral("gtk-xft-dpi"), Default::xftDpi).toInt();
    xftHinting_                = settings.value(QStringLiteral("gtk-xft-hinting"), Default::xftHinting).toInt();
    xftHintStyle_              = settings.value(QStringLiteral("gtk-xft-hintstyle"), QString()).toString();
    xftRgba_                   = settings.value(QStringLiteral("gtk-xft-rgba"), QString()).toString();
    settings.endGroup();
#else
    preferDarkTheme_           = g_settings_get_boolean(gsettings, "gtk-application-prefer-dark-theme");
    cursorThemeName_           = g_settings_get_string(gsettings,  "gtk-cursor-theme-name");
    cursorThemeSize_           = g_settings_get_int(gsettings,     "gtk-cursor-theme-size");
    enableEventSounds_         = g_settings_get_boolean(gsettings, "gtk-enable-event-sounds");
    enableInputFeedbackSounds_ = g_settings_get_boolean(gsettings, "gtk-enable-input-feedback-sounds");
    fontName_                  = g_settings_get_string(gsettings,  "gtk-font-name");
    iconThemeName_             = g_settings_get_string(gsettings,  "gtk-icon-theme-name");
    overlayScrolling_          = g_settings_get_boolean(gsettings, "gtk-overlay-scrolling");
    warpSlider_                = g_settings_get_boolean(gsettings, "gtk-primary-button-warps-slider");
    enableRecentFiles_         = g_settings_get_boolean(gsettings, "gtk-recent-files-enabled");
    recentFilesMaxAge_         = g_settings_get_int(gsettings,     "gtk-recent-files-max-age");
    themeName_                 = g_settings_get_string(gsettings,  "gtk-theme-name");
    xftAntialias_              = g_settings_get_int(gsettings,     "gtk-xft-antialias");
    xftDpi_                    = g_settings_get_int(gsettings,     "gtk-xft-dpi");
    xftHinting_                = g_settings_get_int(gsettings,     "gtk-xft-hinting");
    xftHintStyle_              = g_settings_get_string(gsettings,  "gtk-xft-hintstyle");
    xftRgba_                   = g_settings_get_string(gsettings,  "gtk-xft-rgba");
#endif
}

void Settings::save()
{
#if 1
    for (int version = 3; version < 5; ++version) {
        QString path = QString("%1%2").arg(std::getenv("HOME"),
            QString("%1%2%3").arg("/.config/gtk-", QString::number(version), ".0/settings.ini"));
        QSettings settings(path, QSettings::IniFormat);
    
        settings.beginGroup("Settings");
        settings.setValue(QStringLiteral("gtk-application-prefer-dark-theme"), preferDarkTheme_);
        settings.setValue(QStringLiteral("gtk-cursor-theme-name"), cursorThemeName_);
        settings.setValue(QStringLiteral("gtk-cursor-theme-size"), cursorThemeSize_);
        settings.setValue(QStringLiteral("gtk-enable-event-sounds"), enableEventSounds_);
        settings.setValue(QStringLiteral("gtk-enable-input-feedback-sounds"), enableInputFeedbackSounds_);
        settings.setValue(QStringLiteral("gtk-font-name"), fontName_);
        settings.setValue(QStringLiteral("gtk-icon-theme-name"), iconThemeName_);
        settings.setValue(QStringLiteral("gtk-overlay-scrolling"), overlayScrolling_);
        settings.setValue(QStringLiteral("gtk-primary-button-warps-slider"), warpSlider_);
        settings.setValue(QStringLiteral("gtk-recent-files-enabled"), enableRecentFiles_);
        settings.setValue(QStringLiteral("gtk-recent-files-max-age"), recentFilesMaxAge_);
        settings.setValue(QStringLiteral("gtk-theme-name"), themeName_);
        settings.setValue(QStringLiteral("gtk-xft-antialias"), xftAntialias_);
        settings.setValue(QStringLiteral("gtk-xft-dpi"), xftDpi_);
        settings.setValue(QStringLiteral("gtk-xft-hinting"), xftHinting_);
        settings.setValue(QStringLiteral("gtk-xft-hintstyle"), xftHintStyle_);
        settings.setValue(QStringLiteral("gtk-xft-rgba"), xftRgba_);
        settings.endGroup();
        settings.sync();
    }
#else
    g_settings_set_boolean(gsettings, "gtk-application-prefer-dark-theme", preferDarkTheme_);
    g_settings_set_string(gsettings,  "gtk-cursor-theme-name",             cursorThemeName_.toStdString().c_str());
    g_settings_set_int(gsettings,     "gtk-cursor-theme-size",             cursorThemeSize_);
    g_settings_set_boolean(gsettings, "gtk-enable-event-sounds",           enableEventSounds_);
    g_settings_set_boolean(gsettings, "gtk-enable-input-feedback-sounds",  enableInputFeedbackSounds_);
    g_settings_set_string(gsettings,  "gtk-font-name",                     fontName_.toStdString().c_str());
    g_settings_set_string(gsettings,  "gtk-icon-theme-name",               iconThemeName_.toStdString().c_str());
    g_settings_set_boolean(gsettings, "gtk-overlay-scrolling",             overlayScrolling_);
    g_settings_set_boolean(gsettings, "gtk-primary-button-warps-slider",   warpSlider_);
    g_settings_set_boolean(gsettings, "gtk-recent-files-enabled",          enableRecentFiles_);
    g_settings_set_int(gsettings,     "gtk-recent-files-max-age",          recentFilesMaxAge_);
    g_settings_set_string(gsettings,  "gtk-theme-name",                    themeName_.toStdString().c_str());
    g_settings_set_int(gsettings,     "gtk-xft-antialias",                 xftAntialias_);
    g_settings_set_int(gsettings,     "gtk-xft-dpi",                       xftDpi_);
    g_settings_set_int(gsettings,     "gtk-xft-hinting",                   xftHinting_);
    g_settings_set_string(gsettings,  "gtk-xft-hintstyle",                 xftHintStyle_.toStdString().c_str());
    g_settings_set_string(gsettings,  "gtk-xft-rgba",                      xftRgba_.toStdString().c_str());
    g_settings_sync();
#endif
}
