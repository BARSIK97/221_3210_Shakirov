#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

class GameBoard : public QWidget {
    Q_OBJECT

public:
    explicit GameBoard(QWidget *parent = nullptr);
    ~GameBoard();

public slots:
    void onCardClicked();
    void onResetButtonClicked();
    void resetGame();

private:
    QPushButton *cards[9];
    QPushButton *resetButton;
    QLabel *scoreLabel;
    int score;
    int cardClicks;
    void showResultMessage();
};

#endif
