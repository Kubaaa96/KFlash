#pragma once

#include <QMainWindow>
#include <QLineEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void showLineEditText();

private:
    QLineEdit* lineEdit;

};