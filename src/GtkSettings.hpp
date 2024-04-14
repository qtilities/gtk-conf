#pragma once

#include <QtCore/QObject>

namespace QGtkSettings
{
    Q_NAMESPACE
/**
    What degree of font hinting to use.
*/
    enum class XftHintStyle {
        hintnone,
        hintslight,
        hintmedium,
        hintfull
    };
    Q_ENUM_NS(XftHintStyle)

/**
    The type of subpixel antialiasing to use.
    @note GSK does not support subpixel antialiasing,
          and this setting has no effect on font rendering in GTK.
*/
    enum class XftRgba {
        none,
        rgb,
        bgr,
        vrgb,
        vbgr
    };
    Q_ENUM_NS(XftRgba)

} // namespace GtkSettings
