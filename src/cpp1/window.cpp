#include "window.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QScrollBar>
#include <QTabWidget>

void Window::refreshPlayer1List() {
    qDebug() << "refresh 1";
    const auto player1Index = this->selectPlayer1->currentIndex();
    this->selectPlayer1->clear();
    this->selectPlayer1->insertItem(0, "Human", "0");
    this->selectPlayer1->insertItem(1, "Dumb", "1");
    this->selectPlayer1->insertItem(2, "Random", "2");
    auto models = io::getSnnModels(this->game->getGobanSize());
    int i = 3;
    for (const auto& model : models) {
        QString name = QString::fromStdString(model[0]);
        QString path = QString::fromStdString(model[1]);
        this->selectPlayer1->insertItem(i, name, path);
        i++;
    }
    if (player1Index < this->selectPlayer1->count()) {
        this->selectPlayer1->setCurrentIndex(player1Index);
    }
}

void Window::refreshPlayer2List() {
    if (this->selectPlayer1->count() > 0) {
        qDebug() << "refresh 2";
        const auto player2Index = this->selectPlayer2->currentIndex();
        this->selectPlayer2->clear();
        if (this->selectPlayer1->currentIndex() > 2) {
            this->selectPlayer2->insertItem(0, "Itself", "-1");
        }
        this->selectPlayer2->insertItem(1, "Human", "0");
        this->selectPlayer2->insertItem(2, "Dumb", "1");
        this->selectPlayer2->insertItem(3, "Random", "2");

        auto models = io::getSnnModels(this->game->getGobanSize());
        int i = 3;
        for (const auto& model : models) {
            QString name = QString::fromStdString(model[0]);
            QString path = QString::fromStdString(model[1]);
            this->selectPlayer2->insertItem(i+1, name, path);
            i++;
        }
        if (player2Index < this->selectPlayer2->count()) {
            this->selectPlayer2->setCurrentIndex(player2Index);
        }
    }
}

void Window::displayTabLayouts() {
    this->tabWidget = new QTabWidget;
    this->setCentralWidget(tabWidget);

    this->setFixedSize(RaspberryScreenWidth, RaspberryScreenHeight);
    this->centralWidget()->setFixedSize(this->size());

    QWidget* menuTab = new QWidget(this);
    this->menuLayout = new QVBoxLayout(menuTab);
    this->menuLayout->setContentsMargins(6, 8, 6, 8);
    this->menuLayout->setSpacing(8);
    this->menuLayout->setAlignment(Qt::AlignTop);
    menuTab->setLayout(this->menuLayout);
    this->tabWidget->addTab(menuTab, "Menu");

    QWidget *mainTab = new QWidget(this);
    this->mainLayout = new QVBoxLayout(mainTab);
    this->mainLayout->setContentsMargins(6, 0, 6, 0);
    this->mainLayout->setSpacing(8);
    this->mainLayout->setAlignment(Qt::AlignTop);
    mainTab->setLayout(mainLayout);
    this->tabWidget->addTab(mainTab, "Game");
    this->tabWidget->tabBar()->hide();
}

void Window::displayGoban() {
    this->gobanWidget = new GobanWidget(this);
    this->mainLayout->insertWidget(0, this->gobanWidget);
    this->connect(this, &Window::refreshGoban9Signal, this->gobanWidget, &GobanWidget::refresh<9>);
    this->connect(this, &Window::refreshGoban13Signal, this->gobanWidget, &GobanWidget::refresh<13>);
    this->connect(this, &Window::refreshGoban19Signal, this->gobanWidget, &GobanWidget::refresh<19>);
}

void Window::displayPassButton() {
    auto* line2Layout = new QHBoxLayout();
    this->mainLayout->addLayout(line2Layout);
    auto* passButton = new QPushButton("Pass", this);
    line2Layout->addWidget(passButton, 1);
    this->connect(passButton, &QPushButton::clicked, this, [=]() {
        if (this->loop != nullptr) {
            this->loop->quit();
        }
    });
}

void Window::displayStopButton() {
    auto* line2Layout = new QHBoxLayout();
    this->mainLayout->addLayout(line2Layout);
    auto* stopButton = new QPushButton("Stop", this);
    line2Layout->addWidget(stopButton, 1);
    this->connect(stopButton, &QPushButton::clicked, this, [=]() {
        this->stop();
        this->tabWidget->setCurrentIndex(0);
        this->logText->clear();
    });
}

void Window::displayLogText() {
    auto* line3Layout = new QHBoxLayout();
    this->mainLayout->addLayout(line3Layout);
    this->logText = new QTextEdit(this);
    this->logText->setReadOnly(true);
    line3Layout->addWidget(this->logText, 1);
    this->logText->verticalScrollBar();
    this->connect(this, &Window::addLogSignal, this, [=](const std::string& message) {
        this->logText->append(QString::fromStdString(message));
        QTimer::singleShot(5, this, [=]() {
            QScrollBar* bar = this->logText->verticalScrollBar();
            bar->setValue(bar->maximum());
        });
    });
    this->connect(this, &Window::clearLogSignal, this, [=]() {
        this->logText->clear();
    });
}

void Window::displayGobanButton() {
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
        this->refreshPlayer1List();
    });
}

void Window::displayPlayerSelection() {
    auto* line2Layout = new QHBoxLayout();
    this->menuLayout->addLayout(line2Layout);
    QLabel* selectPlayersText = new QLabel("Players:", this);
    this->selectPlayer1 = new QComboBox(this);
    QLabel* vsText = new QLabel("vs", this);
    vsText->adjustSize();
    vsText->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    vsText->setMaximumWidth(vsText->sizeHint().width());
    this->selectPlayer2 = new QComboBox(this);
    line2Layout->addWidget(selectPlayersText);
    line2Layout->addWidget(this->selectPlayer1);
    line2Layout->addWidget(vsText);
    line2Layout->addWidget(selectPlayer2);
    this->refreshPlayer1List();
    this->connect(this->selectPlayer1, &QComboBox::currentIndexChanged, [=](int index) {
        const auto selection = this->selectPlayer1->itemData(index).toString().toStdString();
        this->game->selectPlayer(ColorBlack, selection);
        this->refreshPlayer2List();
        if(this->trainButton != nullptr) {
            if(selection == "0") {
                this->trainButton->setEnabled(false);
            } else {
                this->trainButton->setEnabled(true);
            }
        }
    });
    this->connect(this->selectPlayer2, &QComboBox::currentIndexChanged, [=](int index) {
        const auto selection = this->selectPlayer2->itemData(index).toString().toStdString();
        this->game->selectPlayer(ColorWhite, selection);
        if(this->trainButton != nullptr) {
            if(selection == "0") {
                this->trainButton->setEnabled(false);
            } else {
                this->trainButton->setEnabled(true);
            }
        }
    });
    this->selectPlayer1->setCurrentIndex(0);
    this->selectPlayer2->setCurrentIndex(0);
}

void Window::displayPlayButton() {
    auto* line3Layout = new QHBoxLayout();
    this->menuLayout->addLayout(line3Layout);
    auto* playOneButton = new QPushButton("Play one game", this);
    line3Layout->addWidget(playOneButton);
    this->connect(playOneButton, &QPushButton::clicked, this, [=]() {
        if (!this->future.isRunning()) {
            this->future = QtConcurrent::run([this]() {
                this->game->playOne();
            });
        }
        QTimer::singleShot(50, this, [=]() {
            this->tabWidget->setCurrentIndex(1);
        });
    });
}

void Window::displayTrainButton() {
    auto* line4Layout = new QHBoxLayout();
    this->menuLayout->addLayout(line4Layout);
    this->trainButton = new QPushButton("Train black player", this);
    line4Layout->addWidget(this->trainButton);
    this->connect(this->trainButton, &QPushButton::clicked, this, [=]() {
        if (!this->future.isRunning()) {
            this->future = QtConcurrent::run([this]() {
                this->game->trainBlack();
            });
        }
        QTimer::singleShot(50, this, [=]() {
            this->tabWidget->setCurrentIndex(1);
        });
    });
}

void Window::displayEvaluateButton() {
    auto* line5Layout = new QHBoxLayout();
    this->menuLayout->addLayout(line5Layout);
    auto* evaluateButton = new QPushButton("Evaluate players against each other", this);
    line5Layout->addWidget(evaluateButton);
    this->connect(evaluateButton, &QPushButton::clicked, this, [=]() {
        if (!this->future.isRunning()) {
            this->future = QtConcurrent::run([this]() {
                this->game->evaluate();
            });
        }
        QTimer::singleShot(50, this, [=]() {
            this->tabWidget->setCurrentIndex(1);
        });
    });
}
