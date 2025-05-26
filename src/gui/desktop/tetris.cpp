#include "tetris.h"

#include <QMessageBox>
#include <QRandomGenerator>

// Конструктор
Tetris::Tetris(QWidget *parent)
    : QDialog(parent), isPaused(false), isGameOver(false), gameIsOn(true) {
    // Устанавливаем фиксированный размер окна
    setFixedSize(BOARD_X * BLOCK_SIZE + 200, BOARD_Y * BLOCK_SIZE + 40);
    setWindowTitle("Tetris");

    // Убираем стандартные кнопки диалога
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    // Инициализируем цвета для фигур
    colors[0] = QColor(0, 255, 255);  // I - голубой
    colors[1] = QColor(255, 255, 0);  // O - желтый
    colors[2] = QColor(255, 165, 0);  // T - оранжевый
    colors[3] = QColor(0, 255, 0);    // S - зеленый
    colors[4] = QColor(255, 0, 0);    // Z - красный
    colors[5] = QColor(0, 0, 255);    // J - синий
    colors[6] = QColor(255, 0, 255);  // L - фиолетовый

    // Создаем таймер для игрового цикла
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &Tetris::gameLoop);

    // Инициализируем игру
    srand(time(NULL));  // Инициализируем генератор случайных чисел
    field = init_field();

    // Создаем начальную фигуру
    currentFigure = FIGURE.type[field.next];
    field.next = rand() % 7;

    // Запускаем игру
    startGame();
}

// Деструктор
Tetris::~Tetris() {
    gameTimer->stop();
    clean_field(&field);
}

// Игровой цикл - главный метод обновления игры
void Tetris::gameLoop() {
    if (!gameIsOn || isPaused) return;

    // Создаем временную копию фигуры для проверки
    tetris_t tempFigure = currentFigure;
    for (int i = 0; i < 4; i++) {
        tempFigure.y[i] += 1;
    }

    if (check(&field, tempFigure)) {
        // Фигура может двигаться вниз
        for (int i = 0; i < 4; i++) {
            currentFigure.y[i] += 1;
        }
    } else {
        // Фигура достигла дна или других блоков
        // Фиксируем её на поле
        for (int i = 0; i < 4; i++) {
            field.screen[currentFigure.y[i]][currentFigure.x[i]] = 1;
            // Проверка на проигрыш (фигура слишком высоко)
            if (currentFigure.y[i] <= PADDING + 1) {
                field.game_is_on = 0;
            }
        }

        // Генерируем новую фигуру
        currentFigure = FIGURE.type[field.next];
        field.next = rand() % 7;

    }
    // Если изменился уровень, обновляем скорость
    if (field.level != lastLevel) {
        lastLevel = field.level;
        gameTimer->setInterval(field.speed);
    }

    // Обновляем отображение
    update();

    // Проверяем, не закончилась ли игра
    if (!field.game_is_on) {
        gameOver();
    }
    check_fild(&field);
}

void Tetris::keyPressEvent(QKeyEvent *event) {
    if (isGameOver) {
        // Если игра окончена, обрабатываем только клавишу R для перезапуска
        if (event->key() == Qt::Key_R) {
            restartGame();
        }
        return;
    }

    if (event->key() == Qt::Key_Space) {
        // Пауза/снятие с паузы по пробелу
        pauseGame();
        return;
    }

    if (isPaused) return; // Остальные клавиши не обрабатываем в режиме паузы

    // Создаем временную копию фигуры для проверки
    tetris_t tempFigure = currentFigure;

    switch (event->key()) {
    case Qt::Key_Left:
        // Проверяем движение влево
        for (int i = 0; i < 4; i++) {
            tempFigure.x[i] -= 1;
        }
        if (check(&field, tempFigure)) {
            // Применяем движение
            for (int i = 0; i < 4; i++) {
                currentFigure.x[i] -= 1;
            }
        }
        break;

    case Qt::Key_Right:
        // Проверяем движение вправо
        for (int i = 0; i < 4; i++) {
            tempFigure.x[i] += 1;
        }
        if (check(&field, tempFigure)) {
            // Применяем движение
            for (int i = 0; i < 4; i++) {
                currentFigure.x[i] += 1;
            }
        }
        break;

    case Qt::Key_Down:
        // Проверяем движение вниз
        for (int i = 0; i < 4; i++) {
            tempFigure.y[i] += 1;
        }
        if (check(&field, tempFigure)) {
            // Применяем движение
            for (int i = 0; i < 4; i++) {
                currentFigure.y[i] += 1;
            }
        }
        break;

    case Qt::Key_Up:
        // Временная копия для проверки поворота
        tempFigure = currentFigure;
        // Используем логику поворота из оригинального кода
        if (tempFigure.type == 0) {
            swap_type_0(&tempFigure);
        } else if (tempFigure.type == 1) {
            swap_type_1(&tempFigure);
        } else if (tempFigure.type == 2) {
            swap_type_2(&tempFigure);
        } else if (tempFigure.type == 4) {
            swap_type_4(&tempFigure);
        } else if (tempFigure.type == 5) {
            swap_type_5(&tempFigure);
        } else if (tempFigure.type == 6) {
            swap_type_6(&tempFigure);
        }

        // Проверяем возможность поворота
        if (check(&field, tempFigure)) {
            // Применяем поворот
            currentFigure = tempFigure;
        }
        break;

    case Qt::Key_Escape:
        close();
        return;
    }

    // Обновляем отображение
    update();
}

// Отрисовка игрового поля
void Tetris::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Рисуем фон
    painter.fillRect(rect(), QColor(40, 40, 40));

    // Рисуем игровые элементы
    drawBoard(painter);
    drawFigure(painter);
    drawNextFigure(painter);
    drawScore(painter);

    // Рисуем сообщение о паузе поверх всего
    if (isPaused) {
        painter.fillRect(rect(),
                         QColor(0, 0, 0, 128));  // Полупрозрачный черный фон
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 20, QFont::Bold));
        painter.drawText(rect(), Qt::AlignCenter, "PAUSE\nPress SPACE to continue");
    }

    if (isGameOver) {
        painter.fillRect(rect(), QColor(0, 0, 0, 128));
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 20, QFont::Bold));
        painter.drawText(rect(), Qt::AlignCenter,
                         "GAME OVER\nScore: " + QString::number(field.score) +
                             "\nHigh Score: " + QString::number(field.high_score) +
                             "\nPress R to restart");
    }
}

// Отрисовка игрового поля
void Tetris::drawBoard(QPainter &painter) {
    // Рисуем сетку и фон для всего поля
    for (int i = 1; i < BOARD_Y; i++) {
        for (int j = 1; j < BOARD_X; j++) {
            QRect rect(j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE - 1,
                       BLOCK_SIZE - 1);
            // Рисуем серый фон для пустых клеток
            painter.fillRect(rect, QColor(50, 50, 50));
            // Рисуем заполненные клетки
            if (field.screen[i + PADDING][j + PADDING] > 0) {
                painter.fillRect(
                    rect, colors[field.screen[i + PADDING][j + PADDING] == 2
                               ? 0
                               : field.screen[i + PADDING][j + PADDING] - 1]);
            }
        }
    }
}

// Отрисовка текущей фигуры
void Tetris::drawFigure(QPainter &painter) {
    for (int i = 0; i < 4; i++) {
        if (currentFigure.y[i] >= PADDING) {
            painter.fillRect((currentFigure.x[i] - PADDING) * BLOCK_SIZE,
                             (currentFigure.y[i] - PADDING) * BLOCK_SIZE,
                             BLOCK_SIZE - 1, BLOCK_SIZE - 1,
                             colors[currentFigure.type]);
        }
    }
}

// Отрисовка следующей фигуры
void Tetris::drawNextFigure(QPainter &painter) {
    int offsetX = (BOARD_X - PADDING) * BLOCK_SIZE + 50;
    int offsetY = 50;

    // Рисуем заголовок
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(offsetX, offsetY, "Next:");

    // Получаем следующую фигуру из шаблона
    tetris_t nextFigure = FIGURE.type[field.next];

    // Вычисляем центр для отрисовки
    int minX = 4, maxX = 0, minY = 4, maxY = 0;
    for (int i = 0; i < 4; i++) {
        minX = qMin(minX, nextFigure.x[i]);
        maxX = qMax(maxX, nextFigure.x[i]);
        minY = qMin(minY, nextFigure.y[i]);
        maxY = qMax(maxY, nextFigure.y[i]);
    }

    // Рисуем фигуру по центру preview-области
    for (int i = 0; i < 4; i++) {
        painter.fillRect(offsetX + (nextFigure.x[i] - minX) * BLOCK_SIZE,
                         offsetY + 20 + (nextFigure.y[i] - minY) * BLOCK_SIZE,
                         BLOCK_SIZE - 1, BLOCK_SIZE - 1, colors[field.next]);
    }
}

// Отрисовка счета
void Tetris::drawScore(QPainter &painter) {
    int offsetX = BOARD_X * BLOCK_SIZE + 50;
    int offsetY = 200;

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));

    painter.drawText(offsetX, offsetY, "Score: " + QString::number(field.score));
    painter.drawText(offsetX, offsetY + 20,
                     "High Score: " + QString::number(field.high_score));
    painter.drawText(offsetX, offsetY + 40,
                     "Level: " + QString::number(field.level));
}

// Начало новой игры
void Tetris::startGame() {
    gameIsOn = true;
    isPaused = false;
    isGameOver = false;
    lastLevel = field.level;
    gameTimer->start(field.speed);
}

// Перезапуск игры после завершения
void Tetris::restartGame() {
    clean_field(&field);
    field = init_field();
    currentFigure = FIGURE.type[field.next];
    field.next = rand() % 7;
    startGame();
}

// Пауза игры
void Tetris::pauseGame() {
    isPaused = !isPaused;
    if (isPaused) {
        gameTimer->stop();
    } else {
        gameTimer->start(field.speed);
    }
    update();
}

// Окончание игры
void Tetris::gameOver() {
    isGameOver = true;
    gameIsOn = false;
    gameTimer->stop();
    update();
}

// Обработка закрытия окна
void Tetris::closeEvent(QCloseEvent *event) {
    gameTimer->stop();
    event->accept();
}
