#pragma once

#include <QMenuBar>

class MenuBar : public QMenuBar {
    Q_OBJECT

public:
    explicit MenuBar(QWidget *parent = nullptr);
    ~MenuBar() override;
private:

    void createFileMenu();
    void createFlashcardMenu();
    void createHelpMenu();

    void connectFileMenuActions();
    void connectFlashcardActions();
    void connectHelpActions();

    QMenu *fileMenu;
    QAction *importAction;
    QAction *exportAction;
    QAction *exitAction;

    QMenu *flashcardMenu;
    QAction *createFlashcardAction;
    QAction *openFlashcardDirAction;

    QMenu *helpMenu;
    QAction *aboutAction;
};