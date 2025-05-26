#ifndef SNAKE_QT_H
#define SNAKE_QT_H

#include <QDialog>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#include "../../brick_game/snake/backend_s.hpp"

namespace Ui {
class Snake;
}

// Определяем константы ncurses, если они не определены
// #ifndef KEY_UP
// #define KEY_UP 259
// #define KEY_DOWN 258
// #define KEY_LEFT 260
// #define KEY_RIGHT 261
// #endif

class Snake : public QDialog {
  Q_OBJECT

 public:
  explicit Snake(QWidget *parent = nullptr);
  ~Snake();

 protected:
  void paintEvent(QPaintEvent *) override;
  void keyPressEvent(QKeyEvent *) override;
  void closeEvent(QCloseEvent *event) override;

 private slots:
  void updateGame();

 private:
  Ui::Snake *ui;
  static const int CELL_SIZE = 30;  // Размер одной ячейки в пикселях
  s21::GameController game;         // Используем существующий контроллер игры
  QTimer *gameTimer;

  // void drawField(QPainter &painter);
  void startGame();
};

#endif  // SNAKE_QT_H
