#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QList>
#include <QGroupBox>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QKeyEvent>

#include"back\tools\err.h"

class MainWindow : public QMainWindow{
    Q_OBJECT // 宏,包含了一大堆东西

public:
    explicit MainWindow(QWidget *parent = nullptr);
    // explicit:显式,不允许隐式调用
    ~MainWindow() override;

private slots:
    void switchTOstd();   // 切换到标准模式
    void switchTOhp();    // 切换到高精度模式
    void switchTOnt();    // 切换到数论模式
    void switchTOset();   // 切换到设置

    // 标准模式槽函数
    void onStdBtnClicked();
    void onStdCopy();

    // 高精度模式槽函数
    void onHpBtnClicked();
    void onHpCopy();

    // 数论模式槽函数
    void onNtCopySqrt();
    void onNtCopyFactor();
    void onNtCopyGcd();
    void onNtCopyLcm();
    void onNtCalcSqrt();
    void onNtCalcFactor();
    void onNtCalcGcd();
    void onNtCalcLcm();

    // 设置槽函数
    // TODO

private:
    void setupUI(); // 初始化界面
    void setupStdMd();
    void setupHpMd();
    void setupNtMd();
    void setupSet();

    void updateBtnStyle(QPushButton* activeBtn); // 更新按钮高亮
    void fadeSwitch(int index); // 淡出效果切换

    void StdMdCalc();
    void HpMdCalc();

    void StdErrShow(Err err_info);
    void HpErrShow(Err err_info);
    void NtSqrtErrShow(Err err_info);
    void NtFactorErrShow(Err err_info);
    void NtGcdErrShow(Err err_info);
    void NtLcmErrShow(Err err_info);

    QWidget* central_widget; // 中心窗口部件
    QVBoxLayout* main_layout; // 主布局,垂直
    QHBoxLayout* btn_layout; // 按钮布局,水平
    QStackedWidget* stacked_widget; // 堆叠窗口,用于切换面板

    QPushButton* std_md_btn; // 标准模式按钮
    QPushButton* hp_md_btn; // 高精度模式按钮
    QPushButton* nt_md_btn; // 数论模式按钮
    QPushButton* set_btn; // 设置按钮

    QWidget* std_md_panel; // 标准模式面板
    QWidget* hp_md_panel; // 高精度模式面板
    QWidget* nt_md_panel; // 数论模式面板
    QWidget* set_panel; // 设置面板

    // 标准模式控件
    QLineEdit* std_input;
    QTextEdit* std_output;
    QList<QPushButton*> std_btns;

    // 高精度模式控件
    QLineEdit* hp_input;
    QTextEdit* hp_output;
    QList<QPushButton*> hp_btns;

    // 数论模式控件
    QLineEdit* nt_sqrt_num;
    QTextEdit* nt_sqrt_res;
    QLineEdit* nt_factor_input;
    QTextEdit* nt_factor_res;
    QLineEdit* nt_gcd1;
    QLineEdit* nt_gcd2;
    QTextEdit* nt_gcd_res;
    QLineEdit* nt_lcm1;
    QLineEdit* nt_lcm2;
    QTextEdit* nt_lcm_res;

    // 设置控件
    // TODO

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // MAINWINDOW_H
