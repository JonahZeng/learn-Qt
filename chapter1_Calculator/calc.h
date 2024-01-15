#ifndef CALC_H
#define CALC_H

// #define DEBUG_MODE
// #define MACOS

#ifdef _DEBUG
#include <QDebug>
#endif

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QStringList>
#include <QTextEdit>
#include <QQueue>
#include <QTime>
#include <QStack>
#include "divzeroexception.h"

#define LOG_LINE 10

class PlusMinus : public QWidget {

  Q_OBJECT

  public:
    PlusMinus(QWidget *parent = 0);

  private slots:
    void on_btn1();
    void on_btn2();
    void on_btn3();
    void on_btn4();
    void on_btn5();
    void on_btn6();
    void on_btn7();
    void on_btn8();
    void on_btn9();
    void on_btn0();
    void on_btnPt();
    void on_btnClear();
    void on_btnPlus();
    void on_btnMins();
    void on_btnMult();
    void on_btnDiv();
    void on_btnEqual();
    void on_btnLeftBracket();
    void on_btnRightBracket();
  private:
    QTextEdit* m_showLog;
    QQueue<QString> m_log;

    QLabel *m_lbl; // real-time show input and result
    QString m_singleStr;  // stringlist <----- singlestr <----- input
    QStringList m_strList;
    unsigned short m_leftBkt_cnt; //input '(' count
    unsigned short m_rightBkt_cnt; //input ')' count

    bool lastIsNum();
    bool lastIsPoint();
    bool lastIsOperator();
    bool lastIsLeftBracket();
    bool lastIsRightBracket();
    bool lastIsNone(); //nothing input, all are empty
    void flushLog(QString ch);
    QString calcPopOut(QStringList& popOut);// pop is reverse order
    QString calcFinalOut(QStringList finalOut); // last string list, positive order
};

#endif // CALC_H
