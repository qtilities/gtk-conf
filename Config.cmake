#===============================================================================
# Editable project configuration
#
# Essential, non translatable application information (except DESCRIPTION).
# Translatable strings are passed via code.
#===============================================================================
list(APPEND PROJECT_CATEGORIES "Settings;DesktopSettings;Qt;X-XFCE-SettingsDialog;X-XFCE-PersonalSettings") # Freedesktop menu categories
list(APPEND PROJECT_KEYWORDS   "gtk;settings")
set(PROJECT_ID                 "gtk-conf")
set(PROJECT_DESCRIPTION        "Configuration tool for GTK system properties")
set(PROJECT_DISPLAY_NAME       "GTK Settings")
set(PROJECT_AUTHOR_NAME        "Andrea Zanellato")
set(PROJECT_AUTHOR_EMAIL       "redtid3@gmail.com") # Used also for organization email
set(PROJECT_COPYRIGHT_YEAR     "2024")  # TODO: from git
set(PROJECT_ORGANIZATION_NAME  "qtilities")  # Might be equal to PROJECT_AUTHOR_NAME
set(PROJECT_ORGANIZATION_URL   "${PROJECT_ORGANIZATION_NAME}.github.io")
set(PROJECT_HOMEPAGE_URL       "https://${PROJECT_ORGANIZATION_URL}/${PROJECT_ID}")
set(PROJECT_REPOSITORY_URL     "https://github.com/${PROJECT_ORGANIZATION_NAME}/${PROJECT_ID}")
set(PROJECT_REPOSITORY_BRANCH  "master")
set(PROJECT_SPDX_ID            "GPL-3.0-only")
set(PROJECT_TRANSLATIONS_DIR   "${CMAKE_SOURCE_DIR}/resources/translations")
#===============================================================================
# Appstream
#===============================================================================
set(PROJECT_APPSTREAM_SPDX_ID  "CC0-1.0")
set(PROJECT_APPSTREAM_ID       "gtk_conf")
#===============================================================================
# Adapt to CMake variables
#===============================================================================
set(${PROJECT_NAME}_DESCRIPTION  "${PROJECT_DESCRIPTION}")
set(${PROJECT_NAME}_HOMEPAGE_URL "${PROJECT_HOMEPAGE_URL}")
