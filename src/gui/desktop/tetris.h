#ifndef TETRIS_H
#define TETRIS_H

#include <QColor>
#include <QDialog>
#include <QFile>
#include <QFont>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPainter>
#include <QRandomGenerator>
#include <QTextStream>
#include <QTimer>

// Подключаем заголовочные файлы оригинального тетриса
#include "../../brick_game/tetris/backend.h"
#include "../../brick_game/tetris/defines.h"
#include "exit.h"

class Tetris : public QDialog {
    Q_OBJECT

public:
    explicit Tetris(QWidget *parent = nullptr);
    ~Tetris();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    void gameLoop();
    void startGame();
    void pauseGame();
    void gameOver();
    void restartGame();

private:
    // Игровые константы
    static const int BLOCK_SIZE = 30;

    // Игровые переменные
    Field field;
    tetris_t currentFigure;
    QTimer *gameTimer;
    bool gameIsOn;
    bool isGameOver;
    bool isPaused;
    int lastLevel;

    // Цвета для фигур
    QColor colors[7];

    // Методы отрисовки
    void drawBoard(QPainter &painter);
    void drawFigure(QPainter &painter);
    void drawNextFigure(QPainter &painter);
    void drawScore(QPainter &painter);
};

#endif  // TETRIS_H
