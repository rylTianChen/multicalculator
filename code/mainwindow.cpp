#include "mainwindow.h"
#include <QFont>
#include <QTimer>
#include<string>
#include"back\calc_func.h"
#include"back\tools\convert_func.h"
#include"back\tools\err.h"
#include"back\tools\hpcalc.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
}

MainWindow::~MainWindow() {}

QString pretty_style =
    // 按钮样式
    "QPushButton {"
    "   background-color: #f0f0f0;"
    "   border: 1px solid #d0d0d0;"
    "   border-radius: 6px;"
    "   padding: 4px;"
    "   font-weight: bold;"
    "}"
    "QPushButton:hover {"
    "   background-color: #e0e0e0;"
    "   border-color: #f39c12;"
    "}"
    "QPushButton:pressed {"
    "   background-color: #d0d0d0;"
    "}"

    // 输入框
    "QLineEdit {"
    "   border: 1px solid #d0d0d0;"
    "   border-radius: 6px;"
    "   padding: 4px;"
    "   font-size: 14px;"
    "}"
    "QLineEdit:focus {"
    "   border-color: #f39c12;"
    "}"

    // 输出框
    "QTextEdit {"
    "   border: 1px solid #d0d0d0;"
    "   border-radius: 6px;"
    "   padding: 4px;"
    "   background-color: #fafafa;"
    "}"

    // 新增：QGroupBox 样式
    "QGroupBox {"
    "   border: 1px solid #d0d0d0;"
    "   border-radius: 6px;"
    "   margin-top: 6px;"
    "   padding-top: 6px;"
    "   font-weight: bold;"
    "}"
    "QGroupBox::title {"
    "   subcontrol-origin: margin;"
    "   left: 10px;"
    "   padding: 0 5px 0 5px;"
    "}";

constexpr int DIRECT_SHOW_LENGTH_LIMIT = 100;

void MainWindow::setupUI(){
    setFixedSize(500, 650); // 设置窗口大小
    setWindowTitle("高精度多功能计算器");

    central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    main_layout = new QVBoxLayout(central_widget);
    main_layout->setSpacing(10);
    main_layout->setContentsMargins(10, 10, 10, 10);

    btn_layout = new QHBoxLayout();
    btn_layout->setSpacing(10); // 按钮之间间距

    // 创建三个按钮
    std_md_btn = new QPushButton("标准模式");
    hp_md_btn = new QPushButton("高精度模式");
    nt_md_btn = new QPushButton("数论工具");

    // 设置按钮固定大小
    int btn_width = 160, btn_height = 40;
    std_md_btn->setFixedSize(btn_width, btn_height);
    hp_md_btn->setFixedSize(btn_width, btn_height);
    nt_md_btn->setFixedSize(btn_width, btn_height);

    // 设置按钮字体
    QFont btn_font;
    btn_font.setPointSize(12);
    std_md_btn->setFont(btn_font);
    hp_md_btn->setFont(btn_font);
    nt_md_btn->setFont(btn_font);

    // 把按钮添加到水平布局
    btn_layout->addStretch();
    btn_layout->addWidget(std_md_btn);
    btn_layout->addWidget(hp_md_btn);
    btn_layout->addWidget(nt_md_btn);
    btn_layout->addStretch();

    stacked_widget = new QStackedWidget(); // 创建堆叠窗口,用于切换面板

    // 创建三个面板
    setupStdMd();
    setupHpMd();
    setupNtMd();

    // 把三个面板加入堆叠窗口
    stacked_widget->addWidget(std_md_panel); // 索引0
    stacked_widget->addWidget(hp_md_panel); // 索引1
    stacked_widget->addWidget(nt_md_panel); // 索引2

    // 组装布局
    main_layout->addLayout(btn_layout); // 顶部按钮栏
    main_layout->addWidget(stacked_widget); // 内容区域 堆叠窗口

    // 连接信号槽
    connect(std_md_btn, &QPushButton::clicked, this, &MainWindow::switchTOstd);
    connect(hp_md_btn, &QPushButton::clicked, this, &MainWindow::switchTOhp);
    connect(nt_md_btn, &QPushButton::clicked, this, &MainWindow::switchTOnt);

    switchTOstd(); // 默认标准模式

    setWindowFlags(windowFlags() & ~Qt::WindowSystemMenuHint);
    this->installEventFilter(this); // 监听自己的键盘事件
}

void MainWindow::fadeSwitch(int index){
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(stacked_widget);
    stacked_widget->setGraphicsEffect(effect);

    QPropertyAnimation* animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(200); // 200毫秒淡入淡出
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setEasingCurve(QEasingCurve::InOutQuad);

    stacked_widget->setCurrentIndex(index);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}
void MainWindow::switchTOstd(){
    fadeSwitch(0); // std面板索引为0
    updateBtnStyle(std_md_btn);
}
void MainWindow::switchTOhp(){
    fadeSwitch(1); // hp面板索引为1
    updateBtnStyle(hp_md_btn);
}
void MainWindow::switchTOnt(){
    fadeSwitch(2); // nt面板索引为2
    updateBtnStyle(nt_md_btn);
}

void MainWindow::updateBtnStyle(QPushButton* active_btn){
    // 所有按钮恢复普通样式
    QString normal_style =
        "QPushButton {"
        "   background-color: #e0e0e0;"
        "   border: none;"
        "   border-radius: 8px;"
        "   font-weight: normal;"
        "}"
        "QPushButton:hover {"
        "   background-color: #c0c0c0;"
        "}";

    // 高亮按钮样式
    QString active_style =
        "QPushButton {"
        "   background-color: #f39c12;"
        "   border: none;"
        "   border-radius: 8px;"
        "   font-weight: bold;"
        "   color: white;"
        "}"
        "QPushButton:hover {"
        "   background-color: #e67e22;"
        "}";

    std_md_btn->setStyleSheet(normal_style);
    hp_md_btn->setStyleSheet(normal_style);
    nt_md_btn->setStyleSheet(normal_style);
    active_btn->setStyleSheet(active_style);
}

void MainWindow::setupStdMd(){
    std_md_panel = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(std_md_panel);
    layout->setSpacing(10);
    layout->setContentsMargins(10, 10, 10, 10);

    // 介绍文字 - 固定高度
    QLabel* intro = new QLabel("支持小数，运算范围：-2e9 ~ +2e9，适合日常使用");
    intro->setStyleSheet("color: #888; font-size: 16px; background-color: transparent;");
    intro->setAlignment(Qt::AlignCenter);
    intro->setFixedHeight(25);  // 固定高度
    intro->setWordWrap(true);   // 文字过长时自动换行
    layout->addWidget(intro);

    // 输入框
    std_input = new QLineEdit();
    std_input->setPlaceholderText("输入表达式，例如: 123 + 456*789");
    std_input->setStyleSheet("font-size: 18px; padding: 8px;");
    std_input->setReadOnly(true);
    layout->addWidget(std_input);

    // 输出框+复制按钮
    QHBoxLayout* output_layout = new QHBoxLayout();
    std_output = new QTextEdit();
    std_output->setReadOnly(true);
    std_output->setPlaceholderText("计算结果");
    std_output->setStyleSheet("font-size: 16px; background-color: #f5f5f5;");
    std_output->setMaximumHeight(100);
    output_layout->addWidget(std_output);

    QPushButton* copy_btn = new QPushButton("复制");
    copy_btn->setFixedSize(60, 100);
    copy_btn->setStyleSheet("font-size: 14px;");
    connect(copy_btn, &QPushButton::clicked, this, &MainWindow::onStdCopy);
    output_layout->addWidget(copy_btn);
    layout->addLayout(output_layout);

    // 按钮网格
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setSpacing(8);

    QStringList btns = {
        "7", "8", "9", "/", "C",
        "4", "5", "6", "*", "(",
        "1", "2", "3", "-", ")",
        "0", ".", "=", "+", "Del"
    };

    int row = 0, col = 0;
    for(const QString& text : btns) {
        QPushButton* btn = new QPushButton(text);
        btn->setFixedSize(70, 50);
        btn->setStyleSheet("font-size: 16px;");
        gridLayout->addWidget(btn, row, col);
        std_btns.append(btn);
        col++;
        if (col >= 5) {
            col = 0;
            row++;
        }
    }
    layout->addLayout(gridLayout);

    // 连接按钮信号
    for (QPushButton* btn : std_btns) {
        connect(btn, &QPushButton::clicked, this, &MainWindow::onStdBtnClicked);
    }

    std_md_panel->setStyleSheet(pretty_style);
}
void MainWindow::onStdBtnClicked(){
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    QString text = btn->text();

    if(text == "=") {
        StdMdCalc();
    }
    else if(text == "C") {
        std_input->clear();
        std_output->clear();
    }
    else if(text == "Del") {
        QString current = std_input->text();
        if (!current.isEmpty()) current.chop(1);
        std_input->setText(current);
    }
    else{
        std_input->setText(std_input->text() + text);
    }
}
void MainWindow::onStdCopy(){
    std_output->selectAll();
    std_output->copy();
    // 取消选中
    QTimer::singleShot(100, [this]() {
        QTextCursor cursor = std_output->textCursor();
        cursor.clearSelection();
        std_output->setTextCursor(cursor);
    });
}

void MainWindow::setupHpMd(){
    hp_md_panel = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(hp_md_panel);
    layout->setSpacing(10);
    layout->setContentsMargins(10, 10, 10, 10);

    // 介绍文字 - 固定高度
    QLabel* intro = new QLabel("支持超大整数精确运算、部分位运算，但不支持小数");
    intro->setStyleSheet("color: #888; font-size: 16px; background-color: transparent;");
    intro->setAlignment(Qt::AlignCenter);
    intro->setFixedHeight(25);
    intro->setWordWrap(true);
    layout->addWidget(intro);

    // 输入框
    hp_input = new QLineEdit();
    hp_input->setPlaceholderText("输入表达式，例如: 12345678901234567890 + 98765432109876543210");
    hp_input->setStyleSheet("font-size: 18px; padding: 8px;");
    hp_input->setReadOnly(true);
    layout->addWidget(hp_input);

    // 输出框+复制按钮
    QHBoxLayout* output_layout = new QHBoxLayout();
    hp_output = new QTextEdit();
    hp_output->setReadOnly(true);
    hp_output->setPlaceholderText("计算结果会显示在这里");
    hp_output->setStyleSheet("font-size: 16px; background-color: #f5f5f5;");
    hp_output->setMaximumHeight(100);
    output_layout->addWidget(hp_output);

    QPushButton* copy_btn = new QPushButton("复制");
    copy_btn->setFixedSize(60, 100);
    copy_btn->setStyleSheet("font-size: 14px;");
    connect(copy_btn, &QPushButton::clicked, this, &MainWindow::onHpCopy);
    output_layout->addWidget(copy_btn);
    layout->addLayout(output_layout);

    // 按钮网格（高精度模式支持更多运算符）
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setSpacing(8);

    QStringList buttons = {
        "7", "8", "9", "/", "C",
        "4", "5", "6", "*", "^",
        "1", "2", "3", "-", "%",
        "0", "=", "+", "Del", " ",
        "&&", "|", "!", "(", ")"
    };

    int row = 0, col = 0;
    for(const QString& text : buttons) {
        QPushButton* btn = new QPushButton(text);
        btn->setFixedSize(60, 45);
        btn->setStyleSheet("font-size: 14px;");
        gridLayout->addWidget(btn, row, col);
        hp_btns.append(btn);
        col++;
        if(col >= 5) {
            col = 0;
            row++;
        }
    }
    layout->addLayout(gridLayout);

    // 连接按钮信号
    for(QPushButton* btn : hp_btns) {
        connect(btn, &QPushButton::clicked, this, &MainWindow::onHpBtnClicked);
    }

    hp_md_panel->setStyleSheet(pretty_style);
}
void MainWindow::onHpBtnClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if(!btn) return;

    QString text = btn->text();

    if(text == "=") {
        HpMdCalc();
    }
    else if(text == "C") {
        hp_input->clear();
        hp_output->clear();
    }
    else if(text == "Del") {
        QString current = hp_input->text();
        if (!current.isEmpty()) current.chop(1);
        hp_input->setText(current);
    }
    else{
        if(text == "&&") text = "&";
        hp_input->setText(hp_input->text() + text);
    }
}
void MainWindow::onHpCopy(){
    hp_output->selectAll();
    hp_output->copy();
    QTimer::singleShot(100, [this]() {
        QTextCursor cursor = hp_output->textCursor();
        cursor.clearSelection();
        hp_output->setTextCursor(cursor);
    });
}

void MainWindow::setupNtMd(){
    nt_md_panel = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(nt_md_panel);
    layout->setSpacing(15);
    layout->setContentsMargins(0, 0, 0, 0);

    // 介绍文字 - 固定高度
    QLabel* intro = new QLabel("一些简单数论功能，要求输入全部是正整数");
    intro->setStyleSheet("color: #888; font-size: 16px; background-color: transparent;");
    intro->setAlignment(Qt::AlignCenter);
    intro->setFixedHeight(25);
    layout->addWidget(intro);

    // ========== 1. 根号化简 ==========
    QGroupBox* sqrt_group = new QGroupBox("根号化简");
    QHBoxLayout* sqrt_layout = new QHBoxLayout(sqrt_group);

    QLabel* sqrtSymbol = new QLabel("√");
    sqrtSymbol->setStyleSheet("font-size: 18px;");
    nt_sqrt_num = new QLineEdit();
    nt_sqrt_num->setPlaceholderText("根号内数字");
    nt_sqrt_num->setFixedWidth(150);
    nt_sqrt_num->setFixedHeight(25);

    sqrt_layout->addWidget(sqrtSymbol);
    sqrt_layout->addWidget(nt_sqrt_num);
    sqrt_layout->addStretch();
    QPushButton* sqrt_calc_btn = new QPushButton("计算");
    sqrt_calc_btn->setFixedWidth(80);
    sqrt_calc_btn->setFixedHeight(25);
    connect(sqrt_calc_btn, &QPushButton::clicked, this, &MainWindow::onNtCalcSqrt);
    sqrt_layout->addWidget(sqrt_calc_btn);

    QHBoxLayout* sqrt_res_layout = new QHBoxLayout();
    nt_sqrt_res = new QTextEdit();
    nt_sqrt_res->setReadOnly(true);
    nt_sqrt_res->setPlaceholderText("化简结果");
    nt_sqrt_res->setMaximumHeight(60);
    nt_sqrt_res->setStyleSheet("background-color: #f5f5f5;");
    sqrt_res_layout->addWidget(nt_sqrt_res);

    QPushButton* sqrt_copy_btn = new QPushButton("复制");
    sqrt_copy_btn->setFixedSize(50, 50);
    connect(sqrt_copy_btn, &QPushButton::clicked, this, &MainWindow::onNtCopySqrt);
    sqrt_res_layout->addWidget(sqrt_copy_btn);

    layout->addWidget(sqrt_group);
    layout->addLayout(sqrt_res_layout);

    // ========== 2. 分解质因数 ==========
    QGroupBox* factor_group = new QGroupBox("分解质因数");
    QHBoxLayout* factor_input_layout = new QHBoxLayout();
    nt_factor_input = new QLineEdit();
    nt_factor_input->setPlaceholderText("请输入一个数");
    nt_factor_input->setStyleSheet("font-size: 14px;");
    nt_factor_input->setFixedHeight(25);
    factor_input_layout->addWidget(nt_factor_input);
    QPushButton* factor_calc_btn = new QPushButton("计算");
    factor_calc_btn->setFixedWidth(80);
    factor_calc_btn->setFixedHeight(25);
    connect(factor_calc_btn, &QPushButton::clicked, this, &MainWindow::onNtCalcFactor);
    factor_input_layout->addWidget(factor_calc_btn);
    factor_group->setLayout(factor_input_layout);

    QHBoxLayout* factor_res_layout = new QHBoxLayout();
    nt_factor_res = new QTextEdit();
    nt_factor_res->setReadOnly(true);
    nt_factor_res->setPlaceholderText("分解结果");
    nt_factor_res->setMaximumHeight(60);
    nt_factor_res->setStyleSheet("background-color: #f5f5f5;");
    factor_res_layout->addWidget(nt_factor_res);

    QPushButton* factor_copy_btn = new QPushButton("复制");
    factor_copy_btn->setFixedSize(50, 50);
    connect(factor_copy_btn, &QPushButton::clicked, this, &MainWindow::onNtCopyFactor);
    factor_res_layout->addWidget(factor_copy_btn);

    layout->addWidget(factor_group);
    layout->addLayout(factor_res_layout);

    // ========== 3. 最大公因数 ==========
    QGroupBox* gcd_group = new QGroupBox("最大公因数");
    QHBoxLayout* gcd_input_layout = new QHBoxLayout();
    nt_gcd1 = new QLineEdit();
    nt_gcd1->setPlaceholderText("数A");
    nt_gcd1->setFixedWidth(120);
    nt_gcd1->setFixedHeight(25);
    QLabel* comma1 = new QLabel(",");
    nt_gcd2 = new QLineEdit();
    nt_gcd2->setPlaceholderText("数B");
    nt_gcd2->setFixedWidth(120);
    nt_gcd2->setFixedHeight(25);
    QPushButton* gcd_calc_btn = new QPushButton("计算");
    gcd_calc_btn->setFixedWidth(80);
    gcd_calc_btn->setFixedHeight(25);
    connect(gcd_calc_btn, &QPushButton::clicked, this, &MainWindow::onNtCalcGcd);
    gcd_input_layout->addWidget(nt_gcd1);
    gcd_input_layout->addWidget(comma1);
    gcd_input_layout->addWidget(nt_gcd2);
    gcd_input_layout->addWidget(gcd_calc_btn);
    gcd_input_layout->addStretch();
    gcd_group->setLayout(gcd_input_layout);

    QHBoxLayout* gcd_res_layout = new QHBoxLayout();
    nt_gcd_res = new QTextEdit();
    nt_gcd_res->setReadOnly(true);
    nt_gcd_res->setPlaceholderText("最大公因数");
    nt_gcd_res->setMaximumHeight(60);
    nt_gcd_res->setStyleSheet("background-color: #f5f5f5;");
    gcd_res_layout->addWidget(nt_gcd_res);

    QPushButton* gcd_copy_btn = new QPushButton("复制");
    gcd_copy_btn->setFixedSize(50, 50);
    connect(gcd_copy_btn, &QPushButton::clicked, this, &MainWindow::onNtCopyGcd);
    gcd_res_layout->addWidget(gcd_copy_btn);

    layout->addWidget(gcd_group);
    layout->addLayout(gcd_res_layout);

    // ========== 4. 最小公倍数 ==========
    QGroupBox* lcm_group = new QGroupBox("最小公倍数");
    QHBoxLayout* lcm_input_layout = new QHBoxLayout();
    nt_lcm1 = new QLineEdit();
    nt_lcm1->setPlaceholderText("数A");
    nt_lcm1->setFixedWidth(120);
    nt_lcm1->setFixedHeight(25);
    QLabel* comma2 = new QLabel(",");
    nt_lcm2 = new QLineEdit();
    nt_lcm2->setPlaceholderText("数B");
    nt_lcm2->setFixedWidth(120);
    nt_lcm2->setFixedHeight(25);
    QPushButton* lcm_calc_btn = new QPushButton("计算");
    lcm_calc_btn->setFixedWidth(80);
    lcm_calc_btn->setFixedHeight(25);
    connect(lcm_calc_btn, &QPushButton::clicked, this, &MainWindow::onNtCalcLcm);
    lcm_input_layout->addWidget(nt_lcm1);
    lcm_input_layout->addWidget(comma2);
    lcm_input_layout->addWidget(nt_lcm2);
    lcm_input_layout->addWidget(lcm_calc_btn);
    lcm_input_layout->addStretch();
    lcm_group->setLayout(lcm_input_layout);

    QHBoxLayout* lcm_res_layout = new QHBoxLayout();
    nt_lcm_res = new QTextEdit();
    nt_lcm_res->setReadOnly(true);
    nt_lcm_res->setPlaceholderText("最小公倍数");
    nt_lcm_res->setMaximumHeight(60);
    nt_lcm_res->setStyleSheet("background-color: #f5f5f5;");
    lcm_res_layout->addWidget(nt_lcm_res);

    QPushButton* lcm_copy_btn = new QPushButton("复制");
    lcm_copy_btn->setFixedSize(50, 50);
    connect(lcm_copy_btn, &QPushButton::clicked, this, &MainWindow::onNtCopyLcm);
    lcm_res_layout->addWidget(lcm_copy_btn);

    layout->addWidget(lcm_group);
    layout->addLayout(lcm_res_layout);

    layout->addStretch();
    nt_md_panel->setStyleSheet(pretty_style);
}
void MainWindow::onNtCopySqrt(){
    nt_sqrt_res->selectAll();
    nt_sqrt_res->copy();
}
void MainWindow::onNtCopyFactor(){
    nt_factor_res->selectAll();
    nt_factor_res->copy();
}
void MainWindow::onNtCopyGcd(){
    nt_gcd_res->selectAll();
    nt_gcd_res->copy();
}
void MainWindow::onNtCopyLcm(){
    nt_lcm_res->selectAll();
    nt_lcm_res->copy();
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event){
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        int key = keyEvent->key();

        // 获取当前是哪个模式
        int current_index = stacked_widget->currentIndex();

        // 数字 0-9
        if (key >= Qt::Key_0 && key <= Qt::Key_9) {
            QString num = QString::number(key - Qt::Key_0);
            if (current_index == 0) {
                std_input->setText(std_input->text() + num);
            } else if (current_index == 1) {
                hp_input->setText(hp_input->text() + num);
            }
            return true;
        }

        // 功能按键
        switch(key){
            case Qt::Key_C:
                if (!(keyEvent->modifiers() & Qt::ControlModifier)) {
                    if (current_index == 0) {
                        std_input->clear();
                        std_output->clear();
                    } else if (current_index == 1) {
                        hp_input->clear();
                        hp_output->clear();
                    }
                    return true;
                }
                break;
            case Qt::Key_Delete: {
                QString current;
                if (current_index == 0) {
                    current = std_input->text();
                } else if (current_index == 1) {
                    current = hp_input->text();
                }
                if (!current.isEmpty()) current.chop(1);
                if (current_index == 0) {
                    std_input->setText(current);
                } else if (current_index == 1) {
                    hp_input->setText(current);
                }
                return true;
            }
            case Qt::Key_Backspace: {
                QString current;
                if (current_index == 0) {
                    current = std_input->text();
                } else if (current_index == 1) {
                    current = hp_input->text();
                }
                if (!current.isEmpty()) current.chop(1);
                if (current_index == 0) {
                    std_input->setText(current);
                } else if (current_index == 1) {
                    hp_input->setText(current);
                }
                return true;
            }
            case Qt::Key_Return:
            case Qt::Key_Enter:
            case Qt::Key_Equal:
                // 触发计算
                if (current_index == 0) {
                    // 触发标准模式的计算
                    StdMdCalc();
                } else if (current_index == 1) {
                    HpMdCalc();
                }
                return true;
        }

        // 运算符（注意：需要根据当前模式是否支持）
        switch (key) {
        case Qt::Key_Period:  // 小数点 .
            if (current_index == 0) {
                std_input->setText(std_input->text() + ".");
            }
            // 高精度模式不支持小数
            return true;
        case Qt::Key_Plus:
            if (current_index == 0) std_input->setText(std_input->text() + "+");
            else if (current_index == 1) hp_input->setText(hp_input->text() + "+");
            return true;
        case Qt::Key_Minus:
            if (current_index == 0) std_input->setText(std_input->text() + "-");
            else if (current_index == 1) hp_input->setText(hp_input->text() + "-");
            return true;
        case Qt::Key_Asterisk:  // Shift + 8
            if (current_index == 0) std_input->setText(std_input->text() + "*");
            else if (current_index == 1) hp_input->setText(hp_input->text() + "*");
            return true;
        case Qt::Key_Slash:
            if (current_index == 0) std_input->setText(std_input->text() + "/");
            else if (current_index == 1) hp_input->setText(hp_input->text() + "/");
            return true;
        case Qt::Key_AsciiCircum:  // ^
            if(current_index == 0) std_input->setText(std_input->text() + "^");
            if (current_index == 1) hp_input->setText(hp_input->text() + "^");
            return true;
        case Qt::Key_Percent:
            if (current_index == 1) hp_input->setText(hp_input->text() + "%");
            return true;
        case Qt::Key_Ampersand:  // &
            if (current_index == 1) hp_input->setText(hp_input->text() + "&");
            return true;
        case Qt::Key_Bar:  // |
            if (current_index == 1) hp_input->setText(hp_input->text() + "|");
            return true;
        case Qt::Key_Exclam:  // !
            if (current_index == 1) hp_input->setText(hp_input->text() + "!");
            return true;
        case Qt::Key_ParenLeft:
            if(current_index == 0) std_input->setText(std_input->text() + "(");
            if(current_index == 1) hp_input->setText(hp_input->text() + "(");
            return true;
        case Qt::Key_ParenRight:
            if(current_index == 0) std_input->setText(std_input->text() + ")");
            if(current_index == 1) hp_input->setText(hp_input->text() + ")");
            return true;
        }
    }

    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::StdMdCalc(){
    std_output->setText("正在计算中...");
    std_output->repaint();
    QString expr = std_input->text();
    double res = 0;
    try{
        res = StdCalcFunc((std_input->text()).toStdString());
    }catch(Err err_info){
        StdErrShow(err_info);
        return;
    }
    QString res_str = QString::fromStdString(doubleTOstr(res));
    if(!isDouble(res_str.toStdString())) StdErrShow(Err(CALC_ERR, -1, -1));
    else{
        std_output->setText(res_str);
        std_input->setText(res_str);
    }
}
void MainWindow::HpMdCalc(){
    hp_output->setText("正在计算中...");
    hp_output->repaint();
    QString expr = hp_input->text();
    HP res = 0;
    try{
        res = HpCalcFunc((hp_input->text()).toStdString());
    }catch(Err err_info){
        HpErrShow(err_info);
        return;
    }
    if(res.isEMPTY()) HpErrShow(Err(CALC_ERR, -1, -1));
    else{
        str res_std_str = str(res);
        QString res_str = QString::fromStdString(res_std_str);
        QString sci_res_str = "";
        if(res.size() > DIRECT_SHOW_LENGTH_LIMIT){
            sci_res_str = QString::fromStdString(numTOsci(res_std_str));
            hp_output->setText(sci_res_str + '\n' + res_str);
        }else{
            hp_output->setText(res_str);
        }
    }
}
void MainWindow::onNtCalcSqrt(){
    QString num = nt_sqrt_num->text();
    nt_sqrt_res->setText("正在计算中...");
    nt_sqrt_res->repaint();

    if(num.isEmpty()){
        nt_sqrt_res->setText("请输入一个数");
        nt_sqrt_num->clear();
        nt_sqrt_num->setPlaceholderText(num);
        return;
    }
    QString res;
    try{
        res = QString::fromStdString(NtSqrtFunc(num.toStdString()));
    }catch(Err err_info){
        NtSqrtErrShow(err_info);
        nt_sqrt_num->clear();
        nt_sqrt_num->setPlaceholderText(num);
        return;
    }
    nt_sqrt_res->setText(res);
    nt_sqrt_num->clear();
    nt_sqrt_num->setPlaceholderText(num);
}
void MainWindow::onNtCalcFactor(){
    QString num = nt_factor_input->text();
    nt_factor_res->setText("正在计算中...");
    nt_factor_res->repaint();

    if(num.isEmpty()){
        nt_factor_res->setText("请输入一个数");
        nt_factor_input->clear();
        nt_factor_input->setPlaceholderText(num);
        return;
    }
    QString res;
    try{
        res = QString::fromStdString(NtFactorFunc(num.toStdString()));
    }catch(Err err_info){
        NtFactorErrShow(err_info);
        nt_factor_input->clear();
        nt_factor_input->setPlaceholderText(num);
        return;
    }
    nt_factor_res->setText(res);
    nt_factor_input->clear();
    nt_factor_input->setPlaceholderText(num);
}
void MainWindow::onNtCalcGcd()
{
    QString a = nt_gcd1->text();
    QString b = nt_gcd2->text();
    nt_gcd_res->setText("正在计算中...");
    nt_gcd_res->repaint();
    if (a.isEmpty() || b.isEmpty()) {
        nt_gcd_res->setText("请输入两个数");
        nt_gcd1->clear(); nt_gcd1->setPlaceholderText(a);
        nt_gcd2->clear(); nt_gcd2->setPlaceholderText(b);
        return;
    }

    QString res;
    try{
        res = QString::fromStdString(NtGcdFunc(a.toStdString(), b.toStdString()));
    }catch(Err err_info){
        NtGcdErrShow(err_info);
        nt_gcd1->clear(); nt_gcd1->setPlaceholderText(a);
        nt_gcd2->clear(); nt_gcd2->setPlaceholderText(b);
        return;
    }
    nt_gcd_res->setText(res);
    nt_gcd1->clear(); nt_gcd1->setPlaceholderText(a);
    nt_gcd2->clear(); nt_gcd2->setPlaceholderText(b);
}
// 最小公倍数计算
void MainWindow::onNtCalcLcm()
{
    QString a = nt_lcm1->text();
    QString b = nt_lcm2->text();
    nt_lcm_res->setText("正在计算中...");
    nt_lcm_res->repaint();

    if (a.isEmpty() || b.isEmpty()) {
        nt_lcm_res->setText("请输入两个数");
        nt_lcm1->clear(); nt_lcm1->setPlaceholderText(a);
        nt_lcm2->clear(); nt_lcm2->setPlaceholderText(b);
        return;
    }

    QString res;
    try{
        res = QString::fromStdString(NtLcmFunc(a.toStdString(), b.toStdString()));
    }catch(Err err_info){
        NtLcmErrShow(err_info);
        nt_lcm1->clear(); nt_lcm1->setPlaceholderText(a);
        nt_lcm2->clear(); nt_lcm2->setPlaceholderText(b);
        return;
    }
    nt_lcm_res->setText(res);
    nt_lcm1->clear(); nt_lcm1->setPlaceholderText(a);
    nt_lcm2->clear(); nt_lcm2->setPlaceholderText(b);
}

void MainWindow::StdErrShow(Err err_info){
    QString expr = std_input->text();
    QString err_msg;

    // 根据错误码获取错误描述
    switch(err_info.err_code){
    case DIV_BY_ZERO:      err_msg = "除零错误"; break;
    case FLOAT_MOD:        err_msg = "标准模式不支持取模运算(%)"; break;
    case INPUT_ERR:        err_msg = "输入格式错误"; break;
    case MULTIPLE_DOT:     err_msg = "数字包含多个小数点"; break;
    case REDUNDANT_LPAR:   err_msg = "括号不匹配：缺少右括号"; break;
    case REDUNDANT_RPAR:   err_msg = "括号不匹配：缺少左括号"; break;
    case UNKNOWN_CHAR:     err_msg = "包含非法字符"; break;
    case EXPR_ERR:         err_msg = "表达式无效"; break;
    case NEGA_POWER:       err_msg = "不支持负次幂"; break;
    case ZERO_POW_ZERO:    err_msg = "0的0次幂无意义"; break;
    case CALC_ERR:         err_msg = "计算错误"; break;
    default:               err_msg = "未知错误"; break;
    }

    std_output->setText(QString("错误：%1").arg(err_msg));
}
void MainWindow::HpErrShow(Err err_info){
    QString expr = hp_input->text();
    QString err_msg;

    // 根据错误码获取错误描述
    switch(err_info.err_code){
    case DIV_BY_ZERO:      err_msg = "除零错误"; break;
    case MOD_BY_ZERO:      err_msg = "模零错误"; break;
    case INPUT_ERR:        err_msg = "输入格式错误"; break;
    case REDUNDANT_LPAR:   err_msg = "括号不匹配：缺少右括号"; break;
    case REDUNDANT_RPAR:   err_msg = "括号不匹配：缺少左括号"; break;
    case UNKNOWN_CHAR:     err_msg = "包含非法字符"; break;
    case EXPR_ERR:         err_msg = "表达式无效"; break;
    case NEGA_POWER:       err_msg = "不支持负次幂"; break;
    case ZERO_POW_ZERO:    err_msg = "0的0次幂无意义"; break;
    case LARGE_NUM:        err_msg = "幂运算数据过大"; break;
    case CALC_ERR:         err_msg = "计算错误"; break;
    default:               err_msg = "未知错误"; break;
    }

    hp_output->setText(QString("错误：%1").arg(err_msg));
}

void MainWindow::NtSqrtErrShow(Err err_info){
    QString err_msg;
    switch(err_info.err_code){
    case NOT_POSI_INT: err_msg = "输入不是正整数"; break;
    case LARGE_NUM:    err_msg = "数据过大"; break;
    default:           err_msg = "未知错误"; break;
    }
    nt_sqrt_res->setText(QString("错误: %1").arg(err_msg));
}
void MainWindow::NtFactorErrShow(Err err_info){
    QString err_msg;
    switch(err_info.err_code){
    case NOT_POSI_INT: err_msg = "输入不是正整数"; break;
    case LARGE_NUM:    err_msg = "数据过大"; break;
    default:           err_msg = "未知错误"; break;
    }
    nt_factor_res->setText(QString("错误: %1").arg(err_msg));
}
void MainWindow::NtGcdErrShow(Err err_info){
    QString err_msg;
    switch(err_info.err_code){
    case NOT_POSI_INT: err_msg = "输入不是正整数"; break;
    case LARGE_NUM:    err_msg = "数据过大"; break;
    default:           err_msg = "未知错误"; break;
    }
    nt_gcd_res->setText(QString("错误: %1").arg(err_msg));
}
void MainWindow::NtLcmErrShow(Err err_info){
    QString err_msg;
    switch(err_info.err_code){
    case NOT_POSI_INT: err_msg = "输入不是正整数"; break;
    case LARGE_NUM:    err_msg = "数据过大"; break;
    default:           err_msg = "未知错误"; break;
    }
    nt_lcm_res->setText(QString("错误: %1").arg(err_msg));
}