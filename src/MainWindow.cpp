#include "MainWindow.hpp"

#include <QPushButton>
#include <QVBoxLayout>
#include <spdlog/spdlog.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    resize(960, 540);

    constexpr QSize resNHD{640,360};
    setMinimumSize(resNHD);

    constexpr QSize res4K{3840, 2160};
    setMaximumSize(res4K);

    setWindowTitle("KFlash");

    auto *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto *layout = new QVBoxLayout(centralWidget);

    lineEdit = new QLineEdit(centralWidget);
    lineEdit->setPlaceholderText("Enter Text");

    auto *button = new QPushButton("Click Me", this);

    layout->addWidget(lineEdit);
    layout->addWidget(button);

    connect(button, &QPushButton::released, this, &MainWindow::showLineEditText);
}

MainWindow::~MainWindow() {
}

void MainWindow::showLineEditText() {
    spdlog::info("{}", lineEdit->text().toStdString());
}