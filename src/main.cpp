#include <spdlog/spdlog.h>
#include <QApplication>
#include "ui/MainWindow.hpp"


int main(int argc, char *argv[]) {
    spdlog::info("Start KFlash Application");
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}