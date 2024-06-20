#include "gameboard.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QTimer>

GameBoard::GameBoard(QWidget *parent) : QWidget(parent), score(0), cardClicks(0) {
    QGridLayout *gridLayout = new QGridLayout(this);
    for (int i = 0; i < 9; ++i) {
        cards[i] = new QPushButton("Карта", this);
        connect(cards[i], &QPushButton::clicked, this, &GameBoard::onCardClicked);
        gridLayout->addWidget(cards[i], i / 3, i % 3);
    }

    resetButton = new QPushButton("Сброс", this);
    connect(resetButton, &QPushButton::clicked, this, &GameBoard::onResetButtonClicked);
    gridLayout->addWidget(resetButton, 3, 0);

    scoreLabel = new QLabel("Очки: 0", this);
    gridLayout->addWidget(scoreLabel, 3, 1);

    onResetButtonClicked();
}

void GameBoard::onCardClicked() {
    QPushButton *card = qobject_cast<QPushButton *>(sender());
    if (card) {
        int cardValue = card->property("value").toInt();
        score += cardValue;
        card->setText(QString::number(cardValue));
        card->setEnabled(false);
        cardClicks++;

        scoreLabel->setText("Очки: " + QString::number(score));

        if (cardClicks == 3) {
            QTimer::singleShot(0, this, &GameBoard::showResultMessage);
        }
    }
}

void GameBoard::onResetButtonClicked() {
    resetGame();
}

void GameBoard::showResultMessage() {
    QMessageBox::information(this, "Результат", "Вы набрали: " + QString::number(score) + " очков");
    resetGame();
}

void GameBoard::resetGame() {
    score = 0;
    cardClicks = 0;
    scoreLabel->setText("Очки: 0");
    for (int i = 0; i < 9; ++i) {
        int randomValue = QRandomGenerator::global()->bounded(-100, 101);
        cards[i]->setProperty("value", randomValue);
        cards[i]->setText("Карта");
        cards[i]->setEnabled(true);
    }
}

GameBoard::~GameBoard() {
}
