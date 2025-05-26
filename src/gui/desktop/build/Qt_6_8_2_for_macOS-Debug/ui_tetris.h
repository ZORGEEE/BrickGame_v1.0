/********************************************************************************
** Form generated from reading UI file 'tetris.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TETRIS_H
#define UI_TETRIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tetris
{
public:

    void setupUi(QWidget *Tetris)
    {
        if (Tetris->objectName().isEmpty())
            Tetris->setObjectName("Tetris");
        Tetris->resize(400, 300);

        retranslateUi(Tetris);

        QMetaObject::connectSlotsByName(Tetris);
    } // setupUi

    void retranslateUi(QWidget *Tetris)
    {
        Tetris->setWindowTitle(QCoreApplication::translate("Tetris", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tetris: public Ui_Tetris {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TETRIS_H
