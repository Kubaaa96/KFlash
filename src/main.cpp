#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <QApplication>
#include "MainWindow.hpp"


int main(int argc, char *argv[]) {
    spdlog::info("Hello World\n");
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}