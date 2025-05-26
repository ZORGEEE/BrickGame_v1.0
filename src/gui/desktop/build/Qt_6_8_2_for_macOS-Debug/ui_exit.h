/********************************************************************************
** Form generated from reading UI file 'exit.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXIT_H
#define UI_EXIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EXIT
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_YES;
    QPushButton *pushButton_NO;

    void setupUi(QWidget *EXIT)
    {
        if (EXIT->objectName().isEmpty())
            EXIT->setObjectName("EXIT");
        EXIT->resize(250, 120);
        horizontalLayoutWidget = new QWidget(EXIT);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 20, 231, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_YES = new QPushButton(horizontalLayoutWidget);
        pushButton_YES->setObjectName("pushButton_YES");

        horizontalLayout->addWidget(pushButton_YES);

        pushButton_NO = new QPushButton(horizontalLayoutWidget);
        pushButton_NO->setObjectName("pushButton_NO");

        horizontalLayout->addWidget(pushButton_NO);


        retranslateUi(EXIT);

        QMetaObject::connectSlotsByName(EXIT);
    } // setupUi

    void retranslateUi(QWidget *EXIT)
    {
        EXIT->setWindowTitle(QCoreApplication::translate("EXIT", "Form", nullptr));
        pushButton_YES->setText(QCoreApplication::translate("EXIT", "YES", nullptr));
        pushButton_NO->setText(QCoreApplication::translate("EXIT", "NO", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EXIT: public Ui_EXIT {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXIT_H
