#pragma once
#include <chrono>
#include <memory>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QMainWindow>
#include <QPixmap>
#include <QPushButton>
#include <QtConcurrent>
#include <QTabWidget>
#include <QThread>

#include "goban_widget.h"

#include "../generate/interface.h"
#include "../generate/io.h"
#include "../generate/game.h"

using namespace std::literals::chrono_literals;

inline constexpr int gobanImageSize = 429;
inline constexpr int RaspberryScreenWidth = 320;
inline constexpr int RaspberryScreenHeight = 480;


class Window : public QMainWindow {
    Q_OBJECT
  private:
    GobanWidget* gobanWidget = nullptr;
    QTabWidget* tabWidget = nullptr;
    QVBoxLayout* menuLayout = nullptr;
    QVBoxLayout* mainLayout = nullptr;
    Game* game = nullptr;

    void Window::displayTabLayouts() {
        this->tabWidget = new QTabWidget;
        this->setCentralWidget(tabWidget);

        this->setFixedSize(RaspberryScreenWidth, RaspberryScreenHeight);
        this->centralWidget()->setFixedSize(this->size());

        QWidget* menuTab = new QWidget(this);
        this->menuLayout = new QVBoxLayout(menuTab);
        this->menuLayout->setContentsMargins(8, 8, 8, 8);
        this->menuLayout->setSpacing(8);
        this->menuLayout->setAlignment(Qt::AlignTop);
        menuTab->setLayout(this->menuLayout);
        this->tabWidget->addTab(menuTab, "Menu");

        QWidget *mainTab = new QWidget(this);
        this->mainLayout = new QVBoxLayout(mainTab);
        this->mainLayout->setContentsMargins(0, 0, 0, 0);
        this->mainLayout->setSpacing(0);
        this->mainLayout->setAlignment(Qt::AlignTop);
        mainTab->setLayout(mainLayout);
        this->tabWidget->addTab(mainTab, "Game");
        this->tabWidget->tabBar()->hide();
    }

    void displayGoban() {
        this->gobanWidget = new GobanWidget(this);
        this->mainLayout->insertWidget(0, this->gobanWidget);
        this->connect(this, &Window::refreshGoban9Signal, this->gobanWidget, &GobanWidget::refresh<9>);
        this->connect(this, &Window::refreshGoban13Signal, this->gobanWidget, &GobanWidget::refresh<13>);
        this->connect(this, &Window::refreshGoban19Signal, this->gobanWidget, &GobanWidget::refresh<19>);
    }

    void displayMainLine2() {
        auto* line2Layout = new QHBoxLayout();
        this->mainLayout->addLayout(line2Layout);
        auto* stopButton = new QPushButton("Stop", this);
        line2Layout->addWidget(stopButton, 1);
        this->connect(stopButton, &QPushButton::clicked, this, [=]() {
            this->tabWidget->setCurrentIndex(0);
        });
    }

    void displayMenuLine1() {
        auto* line1Layout = new QHBoxLayout();
        this->menuLayout->addLayout(line1Layout);
        QLabel* selectGobanText = new QLabel("Goban size:", this);
        QComboBox* selectGoban = new QComboBox(this);
        selectGoban->insertItem(0, "9x9", 9);
        selectGoban->insertItem(1, "13x13", 13);
        selectGoban->insertItem(2, "19x19", 19);
        line1Layout->addWidget(selectGobanText);
        line1Layout->addWidget(selectGoban);
        line1Layout->addItem(new QSpacerItem(100, 0));
        this->connect(selectGoban, &QComboBox::currentIndexChanged, [=](int index) {
            const auto selection = selectGoban->itemData(index).toInt();
            this->game->setGobanSize(selection);
        });
    }

    void displayMenuLine2() {
        auto* line2Layout = new QHBoxLayout();
        this->menuLayout->addLayout(line2Layout);
        QLabel* selectPlayersText = new QLabel("Players:", this);
        QComboBox* selectPlayer1 = new QComboBox(this);
        QLabel* vsText = new QLabel("vs", this);
        vsText->adjustSize();
        vsText->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        vsText->setMaximumWidth(vsText->sizeHint().width());
        QComboBox* selectPlayer2 = new QComboBox(this);
        line2Layout->addWidget(selectPlayersText);
        line2Layout->addWidget(selectPlayer1);
        line2Layout->addWidget(vsText);
        line2Layout->addWidget(selectPlayer2);
        auto models = io::getSnnModels(this->game->getGobanSize());

        selectPlayer2->insertItem(0, "Itself", "-1");
        selectPlayer1->insertItem(0, "Human", "0");
        selectPlayer2->insertItem(1, "Human", "0");
        selectPlayer1->insertItem(1, "Dumb", "1");
        selectPlayer2->insertItem(2, "Dumb", "1");
        selectPlayer1->insertItem(2, "Random", "2");
        selectPlayer2->insertItem(3, "Random", "2");
        int i = 3;
        for (const auto& model : models) {
            QString name = QString::fromStdString(model[0]);
            QString path = QString::fromStdString(model[1]);
            selectPlayer1->insertItem(i, name, path);
            selectPlayer2->insertItem(i+1, name, path);
            i++;
        }
        selectPlayer1->setCurrentIndex(1);
        this->connect(selectPlayer1, &QComboBox::currentIndexChanged, [=](int index) {
            const auto selection = selectPlayer1->itemData(index).toString().toStdString();
            this->game->selectPlayer(Color::Black, selection);
        });
        this->connect(selectPlayer2, &QComboBox::currentIndexChanged, [=](int index) {
            const auto selection = selectPlayer2->itemData(index).toString().toStdString();
            this->game->selectPlayer(Color::White, selection);
        });
        selectPlayer1->setCurrentIndex(0);
        selectPlayer2->setCurrentIndex(1);
    }

    void displayMenuLine3() {
        auto* line3Layout = new QHBoxLayout();
        this->menuLayout->addLayout(line3Layout);
        auto* playOneButton = new QPushButton("Play one game", this);
        line3Layout->addWidget(playOneButton);
        this->connect(playOneButton, &QPushButton::clicked, this, [=]() {
            qDebug() << "Info: Start a game.";
            QtConcurrent::run([this]() {
                this->game->playOne();
            });
            QTimer::singleShot(50, this, [=]() {
                this->tabWidget->setCurrentIndex(1);
            });
        });
    }

    void displayMenuLine4() {
        auto* line4Layout = new QHBoxLayout();
        this->menuLayout->addLayout(line4Layout);
        auto* trainButton = new QPushButton("Train black player", this);
        line4Layout->addWidget(trainButton);
        this->connect(trainButton, &QPushButton::clicked, this, [=]() {
            QTimer::singleShot(50, this, [=]() {
                this->tabWidget->setCurrentIndex(1);
            });
        });
    }

    void displayMenuLine5() {
        auto* line5Layout = new QHBoxLayout();
        this->menuLayout->addLayout(line5Layout);
        auto* evaluateButton = new QPushButton("Evaluate players against each other", this);
        line5Layout->addWidget(evaluateButton);
        this->connect(evaluateButton, &QPushButton::clicked, this, [=]() {
            QTimer::singleShot(50, this, [=]() {
                this->tabWidget->setCurrentIndex(1);
            });
        });
    }

  public:
    Window::Window(Interface* interface, Game* game, QWidget* parent = nullptr)
        : QMainWindow(parent),
          game(game) {
        this->displayTabLayouts();
        this->displayMenuLine1();
        this->displayMenuLine2();
        this->displayMenuLine3();
        this->displayMenuLine4();
        this->displayMenuLine5();
        this->displayMainLine2();
        this->displayGoban();
    }
    virtual ~Window() = default;

    template<int8_t Size>
    void refreshGoban(const Goban<Size>& goban) {
        QThread::msleep(10); // Prevents the GUI from being saturated with signals.
        if constexpr (Size == 9) {
            emit refreshGoban9Signal(&goban);
        } else if constexpr (Size == 13) {
            emit refreshGoban13Signal(&goban);
        } else if constexpr (Size == 19) {
            emit refreshGoban19Signal(&goban);
        }
    }

  signals:
    void refreshGoban9Signal(const Goban<9>* goban);
    void refreshGoban13Signal(const Goban<13>* goban);
    void refreshGoban19Signal(const Goban<19>* goban);

};
