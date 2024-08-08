#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QPalette darkPalette;
    // Настраиваем палитру для цветовых ролей элементов интерфейса
    darkPalette.setColor(QPalette::Window, QColor("#1d2228"));
    darkPalette.setColor(QPalette::WindowText, QColor("#E1E2E2"));
    darkPalette.setColor(QPalette::Base, QColor("#1d2228"));
    darkPalette.setColor(QPalette::AlternateBase, QColor("#E1E2E2"));
    darkPalette.setColor(QPalette::ToolTipBase, QColor("#1d2228"));
    darkPalette.setColor(QPalette::ToolTipText, QColor("#E1E2E2"));
    darkPalette.setColor(QPalette::Text, QColor("#E1E2E2"));
    darkPalette.setColor(QPalette::Button, QColor("#1d2228"));
    darkPalette.setColor(QPalette::NoRole, QColor("#1d2228"));
//    darkPalette.setColor(QPalette::, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, QColor("#E1E2E2"));
    darkPalette.setColor(QPalette::BrightText, QColor("#1d2228"));
    darkPalette.setColor(QPalette::Link, QColor("#E1E2E2"));
    darkPalette.setColor(QPalette::Highlight, QColor("#E1E2E2"));
    darkPalette.setColor(QPalette::HighlightedText, QColor("#1d2228"));

    // Устанавливаем данную палитру
    qApp->setPalette(darkPalette);
    w.show();
    return a.exec();
}
