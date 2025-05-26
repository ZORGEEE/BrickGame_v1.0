#include "snake.h"
#include "exit.h"

#include <QCloseEvent>
#include <QKeyEvent>
#include <QPainter>

#include "ui_snake.h"

Snake::Snake(QWidget *parent) : QDialog(parent), game(200) {
  setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint | Qt::WindowTitleHint);
  setWindowTitle("Snake Game");

  // Фиксированный размер окна
  setFixedSize((BOARD_X - 1) * CELL_SIZE, (BOARD_Y - 1) * CELL_SIZE);

  // Отключаем стандартные кнопки диалога
  setModal(true);

  // Инициализация таймера
  gameTimer = new QTimer(this);
  connect(gameTimer, &QTimer::timeout, this, &Snake::updateGame);

  startGame();
}

Snake::~Snake() {
  delete ui;
  gameTimer->stop();
}

void Snake::closeEvent(QCloseEvent *event) {
  gameTimer->stop();
  // Сохраняем рекорд перед закрытием
  s21::SaveHighScore(game.highScore);
  event->accept();
  EXIT w;
  w.setModal(true);
  w.exec();
}

void Snake::startGame() { gameTimer->start(game.delay); }

void Snake::paintEvent(QPaintEvent *) {
  QPainter painter(this);

  // Заливаем фон черным
  painter.fillRect(rect(), Qt::black);

  // Рисуем границу
  painter.setPen(QPen(Qt::white, 2));
  painter.drawRect(1, 1, width() - 2, height() - 2);

  // Отрисовка змейки
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::green);
  const auto &tail = game.snake.GetTail();
  for (const auto &[tailX, tailY] : tail) {
    painter.fillRect(tailX * CELL_SIZE, tailY * CELL_SIZE, CELL_SIZE - 1,
                     CELL_SIZE - 1, Qt::green);
  }

  // Отрисовка еды
  painter.setBrush(Qt::red);
  painter.fillRect(game.food.GetX() * CELL_SIZE, game.food.GetY() * CELL_SIZE,
                   CELL_SIZE - 1, CELL_SIZE - 1, Qt::red);

  // Отрисовка счета и другой информации
  painter.setPen(Qt::white);
  painter.setFont(QFont("Arial", 12));
  painter.drawText(10, 20, QString("Score: %1").arg(game.score));
  painter.drawText(10, 40, QString("High Score: %1").arg(game.highScore));
  painter.drawText(10, 60, QString("Level: %1").arg(game.level));

  // Отрисовка различных состояний игры
  switch (game.gameState) {
    case s21::GameState::MENU:
      painter.drawText(rect(), Qt::AlignCenter, "Press Enter to Start");
      break;

    case s21::GameState::PAUSED:
      painter.drawText(rect(), Qt::AlignCenter,
                       "PAUSED\nPress Space to Continue");
      break;

    case s21::GameState::GAME_OVER:
      painter.drawText(rect(), Qt::AlignCenter,
                       "GAME OVER\nScore: " + QString::number(game.score) +
                           "\nPress Q to Quit");
      break;

    case s21::GameState::WIN:
      painter.drawText(rect(), Qt::AlignCenter,
                       "YOU WIN!\nScore: " + QString::number(game.score) +
                           "\nPress Q to Quit");
      break;

    default:
      break;
  }
}

void Snake::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape) {
    close();
  }

  // Преобразуем клавиши Qt в коды ncurses
  int key = 0;
  switch (event->key()) {
    case Qt::Key_Left:
      key = KEY_LEFT;
      break;
    case Qt::Key_Right:
      key = KEY_RIGHT;
      break;
    case Qt::Key_Up:
      key = KEY_UP;
      break;
    case Qt::Key_Down:
      key = KEY_DOWN;
      break;
    case Qt::Key_Space:
      key = ' ';  // Пробел для паузы
      break;
    case Qt::Key_Q:
      key = 'q';
      break;
    case Qt::Key_Plus:
      key = '+';
      break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
      key = 10;  // Enter для начала игры
      break;
    case Qt::Key_E:
      key = 'e';  // Альтернативная клавиша для начала игры
      break;
    default:
      QDialog::keyPressEvent(event);
      return;
  }

  // Передаем код клавиши в игровой контроллер
  game.HandleInput(key);

  // Если была нажата Q и игра завершена, закрываем окно
  if (key == 'q' && (game.gameState == s21::GameState::GAME_OVER ||
                     game.gameState == s21::GameState::WIN)) {
    s21::SaveHighScore(game.highScore);
    close();
    EXIT w;
    w.setModal(true);
    w.exec();
  }
}

void Snake::updateGame() {
  game.Update();
  update();  // Перерисовка виджета

  // Обновление скорости таймера, если изменился delay
  if (gameTimer->interval() != game.delay) {
    gameTimer->setInterval(game.delay);
  }
}
