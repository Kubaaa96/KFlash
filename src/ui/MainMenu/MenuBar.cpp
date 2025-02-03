#include "ui\MainMenu\MenuBar.hpp"

#include <QApplication>
#include <QKeyEvent>
#include <spdlog/spdlog.h>

MenuBar::MenuBar(QWidget *parent) : QMenuBar(parent) {
    createFileMenu();
    createFlashcardMenu();
    createHelpMenu();

    addMenu(fileMenu);
    addMenu(flashcardMenu);
    addMenu(helpMenu);

    connectFileMenuActions();
    connectFlashcardActions();
    connectHelpActions();
}

MenuBar::~MenuBar() {}

void MenuBar::createFileMenu() {
    fileMenu = new QMenu("File", this);
    importAction = fileMenu->addAction("Import");
    exportAction = fileMenu->addAction("Export");
    exitAction = fileMenu->addAction("Exit");
}

void MenuBar::createFlashcardMenu() {
    flashcardMenu = new QMenu("Flashcard", this);
    createFlashcardAction = flashcardMenu->addAction("Create");
    openFlashcardDirAction = flashcardMenu->addAction("Open Flashcard Folder");
}

void MenuBar::createHelpMenu() {
    helpMenu = new QMenu("Help", this);
    aboutAction = helpMenu->addAction("About");
}

void MenuBar::connectFileMenuActions() {
    connect(importAction, &QAction::triggered, this, [] { spdlog::info("Import"); });
    connect(exportAction, &QAction::triggered, this, [] { spdlog::info("Export"); });
    connect(exitAction, &QAction::triggered, this, [] { QApplication::instance()->quit(); });
}

void MenuBar::connectFlashcardActions() {
    connect(createFlashcardAction, &QAction::triggered, this, [] { spdlog::info("Create Flashcard"); });
    connect(openFlashcardDirAction, &QAction::triggered, this, [] { spdlog::info("Open Flashcard Directory"); });
}

void MenuBar::connectHelpActions() {
    connect(aboutAction, &QAction::triggered, this, [] { spdlog::info("About"); });
}
