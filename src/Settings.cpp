#include "Settings.hpp"
#include <gtk/gtk.h>

static gboolean
on_change_event(GSettings */*gsettings*/,
                gpointer   /*keys*/,
                int        /*n_keys*/,
                gpointer   settings)
{
    Settings* s = static_cast<Settings*>(settings);
    Q_EMIT s->propertiesChanged();
    return TRUE;
}

Settings::Settings(QObject* parent)
    : QObject(parent)
    , guiSettings(g_settings_new("org.gnome.desktop.interface"))
    , prvSettings(g_settings_new("org.gnome.desktop.privacy"))
    , sndSettings(g_settings_new("org.gnome.desktop.sound"))
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
    g_signal_connect(G_OBJECT(guiSettings), "change-event", G_CALLBACK(on_change_event), this);
    g_signal_connect(G_OBJECT(prvSettings), "change-event", G_CALLBACK(on_change_event), this);
    g_signal_connect(G_OBJECT(sndSettings), "change-event", G_CALLBACK(on_change_event), this);
}

Settings::~Settings()
{
    g_object_unref(guiSettings);
    g_object_unref(sndSettings);
    g_object_unref(prvSettings);
}

void Settings::load()
{
    colorScheme_               = g_settings_get_string(guiSettings,  "color-scheme");
//  preferDarkTheme_           = g_settings_get_boolean(guiSettings, "gtk-application-prefer-dark-theme");
    cursorThemeName_           = g_settings_get_string(guiSettings,  "cursor-theme");
    cursorThemeSize_           = g_settings_get_int(guiSettings,     "cursor-size");
    enableEventSounds_         = g_settings_get_boolean(sndSettings, "event-sounds");
    enableInputFeedbackSounds_ = g_settings_get_boolean(sndSettings, "input-feedback-sounds");
    fontAntialiasing_          = g_settings_get_string(guiSettings,  "font-antialiasing");
    fontName_                  = g_settings_get_string(guiSettings,  "font-name");
    iconThemeName_             = g_settings_get_string(guiSettings,  "icon-theme");
    overlayScrolling_          = g_settings_get_boolean(guiSettings, "overlay-scrolling");
//  warpSlider_                = g_settings_get_boolean(guiSettings, "gtk-primary-button-warps-slider");
    enableRecentFiles_         = g_settings_get_boolean(prvSettings, "remember-recent-files");
    recentFilesMaxAge_         = g_settings_get_int(prvSettings,     "recent-files-max-age");
    themeName_                 = g_settings_get_string(guiSettings,  "gtk-theme");
//  xftAntialias_              = g_settings_get_int(guiSettings,     "gtk-xft-antialias");
//  xftDpi_                    = g_settings_get_int(guiSettings,     "gtk-xft-dpi");
//  xftHinting_                = g_settings_get_int(guiSettings,     "gtk-xft-hinting");
    xftHintStyle_              = g_settings_get_string(guiSettings,  "font-hinting");
    xftRgba_                   = g_settings_get_string(guiSettings,  "font-rgba-order");
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
    g_settings_set_string(guiSettings,  "color-scheme",                    colorScheme_.toStdString().c_str());
//  g_settings_set_boolean(guiSettings, "gtk-application-prefer-dark-theme", preferDarkTheme_);
    g_settings_set_string(guiSettings,  "cursor-theme",                    cursorThemeName_.toStdString().c_str());
    g_settings_set_int(guiSettings,     "cursor-size",                     cursorThemeSize_);
    g_settings_set_boolean(sndSettings, "event-sounds",                    enableEventSounds_);
    g_settings_set_boolean(sndSettings, "input-feedback-sounds",           enableInputFeedbackSounds_);
    g_settings_set_string(guiSettings,  "font-antialiasing",               fontAntialiasing_.toStdString().c_str());
    g_settings_set_string(guiSettings,  "font-name",                       fontName_.toStdString().c_str());
    g_settings_set_string(guiSettings,  "icon-theme",                      iconThemeName_.toStdString().c_str());
    g_settings_set_boolean(guiSettings, "overlay-scrolling",               overlayScrolling_);
//  g_settings_set_boolean(guiSettings, "gtk-primary-button-warps-slider", warpSlider_);
    g_settings_set_boolean(prvSettings, "remember-recent-files",           enableRecentFiles_);
    g_settings_set_int(prvSettings,     "recent-files-max-age",            recentFilesMaxAge_);
    g_settings_set_string(guiSettings,  "gtk-theme",                       themeName_.toStdString().c_str());
//  g_settings_set_int(guiSettings,     "gtk-xft-antialias",               xftAntialias_);
//  g_settings_set_int(guiSettings,     "gtk-xft-dpi",                     xftDpi_);
//  g_settings_set_int(guiSettings,     "gtk-xft-hinting",                 xftHinting_);
    g_settings_set_string(guiSettings,  "font-hinting",                    xftHintStyle_.toStdString().c_str());
    g_settings_set_string(guiSettings,  "font-rgba-order",                 xftRgba_.toStdString().c_str());
    g_settings_sync();
}
