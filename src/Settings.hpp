#pragma once

#include <QObject>
#include <QString>

typedef struct _GSettings GSettings;

class QFileSystemWatcher;

class Settings : public QObject
{
    Q_OBJECT

public:
    Settings(QObject* parent = nullptr);
    ~Settings();

    void load();
    void save();

    bool isWayland() const { return isWayland_; }
    int saving() const { return saving_; }
#if 0
    int allowVolumeAbove100() const { return allowVolumeAbove100_; }
    void setAllowVolumeAbove100(int allowVolumeAbove100) { allowVolumeAbove100_ = allowVolumeAbove100; }
#endif
    bool enableEventSounds() const { return enableEventSounds_; }
    void setEnableEventSounds(bool enableEventSounds) { enableEventSounds_ = enableEventSounds; }

    bool enableInputFeedbackSounds() const { return enableInputFeedbackSounds_; }
    void setEnableInputFeedbackSounds(bool enableInputFeedbackSounds) { enableInputFeedbackSounds_ = enableInputFeedbackSounds; }

    bool enableRecentFiles() const { return enableRecentFiles_; }
    void setEnableRecentFiles(bool enableRecentFiles) { enableRecentFiles_ = enableRecentFiles; }

    bool overlayScrolling() const { return overlayScrolling_; }
    void setOverlayScrolling(bool overlayScrolling) { overlayScrolling_ = overlayScrolling; }

    bool preferDarkTheme() const { return preferDarkTheme_; }
    void setPreferDarkTheme(bool preferDarkTheme) { preferDarkTheme_ = preferDarkTheme; }

    bool warpSlider() const { return warpSlider_; }
    void setWarpSlider(bool warpSlider) { warpSlider_ = warpSlider; }

    int cursorThemeSize() const { return cursorThemeSize_; }
    void setCursorThemeSize(int cursorThemeSize) { cursorThemeSize_ = cursorThemeSize; }

    int recentFilesMaxAge() const { return recentFilesMaxAge_; }
    void setRecentFilesMaxAge(int recentFilesMaxAge) { recentFilesMaxAge_ = recentFilesMaxAge; }

    int xftAntialias() const { return xftAntialias_; }
    void setXftAntialias(int xftAntialias) { xftAntialias_ = xftAntialias; }

    int xftHinting() const { return xftHinting_; }
    void setXftHinting(int xftHinting) { xftHinting_ = xftHinting; }

    int xftDpi() const { return xftDpi_; }
    void setXftDpi(int xftDpi) { xftDpi_ = xftDpi; }

    int scaleFactor() const { return scaleFactor_; }
    void setScaleFactor(int scaleFactor) { scaleFactor_ = scaleFactor; }

    qreal textScaleFactor() const { return textScaleFactor_; }
    void setTextScaleFactor(qreal textScaleFactor) { textScaleFactor_ = textScaleFactor; }

    QString colorScheme() const { return colorScheme_; }
    void setColorScheme(const QString& colorScheme) { colorScheme_ = colorScheme; }

    QString cursorThemeName() const { return cursorThemeName_; }
    void setCursorThemeName(const QString& cursorThemeName) { cursorThemeName_ = cursorThemeName; }

    QString fontAntialiasing() const { return fontAntialiasing_; }
    void setFontAntialiasing(const QString& fontAntialiasing) { fontAntialiasing_ = fontAntialiasing; }

    QString fontName() const { return fontName_; }
    void setFontName(const QString& fontName) { fontName_ = fontName; }

    QString iconThemeName() const { return iconThemeName_; }
    void setIconThemeName(const QString& iconThemeName) { iconThemeName_ = iconThemeName; }

    QString soundThemeName() const { return soundThemeName_; }
    void setSoundThemeName(const QString& soundThemeName) { soundThemeName_ = soundThemeName; }

    QString themeName() const { return themeName_; }
    void setThemeName(const QString& themeName) { themeName_ = themeName; }

    QString xftHintStyle() const { return xftHintStyle_; }
    void setXftHintStyle(const QString& xftHintStyle) { xftHintStyle_ = xftHintStyle; }

    QString xftRgba() const { return xftRgba_; }
    void setXftRgba(const QString& xftRgba) { xftRgba_ = xftRgba; }

Q_SIGNALS:
    void propertiesChanged();

private:
    void loadGSettings();
    void saveGSettings();

    void loadIniSettings();
    void saveIniSettings();

    GSettings *guiSettings_,
              *prvSettings_,
              *sndSettings_;
    bool isWayland_;
    bool saving_;

    QFileSystemWatcher* fsWatcher_;

//  int allowVolumeAbove100_;
    bool enableEventSounds_;
    bool enableInputFeedbackSounds_;
    bool enableRecentFiles_;
    bool overlayScrolling_;
    bool preferDarkTheme_;
    bool warpSlider_;
    int cursorThemeSize_;
    int recentFilesMaxAge_;
    int xftAntialias_;
    int xftHinting_;
    int xftDpi_;
    int scaleFactor_;
    qreal textScaleFactor_;
    QString colorScheme_;
    QString cursorThemeName_;
    QString fontName_;
    QString fontAntialiasing_;
    QString iconThemeName_;
    QString soundThemeName_;
    QString themeName_;
    QString xftHintStyle_;
    QString xftRgba_;
};
