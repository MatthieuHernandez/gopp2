#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QPushButton>
#include <QTabWidget>

#include "goban_widget.h"
#include "../generate/io.h"

constexpr int gobanImageSize = 429;

constexpr int RaspberryScreenWidth = 320;
constexpr int RaspberryScreenHeight = 480;

class Window : public QMainWindow {
  private:
  QWidget* gobanWidget = nullptr;
  QTabWidget* tabWidget = nullptr;
  QVBoxLayout* menuLayout = nullptr;
  QVBoxLayout* mainLayout = nullptr;
  int8_t gobanSize = 9;


    void displayTabLayouts() {
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
        if(this->gobanWidget != nullptr) {
            delete this->gobanWidget;
        }
        if (this->gobanSize == 9) {
            this->gobanWidget = new GobanWidget<9>(this);
        } else if (this->gobanSize == 13) {
            this->gobanWidget = new GobanWidget<13>(this);
        } else {
            this->gobanWidget = new GobanWidget<19>(this);
        }
        this->mainLayout->insertWidget(0, this->gobanWidget);

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
            this->gobanSize = selectGoban->itemData(index).toInt();
            displayGoban();
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
        auto models = getSnnModels(this->gobanSize);

        selectPlayer2->insertItem(0, "Itself", "-1");
        selectPlayer1->insertItem(0, "Human", "0");
        selectPlayer2->insertItem(1, "Human", "0");
        selectPlayer1->insertItem(1, "Dumb", "1");
        selectPlayer2->insertItem(2, "Dumb", "1");
        selectPlayer1->insertItem(2, "Random", "2");
        selectPlayer2->insertItem(3, "Random", "2");
        int i = 3;
        for (auto& model : models) {
            QString name = QString::fromStdString(model[0]);
            QString path = QString::fromStdString(model[1]);
            selectPlayer1->insertItem(i, name, path);
            selectPlayer2->insertItem(i+1, name, path);
            i++;
        }
    }

    void displayMenuLine3() {
        auto* line3Layout = new QHBoxLayout();
        this->menuLayout->addLayout(line3Layout);
        auto* playOneButton = new QPushButton("Play one game", this);
        line3Layout->addWidget(playOneButton);
        this->connect(playOneButton, &QPushButton::clicked, this, [=]() {
            this->tabWidget->setCurrentIndex(1);
        });
    }

  public:
    Window(QWidget* parent = nullptr) : QMainWindow(parent) {
        this->displayTabLayouts();
        this->displayMenuLine1();
        this->displayMenuLine2();
        this->displayMenuLine3();
        this->displayGoban();
        this->displayMainLine2();
    }
};
