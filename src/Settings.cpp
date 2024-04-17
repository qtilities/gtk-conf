#include "Settings.hpp"

#include <gio/gio.h>
#include <glib-object.h>

#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QSettings>

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
static constexpr int  scaleFactor               {  1 };
static constexpr qreal textScaleFactor          { 1.0 };
static const QString  colorScheme               { "default" };
static const QString  fontName                  { "Sans 10" };
static const QString  iconThemeName             { "Adwaita" };
static const QString  soundThemeName            { "freedesktop" };
static const QString  themeName                 { "Default" };
} // namespace Default

static constexpr std::array<int, 2> GtkVersions { 3, 4 };

static gboolean
on_change_event(GSettings */*gsettings*/,
                gpointer   /*keys*/,
                int        /*n_keys*/,
                gpointer   settings)
{
    Settings* s = static_cast<Settings*>(settings);
    if (s->saving())
        return FALSE;

    Q_EMIT s->propertiesChanged();
    return TRUE;
}

static bool isItWayland()
{
    if (std::getenv("WAYLAND_DISPLAY"))
        return true;

    return false;
}

static QStringList iniPaths()
{
    QStringList paths;
    const char* home = std::getenv("HOME");

    for (int gtkVersion : GtkVersions) {
        QString path = QString("%1/.config/gtk-%2.0/settings.ini").arg(home, QString::number(gtkVersion));
        if (QFileInfo::exists(path))
            paths << path;
    }
    return paths;
}

Settings::Settings(QObject* parent)
    : QObject(parent)
    , guiSettings_(nullptr)
    , prvSettings_(nullptr)
    , sndSettings_(nullptr)
    , isWayland_(isItWayland())
    , saving_(false)
    , fsWatcher_(new QFileSystemWatcher(iniPaths(), this))
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
    , scaleFactor_(Default::scaleFactor)
    , textScaleFactor_(Default::textScaleFactor)
    , colorScheme_(Default::colorScheme)
    , fontName_(Default::fontName)
    , iconThemeName_(Default::iconThemeName)
    , soundThemeName_(Default::soundThemeName)
    , themeName_(Default::themeName)
{
    if (isWayland_) {
        guiSettings_ = g_settings_new("org.gnome.desktop.interface");
        prvSettings_ = g_settings_new("org.gnome.desktop.privacy");
        sndSettings_ = g_settings_new("org.gnome.desktop.sound");
        g_signal_connect(G_OBJECT(guiSettings_), "change-event", G_CALLBACK(on_change_event), this);
        g_signal_connect(G_OBJECT(prvSettings_), "change-event", G_CALLBACK(on_change_event), this);
        g_signal_connect(G_OBJECT(sndSettings_), "change-event", G_CALLBACK(on_change_event), this);
    } else {
        connect(fsWatcher_, &QFileSystemWatcher::fileChanged, [this](const QString& path) {
            if (!fsWatcher_->files().contains(path) && QFileInfo::exists(path))
                fsWatcher_->addPath(path);

            if (saving_)
                Q_EMIT this->propertiesChanged();
        });
    }
    load();
}

Settings::~Settings()
{
    if (isWayland_) {
        g_object_unref(guiSettings_);
        g_object_unref(sndSettings_);
        g_object_unref(prvSettings_);
    }
}

void Settings::load()
{
    if (isWayland_) {
        loadGSettings();
    } else {
        loadIniSettings();
    }
}

void Settings::save()
{
    saving_ = true;

    if (isWayland_) {
        saveGSettings();
    } else {
        saveIniSettings();
    }
    saving_ = false;
}

void Settings::loadGSettings()
{
    // no primary-button-warps-slider, xft-antialias, gtk-xft-dpi, and gtk-xft-hinting
//  allowVolumeAbove100_       = g_settings_get_boolean(sndSettings_, "allow-volume-above-100-percent");
    colorScheme_               = g_settings_get_string(guiSettings_,  "color-scheme");
    cursorThemeName_           = g_settings_get_string(guiSettings_,  "cursor-theme");
    cursorThemeSize_           = g_settings_get_int(guiSettings_,     "cursor-size");
    enableEventSounds_         = g_settings_get_boolean(sndSettings_, "event-sounds");
    enableInputFeedbackSounds_ = g_settings_get_boolean(sndSettings_, "input-feedback-sounds");
    fontAntialiasing_          = g_settings_get_string(guiSettings_,  "font-antialiasing");
    fontName_                  = g_settings_get_string(guiSettings_,  "font-name");
    iconThemeName_             = g_settings_get_string(guiSettings_,  "icon-theme");
    overlayScrolling_          = g_settings_get_boolean(guiSettings_, "overlay-scrolling");
    enableRecentFiles_         = g_settings_get_boolean(prvSettings_, "remember-recent-files");
    recentFilesMaxAge_         = g_settings_get_int(prvSettings_,     "recent-files-max-age");
    soundThemeName_            = g_settings_get_string(sndSettings_,  "theme-name");
    themeName_                 = g_settings_get_string(guiSettings_,  "gtk-theme");
    xftHintStyle_              = g_settings_get_string(guiSettings_,  "font-hinting");
    xftRgba_                   = g_settings_get_string(guiSettings_,  "font-rgba-order");
}

void Settings::saveGSettings()
{
//  g_settings_set_boolean(sndSettings_, "allow-volume-above-100-percent",  allowVolumeAbove100_);
    g_settings_set_string(guiSettings_,  "color-scheme",                    colorScheme_.toStdString().c_str());
    g_settings_set_string(guiSettings_,  "cursor-theme",                    cursorThemeName_.toStdString().c_str());
    g_settings_set_int(guiSettings_,     "cursor-size",                     cursorThemeSize_);
    g_settings_set_boolean(sndSettings_, "event-sounds",                    enableEventSounds_);
    g_settings_set_boolean(sndSettings_, "input-feedback-sounds",           enableInputFeedbackSounds_);
    g_settings_set_string(guiSettings_,  "font-antialiasing",               fontAntialiasing_.toStdString().c_str());
    g_settings_set_string(guiSettings_,  "font-name",                       fontName_.toStdString().c_str());
    g_settings_set_string(guiSettings_,  "icon-theme",                      iconThemeName_.toStdString().c_str());
    g_settings_set_boolean(guiSettings_, "overlay-scrolling",               overlayScrolling_);
    g_settings_set_boolean(prvSettings_, "remember-recent-files",           enableRecentFiles_);
    g_settings_set_int(prvSettings_,     "recent-files-max-age",            recentFilesMaxAge_);
    g_settings_set_string(sndSettings_,  "theme-name",                      soundThemeName_.toStdString().c_str());
    g_settings_set_string(guiSettings_,  "gtk-theme",                       themeName_.toStdString().c_str());
    g_settings_set_string(guiSettings_,  "font-hinting",                    xftHintStyle_.toStdString().c_str());
    g_settings_set_string(guiSettings_,  "font-rgba-order",                 xftRgba_.toStdString().c_str());
    g_settings_sync();
}

void Settings::loadIniSettings()
{
    for (const QString& path : iniPaths()) {
        QSettings settings(path, QSettings::IniFormat);

        settings.beginGroup("Settings");
        preferDarkTheme_           = settings.value(QStringLiteral("gtk-application-prefer-dark-theme"), Default::preferDarkTheme).toBool();
        cursorThemeName_           = settings.value(QStringLiteral("gtk-cursor-theme-name"),             QString()).toString();
        cursorThemeSize_           = settings.value(QStringLiteral("gtk-cursor-theme-size"),             Default::cursorThemeSize).toInt();
        enableEventSounds_         = settings.value(QStringLiteral("gtk-enable-event-sounds"),           Default::enableEventSounds).toBool();
        enableInputFeedbackSounds_ = settings.value(QStringLiteral("gtk-enable-input-feedback-sounds"),  Default::enableInputFeedbackSounds).toBool();
        fontName_                  = settings.value(QStringLiteral("gtk-font-name"),                     Default::fontName).toString();
        iconThemeName_             = settings.value(QStringLiteral("gtk-icon-theme-name"),               Default::iconThemeName).toString();
        overlayScrolling_          = settings.value(QStringLiteral("gtk-overlay-scrolling"),             Default::overlayScrolling).toBool();
        warpSlider_                = settings.value(QStringLiteral("gtk-primary-button-warps-slider"),   Default::primaryButtonWarpSlider).toBool();
        enableRecentFiles_         = settings.value(QStringLiteral("gtk-recent-files-enabled"),          Default::enableRecentFiles).toBool();
        recentFilesMaxAge_         = settings.value(QStringLiteral("gtk-recent-files-max-age"),          Default::recentFilesMaxAge).toInt();
        soundThemeName_            = settings.value(QStringLiteral("gtk-sound-theme-name"),              Default::soundThemeName).toString();
        themeName_                 = settings.value(QStringLiteral("gtk-theme-name"),                    Default::themeName).toString();
        xftAntialias_              = settings.value(QStringLiteral("gtk-xft-antialias"),                 Default::xftAntialias).toInt();
        xftDpi_                    = settings.value(QStringLiteral("gtk-xft-dpi"),                       Default::xftDpi).toInt();
        xftHinting_                = settings.value(QStringLiteral("gtk-xft-hinting"),                   Default::xftHinting).toInt();
        xftHintStyle_              = settings.value(QStringLiteral("gtk-xft-hintstyle"),                 QString()).toString();
        xftRgba_                   = settings.value(QStringLiteral("gtk-xft-rgba"),                      QString()).toString();
        settings.endGroup();
    }
}

void Settings::saveIniSettings()
{
    for (const QString& path : iniPaths()) {
        QSettings settings(path, QSettings::IniFormat);

        settings.beginGroup("Settings");
        settings.setValue(QStringLiteral("gtk-application-prefer-dark-theme"), preferDarkTheme_);
        settings.setValue(QStringLiteral("gtk-cursor-theme-name"),             cursorThemeName_);
        settings.setValue(QStringLiteral("gtk-cursor-theme-size"),             cursorThemeSize_);
        settings.setValue(QStringLiteral("gtk-enable-event-sounds"),           enableEventSounds_);
        settings.setValue(QStringLiteral("gtk-enable-input-feedback-sounds"),  enableInputFeedbackSounds_);
        settings.setValue(QStringLiteral("gtk-font-name"),                     fontName_);
        settings.setValue(QStringLiteral("gtk-icon-theme-name"),               iconThemeName_);
        settings.setValue(QStringLiteral("gtk-overlay-scrolling"),             overlayScrolling_);
        settings.setValue(QStringLiteral("gtk-primary-button-warps-slider"),   warpSlider_);
        settings.setValue(QStringLiteral("gtk-recent-files-enabled"),          enableRecentFiles_);
        settings.setValue(QStringLiteral("gtk-recent-files-max-age"),          recentFilesMaxAge_);
        settings.setValue(QStringLiteral("gtk-theme-name"),                    themeName_);
        settings.setValue(QStringLiteral("gtk-sound-theme-name"),              soundThemeName_);
        settings.setValue(QStringLiteral("gtk-xft-antialias"),                 xftAntialias_);
        settings.setValue(QStringLiteral("gtk-xft-dpi"),                       xftDpi_);
        settings.setValue(QStringLiteral("gtk-xft-hinting"),                   xftHinting_);
        settings.setValue(QStringLiteral("gtk-xft-hintstyle"),                 xftHintStyle_);
        settings.setValue(QStringLiteral("gtk-xft-rgba"),                      xftRgba_);
        settings.endGroup();
        settings.sync();
    }
}
