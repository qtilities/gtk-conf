/*
    SPDX-FileCopyrightText:  2024 Andrea Zanellato <redtid3@gmail.com> and Qtilities team
    SPDX-License-Identifier: GPL-2.0-only

    This file is part of the gtk-conf application project,
    see AUTHORS and COPYING files for further details.
*/
#include "DialogMain.hpp"
#include "Settings.hpp"

#define QSL(x) QStringLiteral(x)

void DialogMain::setupToolTips() {
    chkPreferDarkTheme->setToolTip(
        QString("<h3>gtk-application-prefer-dark-theme</h3><p>") + tr(
        "Whether the application prefers to use a dark theme. "
        "If a GTK theme includes a dark variant, it will be used instead of the configured theme.") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>FALSE</b></p>")
    );
    lblCursorThemeName->setToolTip(
        QString("<h3>gtk-cursor-theme-name</h3><p>") + tr(
        "Name of the cursor theme to use. "
        "Use %1 to use the default theme.").arg("<b>NULL</b>") + QString("</p>")
    );
    lblCursorThemeSize->setToolTip(
        QString("<h3>gtk-cursor-theme-size</h3><p>") + tr(
        "The size to use for cursors. "
        "%1 means to use the default size.").arg("<b>0</b>") + QString("</p>")
    );
    chkEnableEventSounds->setToolTip(
        QString("<h3>gtk-enable-event-sounds</h3><p>") + tr(
        "Whether to play any event sounds at all. "
        "See the Sound Theme Specifications for more information on event sounds and sound themes. "
        "GTK itself does not support event sounds, "
        "you have to use a loadable module like the one that comes with libcanberra.") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>TRUE</b></p>")
    );
    chkEnableInputFeedbackSounds->setToolTip(
        QString("<h3>gtk-enable-input-feedback-sounds</h3><p>") + tr(
        "Whether to play event sounds as feedback to user input. "
        "See the Sound Theme Specifications for more information on event sounds and sound themes. "
        "GTK itself does not support event sounds, "
        "you have to use a loadable module like the one that comes with libcanberra.") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>TRUE</b></p>")
    );
    lblGtkTheme->setToolTip(
        QString("<h3>gtk-theme-name</h3><p>") + tr(
        "Name of the theme to load. "
        "See GtkCssProvider for details about how GTK finds the CSS stylesheet for a theme.") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>Default</b></p>")
    );
    lblIconThemeName->setToolTip(
        QString("<h3>gtk-icon-theme-name</h3><p>") + tr(
        "Name of the icon theme to use. "
        "See GtkIconTheme for details about how GTK handles icon themes.") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>Adwaita</b></p>")
    );
    chkOverlayScrolling->setToolTip(
        QString("<h3>gtk-overlay-scrolling</h3><p>") + tr(
        "Whether scrolled windows may use overlaid scrolling indicators. "
        "If this is set to %1, scrolled windows will have permanent scrollbars.").arg("<b>FALSE</b>") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>TRUE</b></p>")
    );
    chkWarpSlider->setToolTip(
        QString("<h3>gtk-primary-button-warps-slider</h3><p>") + tr(
        "If the value of this setting is %1, clicking the primary button in a <b>GtkRange</b> "
        "trough will move the slider, and hence set the range’s value, to the point that you clicked. "
        "If it is %2, a primary click will cause the slider/value to move by the range’s "
        "page-size towards the point clicked. Whichever action you choose for the primary button, "
        "the other action will be available by holding <b>Shift</b> and primary-clicking, "
        "or clicking the middle mouse button.").arg("<b>TRUE</b>", "<b>FALSE</b>") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>TRUE</b></p>")
    );
    gbxEnableRecentFiles->setToolTip(
        QString("<h3>gtk-recent-files-enabled</h3><p>") + tr(
        "Whether GTK should keep track of items inside the recently used resources list. "
        "If set to %1, the list will always be empty.").arg("<b>FALSE</b>") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>TRUE</b></p>")
    );
    lblRecentFilesMaxAge->setToolTip(
        QString("<h3>gtk-recent-files-max-age</h3><p>") + tr(
        "The maximum age, in days, of the items inside the recently used resources list. "
        "Items older than this setting will be excised from the list. "
        "If set to 0, the list will always be empty; if set to -1, no item will be removed.") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>30</b></p>")
    );
    lblSoundThemeName->setToolTip(
        QString("<h3>gtk-sound-theme-name</h3><p>") + tr(
        "The XDG sound theme to use for event sounds. "
        "See the Sound Theme Specifications for more information on event sounds and sound themes. "
        "GTK itself does not support event sounds, "
        "you have to use a loadable module like the one that comes with libcanberra.") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>freedesktop</b></p>")
    );
    lblDefaultFont->setToolTip(
        QString("<h3>gtk-font-name</h3><p>") + tr(
        "The default font to use. "
        "GTK uses the family name and size from this string.") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>Sans 10</b></p>")
    );
    chkXftAntialias->setToolTip(
        QString("<h3>gtk-xft-antialias</h3><p>") + tr(
        "Whether to antialias fonts. "
        "The values are: "
        "0 for no, 1 for yes or %1 for the system default.").arg("<b>-1</b>") + QString("</p>")
    );
    chkXftHinting->setToolTip(
        QString("<h3>gtk-xft-hinting</h3><p>") + tr(
        "Whether to enable font hinting. "
        "The values are: "
        "0 for no, 1 for yes or %1 for the system default.").arg("<b>-1</b>") + QString("</p>")
    );
    lblXftDpi->setToolTip(
        QString("<h3>gtk-xft-dpi</h3><p>") + tr(
        "The font resolution, in 1024 * dots/inch. "
        "%1 to use the default value.").arg("<b>-1</b>") + QString("</p>")
    );
    lblXftHintStyle->setToolTip(
        QString("<h3>gtk-xft-hintstyle</h3><p>") + tr(
        "What degree of font hinting to use. "
        "The possible values are %1.").arg("hintnone, hintslight, hintmedium, hintfull") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>NULL</b></p>")
    );
    lblXftRgba->setToolTip(
        QString("<h3>gtk-xft-rgba</h3><p>") + tr(
        "The type of subpixel antialiasing to use. "
        "The possible values are %1. "
        "Note that GSK does not support subpixel antialiasing, "
        "and this setting has no effect on font rendering in GTK.").arg("none, rgb, bgr, vrgb, vbgr") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>NULL</b></p>")
    );
}

void DialogMain::setupToolTipsGSettings() {
    lblColorScheme->setToolTip(
        QString("<h3>color-scheme</h3><p>") + tr(
        "The preferred color scheme for the user interface. "
        "Valid values are:") + QString("“default”, “prefer-dark”, “prefer-light”.</p><p>") + tr(
        "Default value") + QString(": <b>default</b></p>")
    );
    lblCursorThemeName->setToolTip(
        QString("<h3>cursor-theme</h3><p>") + tr(
        "Cursor theme name. Used only by Xservers that support the Xcursor extension.") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>24</b></p>")
    );
    lblCursorThemeSize->setToolTip(
        QString("<h3>cursor-size</h3><p>") + tr(
        "Size of the cursor used as cursor theme.") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>Adwaita</b></p>")
    );
    chkEnableEventSounds->setToolTip(
        QString("<h3>sound/event-sounds</h3><p>") + tr(
        "Whether to play sounds on user events.") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>true</b></p>")
    );
    chkEnableInputFeedbackSounds->setToolTip(
        QString("<h3>sound/input-feedback-sounds</h3><p>") + tr(
        "Whether to play sounds on input events.") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>false</b></p>")
    );
    lblGtkTheme->setToolTip(
        QString("<h3>gtk-theme</h3><p>") + tr(
        "Basename of the default theme used by gtk+.") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>Adwaita</b></p>")
    );
    lblIconThemeName->setToolTip(
        QString("<h3>icon-theme</h3><p>") + tr(
        "Icon theme to use for the panel, nautilus etc.") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>Adwaita</b></p>")
    );
    chkOverlayScrolling->setToolTip(
        QString("<h3>overlay-scrolling</h3><p>") + tr(
        "Whether scrollbars should be overlayed as indicators. "
        "Depending on input devices in use, permanent scrollbars may still be displayed.") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>true</b></p>")
    );
    gbxEnableRecentFiles->setToolTip(
        QString("<h3>privacy/remember-recent-files</h3><p>") + tr(
        "Whether to remember recently used files. "
        "If %1, applications will not remember recently used files.") + QString("</p><p>") + tr(
        "Default value").arg("<b>FALSE</b>") + QString(": <b>true</b></p>")
    );
    lblRecentFilesMaxAge->setToolTip(
        QString("<h3>privacy/recent-files-max-age</h3><p>") + tr(
        "Number of days to remember recently used files for. "
        "Recently used files will be remembered for this many days. "
        "If set to 0, recent files will not be remembered; "
        "if set to -1, they will be retained indefinitely.") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>-1</b></p>")
    );
    lblSoundThemeName->setToolTip(
        QString("<h3>sound/theme-name</h3><p>") + tr(
        "The XDG sound theme to use for event sounds.") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>freedesktop</b></p>")
    );
    lblDefaultFont->setToolTip(
        QString("<h3>font-name</h3><p>") + tr(
        "Name of the default font used by gtk+.") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>Cantarell 11</b></p>")
    );
    lblFontAntialiasing->setToolTip(
        QString("<h3>font-antialiasing</h3><p>") + tr(
        "The type of antialiasing to use when rendering fonts. Possible values are: "
        "%1 for no antialiasing, %2 for standard grayscale antialiasing, "
        "and %3 for subpixel antialiasing (LCD screens only).").arg("“none”", "“grayscale”", "“rgba”") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>grayscale</b></p>")
    );
    lblXftHintStyle->setToolTip(
        QString("<h3>font-hinting</h3><p>") + tr(
        "The type of hinting to use when rendering fonts. Possible values are: "
        "%1 for no hinting and %2 for fitting only to the Y-axis like Microsoft’s ClearType, "
        "DirectWrite and Adobe’s proprietary font rendering engine. Ignores native hinting within the font, "
        "generates hints algorithmically. Used on Ubuntu by default. Recommended. "
        "The meaning of %3 and %4 depends on the font format (.ttf, .otf, .pfa/.pfb) "
        "and the installed version of FreeType. "
        "They usually try to fit glyphs to both the X and the Y axis (except for .otf: Y-only). "
        "This can lead to distortion and/or inconsistent rendering depending on the quality of the font, "
        "the font format and the state of FreeType’s font engines.").arg("“none”", "“slight”", "“medium”", "“full”") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>slight</b></p>")
    );
    lblXftRgba->setToolTip(
        QString("<h3>font-rgba-order</h3><p>") + tr(
        "The order of subpixel elements on an LCD screen; only used when antialiasing is set to %1. "
        "Possible values are: %2 for red on left (most common), %3 for blue on left, "
        "%4 for red on top, %5 for red on bottom.").arg("“rgba”", "“rgb”", "“bgr”", "“vrgb”", "“vbgr”") + QString("</p><p>") + tr(
        "Default value") + QString(": <b>rgb</b></p>")
    );
}
