#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameboard.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->edtPin, &QLineEdit::returnPressed, this, &MainWindow::onLoginButtonClicked);
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::onLoginButtonClicked);

    gameBoard = nullptr;
}

void MainWindow::onLoginButtonClicked() {
    QString pinCode = ui->edtPin->text();
    if (pinCode == "1234") {
        if (!gameBoard) {
            gameBoard = new GameBoard(this);
            ui->stackedWidget->addWidget(gameBoard);
        }
        ui->stackedWidget->setCurrentWidget(gameBoard);
        gameBoard->resetGame();
    } else {
        ui->lblLogin->setText("Неверный пинкод");
        ui->lblLogin->setStyleSheet("color:red;");
    }
}

MainWindow::~MainWindow() {
    delete ui;
    if (gameBoard) {
        delete gameBoard;
    }
}
