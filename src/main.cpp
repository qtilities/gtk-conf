#include "DialogMain.hpp"

#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>

static void initLocale(QTranslator* qtTranslator, QTranslator* translator)
{
    QApplication* app = qApp;
#if PROJECT_TRANSLATION_TEST_ENABLED
    QLocale locale(QLocale(PROJECT_TRANSLATION_TEST));
    QLocale::setDefault(locale);
#else
    QLocale locale = QLocale::system();
#endif
    // Qt translations (buttons text and the like)
    QString translationsPath
        = QLibraryInfo::path(QLibraryInfo::TranslationsPath);

    QString translationsFileName = QStringLiteral("qt_") + locale.name();

    if (qtTranslator->load(translationsFileName, translationsPath))
        app->installTranslator(qtTranslator);

    // E.g. "<appname>_en"
    translationsFileName = QCoreApplication::applicationName().toLower() + '_' + locale.name();

    // Try first in the same binary directory, in case we are building,
    // otherwise read from system data
    translationsPath = QCoreApplication::applicationDirPath();

    bool isLoaded = translator->load(translationsFileName, translationsPath);
    if (!isLoaded)
    {
        // "/usr/share/<appname>/translations
        isLoaded = translator->load(translationsFileName,
            QStringLiteral(PROJECT_DATA_DIR) + QStringLiteral("/translations"));
    }
    if (isLoaded)
        app->installTranslator(translator);
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon::fromTheme("preferences-desktop-theme"));
    app.setApplicationName(APPLICATION_NAME);
    app.setApplicationDisplayName(APPLICATION_DISPLAY_NAME);
    app.setOrganizationName(ORGANIZATION_NAME);
    app.setOrganizationDomain(ORGANIZATION_DOMAIN);
    app.setApplicationVersion(APPLICATION_VERSION);

    QTranslator qtTranslator, translator;
    initLocale(&qtTranslator, &translator);

    DialogMain dialog;
    dialog.show();

    return app.exec();
}
