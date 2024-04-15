#include "Settings.hpp"
#include <gtk/gtk.h>

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

Settings::Settings(QObject* parent)
    : QObject(parent)
    , guiSettings_(g_settings_new("org.gnome.desktop.interface"))
    , prvSettings_(g_settings_new("org.gnome.desktop.privacy"))
    , sndSettings_(g_settings_new("org.gnome.desktop.sound"))
    , saving_(false)
    , enableEventSounds_(false)
    , enableInputFeedbackSounds_(false)
    , enableRecentFiles_(false)
    , overlayScrolling_(false)
    , preferDarkTheme_(false)
    , warpSlider_(false)
    , cursorThemeSize_(0)
    , recentFilesMaxAge_(0)
    , xftAntialias_(0)
    , xftHinting_(0)
    , xftDpi_(0)
{
    g_signal_connect(G_OBJECT(guiSettings_), "change-event", G_CALLBACK(on_change_event), this);
    g_signal_connect(G_OBJECT(prvSettings_), "change-event", G_CALLBACK(on_change_event), this);
    g_signal_connect(G_OBJECT(sndSettings_), "change-event", G_CALLBACK(on_change_event), this);
    load();
}

Settings::~Settings()
{
    g_object_unref(guiSettings_);
    g_object_unref(sndSettings_);
    g_object_unref(prvSettings_);
}

void Settings::load()
{
//  allowVolumeAbove100_       = g_settings_get_boolean(sndSettings_, "allow-volume-above-100-percent");
    colorScheme_               = g_settings_get_string(guiSettings_,  "color-scheme");
//  preferDarkTheme_           = g_settings_get_boolean(guiSettings_, "gtk-application-prefer-dark-theme");
    cursorThemeName_           = g_settings_get_string(guiSettings_,  "cursor-theme");
    cursorThemeSize_           = g_settings_get_int(guiSettings_,     "cursor-size");
    enableEventSounds_         = g_settings_get_boolean(sndSettings_, "event-sounds");
    enableInputFeedbackSounds_ = g_settings_get_boolean(sndSettings_, "input-feedback-sounds");
    fontAntialiasing_          = g_settings_get_string(guiSettings_,  "font-antialiasing");
    fontName_                  = g_settings_get_string(guiSettings_,  "font-name");
    iconThemeName_             = g_settings_get_string(guiSettings_,  "icon-theme");
    overlayScrolling_          = g_settings_get_boolean(guiSettings_, "overlay-scrolling");
//  warpSlider_                = g_settings_get_boolean(guiSettings_, "gtk-primary-button-warps-slider");
    enableRecentFiles_         = g_settings_get_boolean(prvSettings_, "remember-recent-files");
    recentFilesMaxAge_         = g_settings_get_int(prvSettings_,     "recent-files-max-age");
    soundThemeName_            = g_settings_get_string(sndSettings_,  "theme-name");
    themeName_                 = g_settings_get_string(guiSettings_,  "gtk-theme");
//  xftAntialias_              = g_settings_get_int(guiSettings_,     "gtk-xft-antialias");
//  xftDpi_                    = g_settings_get_int(guiSettings_,     "gtk-xft-dpi");
//  xftHinting_                = g_settings_get_int(guiSettings_,     "gtk-xft-hinting");
    xftHintStyle_              = g_settings_get_string(guiSettings_,  "font-hinting");
    xftRgba_                   = g_settings_get_string(guiSettings_,  "font-rgba-order");
#if 0
    g_object_get(gtkSettings,
        "gtk-application-prefer-dark-theme", preferDarkTheme_,
        "gtk-cursor-theme-name", &gcursorThemeName,
        "gtk-cursor-theme-size", &cursorThemeSize_,
        "gtk-enable-event-sounds", enableEventSounds_,
        "gtk-enable-input-feedback-sounds", enableInputFeedbackSounds_,
        "gtk-font-name", &gfontName,
        "gtk-icon-theme-name", &giconThemeName,
        "gtk-overlay-scrolling", overlayScrolling_,
        "gtk-primary-button-warps-slider", warpSlider_,
        "gtk-recent-files-enabled", enableRecentFiles_,
        "gtk-recent-files-max-age", &recentFilesMaxAge_,
        "gtk-theme-name", &gthemeName,
        "gtk-xft-antialias", &xftAntialias_,
        "gtk-xft-dpi", &xftDpi_,
        "gtk-xft-hinting", &xftHinting_,
        "gtk-xft-hintstyle", &gxftHintStyle,
        "gtk-xft-rgba", &gxftRgba,
        nullptr
    );
#endif
}

void Settings::save()
{
    saving_ = true;
//  g_settings_set_boolean(sndSettings_, "allow-volume-above-100-percent",  allowVolumeAbove100_);
    g_settings_set_string(guiSettings_,  "color-scheme",                    colorScheme_.toStdString().c_str());
//  g_settings_set_boolean(guiSettings_, "gtk-application-prefer-dark-theme", preferDarkTheme_);
    g_settings_set_string(guiSettings_,  "cursor-theme",                    cursorThemeName_.toStdString().c_str());
    g_settings_set_int(guiSettings_,     "cursor-size",                     cursorThemeSize_);
    g_settings_set_boolean(sndSettings_, "event-sounds",                    enableEventSounds_);
    g_settings_set_boolean(sndSettings_, "input-feedback-sounds",           enableInputFeedbackSounds_);
    g_settings_set_string(guiSettings_,  "font-antialiasing",               fontAntialiasing_.toStdString().c_str());
    g_settings_set_string(guiSettings_,  "font-name",                       fontName_.toStdString().c_str());
    g_settings_set_string(guiSettings_,  "icon-theme",                      iconThemeName_.toStdString().c_str());
    g_settings_set_boolean(guiSettings_, "overlay-scrolling",               overlayScrolling_);
//  g_settings_set_boolean(guiSettings_, "gtk-primary-button-warps-slider", warpSlider_);
    g_settings_set_boolean(prvSettings_, "remember-recent-files",           enableRecentFiles_);
    g_settings_set_int(prvSettings_,     "recent-files-max-age",            recentFilesMaxAge_);
    g_settings_set_string(sndSettings_,  "theme-name",                      soundThemeName_.toStdString().c_str());
    g_settings_set_string(guiSettings_,  "gtk-theme",                       themeName_.toStdString().c_str());
//  g_settings_set_int(guiSettings_,     "gtk-xft-antialias",               xftAntialias_);
//  g_settings_set_int(guiSettings_,     "gtk-xft-dpi",                     xftDpi_);
//  g_settings_set_int(guiSettings_,     "gtk-xft-hinting",                 xftHinting_);
    g_settings_set_string(guiSettings_,  "font-hinting",                    xftHintStyle_.toStdString().c_str());
    g_settings_set_string(guiSettings_,  "font-rgba-order",                 xftRgba_.toStdString().c_str());
    g_settings_sync();
    saving_ = false;
}
