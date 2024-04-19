# GtkSettings and GSettings common properties

Here below all possible equivalent properties.
Note that GtkSettings is v4; in v3 there are some deprecated properties that currently works on GSettings,
like `gtk-im-preedit-style` and `gtk-im-status-style`, so we have to decide what to keep and what to exclude.

| Done  | Name                                | Type   | GSettings
| :---: | ---                                 | ---    | ---
|       | `gtk-alternative-button-order`      | bool   | N/A
|       | `gtk-alternative-sort-arrows`       | bool   | N/A
|   x   | `gtk-application-prefer-dark-theme` | bool   | `color-scheme`
|       | `gtk-cursor-aspect-ratio`           | double | N/A
|       | `gtk-cursor-blink`                  | bool   | `cursor-blink`
|       | `gtk-cursor-blink-time`             | int    | `cursor-blink-time`
|       | `gtk-cursor-blink-timeout`          | int    | `cursor-blink-timeout`
|   x   | `gtk-cursor-theme-name`             | string | `cursor-theme`
|   x   | `gtk-cursor-theme-size`             | int    | `cursor-size`
|       | `gtk-decoration-layout`             | string | `wm/button-layout`
|       | `gtk-dialogs-use-header`            | bool   | N/A
|       | `gtk-dnd-drag-threshold`            | int    | `peripherals/mouse/drag-threshold`
|       | `gtk-double-click-distance`         | int    | N/A
|       | `gtk-double-click-time`             | int    | `peripherals/mouse/double-click`
|       | `gtk-enable-accels`                 | bool   | N/A
|       | `gtk-enable-animations`             | bool   | `enable-animations`
|   x   | `gtk-enable-event-sounds`           | bool   | `sound/event-sounds` `privacy/disable-sound-output`?
|   x   | `gtk-enable-input-feedback-sounds`  | bool   | `sound/input-feedback-sounds`
|       | `gtk-enable-primary-paste`          | bool   | `gtk-enable-primary-paste`
|       | `gtk-entry-password-hint-timeout`   | int    | N/A
|       | `gtk-entry-select-on-focus`         | bool   | N/A
|       | `gtk-error-bell`                    | bool   | `wm/audible-bell`?
|   x   | `gtk-font-name`                     | string | `font-name`
|       | `gtk-fontconfig-timestamp`          | uint   | N/A
|       | `gtk-hint-font-metrics`             | bool   | N/A
|   x   | `gtk-icon-theme-name`               | string | `icon-theme`
|       | `gtk-im-module`                     | string | `gtk-im-module`
|       | `gtk-keynav-use-caret`              | bool   | N/A
|       | `gtk-label-select-on-focus`         | bool   | N/A
|       | `gtk-long-press-time`               | uint   | N/A
|   x   | `gtk-overlay-scrolling`             | bool   | `overlay-scrolling`
|   x   | `gtk-primary-button-warps-slider`   | bool   | N/A
|       | `gtk-print-backends`                | string | N/A
|       | `gtk-print-preview-command`         | string | N/A
|   x   | `gtk-recent-files-enabled`          | bool   | `privacy/remember-recent-files`
|   x   | `gtk-recent-files-max-age`          | int    | `privacy/recent-files-max-age`
|       | `gtk-shell-shows-app-menu`          | bool   | N/A
|       | `gtk-shell-shows-desktop`           | bool   | N/A
|       | `gtk-shell-shows-menubar`           | bool   | N/A
|       | `gtk-show-status-shapes`            | bool   | N/A
|   x   | `gtk-sound-theme-name`              | string | `sound/theme-name`
|       | `gtk-split-cursor`                  | bool   | N/A
|   x   | `gtk-theme-name`                    | string | `gtk-theme`
|       | `gtk-titlebar-double-click`         | string | `wm/action-double-click-titlebar`
|       | `gtk-titlebar-middle-click`         | string | `wm/action-middle-click-titlebar`
|       | `gtk-titlebar-right-click`          | string | `wm/action-right-click-titlebar`
|   x   | `gtk-xft-antialias`                 | int    | `font-antialiasing`
|   x   | `gtk-xft-dpi`                       | int    | N/A
|   x   | `gtk-xft-hinting`                   | int    | N/A
|   x   | `gtk-xft-hintstyle`                 | string | `font-hinting`
|   x   | `gtk-xft-rgba`                      | string | `font-rgba-order`
