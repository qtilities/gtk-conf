# GTK Settings

[![CI]](https://github.com/qtilities/gtk-conf/actions/workflows/build.yml)

## Overview

Configuration tool for GTK system properties.

## Dependencies

### Runtime

- Qt6 base

### Build

- CMake
- Qt Linguist Tools
- [Qtilitools] CMake modules
- Git (optional, to pull latest VCS checkouts)

## Build

`CMAKE_BUILD_TYPE` is usually set to `Release`, though `None` might be a valid [alternative].<br>
`CMAKE_INSTALL_PREFIX` has to be set to `/usr` on most operating systems.<br>
Using `sudo make install` is discouraged, instead use the system package manager where possible.

```bash
cmake -B build -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr -W no-dev
cmake --build build --verbose
DESTDIR="$(pwd)/package" cmake --install build
```

## Packages

[![Packaging status]](https://repology.org/project/gtk-conf/versions)

## Translations

For contributing translations the [LXQt Weblate] platform can be used.

[![Translation status]](https://translate.lxqt-project.org/widgets/qtilities/)

## Licenses

- Licensed under the [GPL-2.0-only] license.


[alternative]:          https://wiki.archlinux.org/title/CMake_package_guidelines#Fixing_the_automatic_optimization_flag_override
[CI]:                   https://github.com/qtilities/gtk-conf/actions/workflows/build.yml/badge.svg
[GPL-2.0-only]:         COPYING
[LXQt Weblate]:         https://translate.lxqt-project.org/projects/qtilities/gtk-conf/
[Packaging status]:     https://repology.org/badge/vertical-allrepos/gtk-conf.svg
[Qtilitools]:           https://github.com/qtilities/qtilitools/
[Translation status]:   https://translate.lxqt-project.org/widgets/qtilities/-/gtk-conf/multi-auto.svg
