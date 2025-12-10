#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "MainWindow.h"
#include "Global.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QApplication::setApplicationName("lvgl-qt");
    QApplication::setApplicationDisplayName("LVGL Qt");
    QApplication::setOrganizationName("GT-Soft");
    QApplication::setApplicationVersion("1.0.0");
    QApplication::setOrganizationDomain("ruilx.top");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale: uiLanguages) {
        const QString baseName = "lvgl-qt_" + QLocale(locale).name();
        rDebug() << "Trying to load translation for locale:" << locale << "baseName:" << baseName;
        if (translator.load("i18n/" + baseName)) {
            QApplication::installTranslator(&translator);
            rDebug() << "Translation loaded successfully for locale:" << locale;
            break;
        }
    }

    MainWindow w;
    w.show();
    int returnCode = QApplication::exec();

    return returnCode;
}
