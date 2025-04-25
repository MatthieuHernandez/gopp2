#include "window.h"

#include <memory>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QScrollBar>
#include <QTabWidget>

#include "ai.h"

void Window::loadAiParameters() {
    const auto ai1 = dynamic_cast<Ai*>(this->game->blackPlayer.get());
    if (ai1 != nullptr) {
        ai1->topK = static_cast<int16_t>(this->player1TopKBox->value());
        ai1->margin = static_cast<int16_t>(this->player1MarginBox->value());
        ai1->learningRate = static_cast<float>(this->learningRateBox->value());
    }
    const auto ai2 = dynamic_cast<Ai*>(this->game->whitePlayer.get());
    if (ai2 != nullptr) {
        ai2->topK = static_cast<int16_t>(this->player2TopKBox->value());
        ai2->margin = static_cast<int16_t>(this->player2MarginBox->value());
    }
    this->game->saveOnlyIfBetter = this->saveBox->checkState() == Qt::Checked ? true : false;
}

void Window::refreshWinRate() {
    if(this->winRateText != nullptr) {
        const auto ai1 = dynamic_cast<Ai*>(this->game->blackPlayer.get());
        if (ai1 != nullptr) {
            auto winrate = QString::number(ai1->calculateWinRate() * 100.0, 'g', 4) + "%";
            this->winRateText->setText(winrate);
        }
        else {
            this->winRateText->setText("--,--%");
        }
    }
}

void Window::refreshButtons() {
    if (this->trainButton != nullptr && this->evaluateButton != nullptr) {
        if (this->selectPlayer1->currentIndex() == 0 || this->selectPlayer2->currentIndex() == 0 ) {
            this->trainButton->setEnabled(false);
            this->evaluateButton->setEnabled(false);
            this->selectTime->setCurrentIndex(1);
            this->selectTime->setEnabled(false);
        } else if (this->selectPlayer1->currentIndex() < 3) {
            this->trainButton->setEnabled(false);
            this->evaluateButton->setEnabled(true);
            this->selectTime->setEnabled(true); 
        } else {
            this->trainButton->setEnabled(true);
            this->evaluateButton->setEnabled(true);
            this->selectTime->setEnabled(true);
        }
        if (this->selectPlayer1->currentIndex() < 3) {
            this->player1Button->setEnabled(false);
            this->player1TopKBox->setEnabled(false);
            this->player1MarginBox->setEnabled(false);
            this->learningRateBox->setEnabled(false);
        } else {
            this->player1Button->setEnabled(true);
            this->player1TopKBox->setEnabled(true);
            this->player1MarginBox->setEnabled(true);
            this->learningRateBox->setEnabled(true);
        }
        if (this->selectPlayer2->currentIndex() < 4) {
            this->player2Button->setEnabled(false);
            this->player2TopKBox->setEnabled(false);
            this->player2MarginBox->setEnabled(false);
        } else {
            this->player2Button->setEnabled(true);
            this->player2TopKBox->setEnabled(true);
            this->player2MarginBox->setEnabled(true);
        }
    }
    this->refreshWinRate();
}

void Window::refreshPlayer1List() {
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
    if (this->selectPlayer1->count() > 2) {
        auto player2Index = this->selectPlayer2->currentIndex();
        this->selectPlayer2->clear();
        this->selectPlayer2->insertItem(0, "Human", "0");
        this->selectPlayer2->insertItem(1, "Dumb", "1");
        this->selectPlayer2->insertItem(2, "Random", "2");
        this->selectPlayer2->insertItem(3, "Itself", "-1");
        auto* listView = qobject_cast<QListView*>(this->selectPlayer2->view());
        if (this->selectPlayer1->currentIndex() < 3) {
            listView->setRowHidden(3, true);
        } else {
            listView->setRowHidden(3, false);
        }
        player2Index = player2Index == 3 ? 2 : player2Index;
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

    auto* menuTab = new QWidget(this);
    this->menuLayout = new QVBoxLayout(menuTab);
    this->menuLayout->setContentsMargins(6, 8, 6, 8);
    this->menuLayout->setSpacing(8);
    this->menuLayout->setAlignment(Qt::AlignTop);
    menuTab->setLayout(this->menuLayout);
    this->tabWidget->addTab(menuTab, "Menu");

    auto *mainTab = new QWidget(this);
    this->mainLayout = new QVBoxLayout(mainTab);
    this->mainLayout->setContentsMargins(6, 0, 6, 0);
    this->mainLayout->setSpacing(8);
    this->mainLayout->setAlignment(Qt::AlignTop);
    mainTab->setLayout(mainLayout);
    this->tabWidget->addTab(mainTab, "Game");
     
    auto *summaryTab = new QWidget(this);
    this->summaryLayout = new QVBoxLayout(summaryTab);
    this->summaryLayout->setContentsMargins(6, 8, 6, 8);
    this->summaryLayout->setSpacing(8);
    this->summaryLayout->setAlignment(Qt::AlignTop);
    summaryTab->setLayout(summaryLayout);
    this->tabWidget->addTab(summaryTab, "Summary");
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
    auto* lineLayout = new QHBoxLayout();
    this->mainLayout->addLayout(lineLayout);
    auto* passButton = new QPushButton("Pass", this);
    lineLayout->addWidget(passButton, 1);
    this->connect(passButton, &QPushButton::clicked, this, [=]() {
        if (this->loop != nullptr) {
            this->loop->quit();
        }
    });
}

void Window::displayStopButton() {
    auto* lineLayout = new QHBoxLayout();
    this->mainLayout->addLayout(lineLayout);
    auto* stopButton = new QPushButton("Stop", this);
    lineLayout->addWidget(stopButton, 1);
    this->connect(stopButton, &QPushButton::clicked, this, [=]() {
        this->stop();
        this->tabWidget->setCurrentIndex(0);
        this->logText->clear();
    });
}

void Window::displayLogText() {
    auto* lineLayout = new QHBoxLayout();
    this->mainLayout->addLayout(lineLayout);
    this->logText = new QTextEdit(this);
    this->logText->setReadOnly(true);
    lineLayout->addWidget(this->logText, 1);
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
    auto* lineLayout = new QHBoxLayout();
    this->menuLayout->addLayout(lineLayout);
    QLabel* selectGobanText = new QLabel("Goban size:", this);
    QComboBox* selectGoban = new QComboBox(this);
    selectGoban->insertItem(0, "9x9", 9);
    selectGoban->insertItem(1, "13x13", 13);
    selectGoban->insertItem(2, "19x19", 19);
    lineLayout->addWidget(selectGobanText);
    lineLayout->addWidget(selectGoban);
    lineLayout->addItem(new QSpacerItem(100, 0));
    this->connect(selectGoban, &QComboBox::currentIndexChanged, [=](int index) {
        const auto selection = selectGoban->itemData(index).toInt();
        this->game->setGobanSize(selection);
        this->refreshPlayer2List();
        this->refreshPlayer1List();
    });
}

void Window::displayPlayerSelection() {
    auto* lineLayout = new QHBoxLayout();
    this->menuLayout->addLayout(lineLayout);
    QLabel* selectPlayersText = new QLabel("Players:", this);
    this->selectPlayer1 = new QComboBox(this);
    QLabel* vsText = new QLabel("vs", this);
    vsText->adjustSize();
    vsText->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    vsText->setMaximumWidth(vsText->sizeHint().width());
    this->selectPlayer2 = new QComboBox(this);
    lineLayout->addWidget(selectPlayersText);
    lineLayout->addWidget(this->selectPlayer1);
    lineLayout->addWidget(vsText);
    lineLayout->addWidget(selectPlayer2);
    this->refreshPlayer1List();
    this->connect(this->selectPlayer1, &QComboBox::currentIndexChanged, [=](int index) {
        const auto selection = this->selectPlayer1->itemData(index).toString().toStdString();
        this->game->selectPlayer(ColorBlack, selection);
        this->refreshPlayer2List();
    });
    this->connect(this->selectPlayer2, &QComboBox::currentIndexChanged, [=](int index) {
        const auto selection = this->selectPlayer2->itemData(index).toString().toStdString();
        this->game->selectPlayer(ColorWhite, selection);
        this->refreshButtons();
    });
    this->selectPlayer1->setCurrentIndex(0);
    this->selectPlayer2->setCurrentIndex(0);
}

void Window::displayPlayerSummay() {
    auto* lineLayout = new QHBoxLayout();
    this->menuLayout->addLayout(lineLayout);
    QLabel* selectPlayersText = new QLabel("Summary:", this);
    this->player1Button = new QPushButton("Player 1", this);
    this->player2Button = new QPushButton("Player 2", this);
    this->player1Button->setEnabled(false);
    this->player1Button->setEnabled(false);
    lineLayout->addWidget(selectPlayersText);
    lineLayout->addWidget(this->player1Button);
    lineLayout->addItem(new QSpacerItem(40, 0));
    lineLayout->addWidget(this->player2Button);
    this->connect(this->player1Button, &QPushButton::clicked, this, [=]() {
        const auto ai1 = dynamic_cast<Ai*>(this->game->blackPlayer.get());
        this->summaryText->append(QString::fromStdString(ai1->summary()));
        this->summaryText->moveCursor(QTextCursor::Start);
        QTimer::singleShot(50, this, [=]() {
            this->tabWidget->setCurrentIndex(2);
        });
    });
    this->connect(this->player2Button, &QPushButton::clicked, this, [=]() {
        const auto ai2 = dynamic_cast<Ai*>(this->game->whitePlayer.get());
        this->summaryText->append(QString::fromStdString(ai2->summary()));
        this->summaryText->moveCursor(QTextCursor::Start);
        QTimer::singleShot(50, this, [=]() {
            this->tabWidget->setCurrentIndex(2);
        });
    });
}

void Window::displayTopK() {
    auto* lineLayout = new QHBoxLayout();
    this->menuLayout->addLayout(lineLayout);
    auto* topKText = new QLabel("Top-k:", this);
    this->player1TopKBox = new QSpinBox(this);
    this->player2TopKBox = new QSpinBox(this);
    this->player1TopKBox->setEnabled(false);
    this->player2TopKBox->setEnabled(false);
    this->player1TopKBox->setRange(1, 360);
    this->player2TopKBox->setRange(1, 360);
    lineLayout->addWidget(topKText);
    lineLayout->addWidget(this->player1TopKBox);
    lineLayout->addItem(new QSpacerItem(40, 0));
    lineLayout->addWidget(this->player2TopKBox);
}

void Window::displayMargin() {
    auto* lineLayout = new QHBoxLayout();
    this->menuLayout->addLayout(lineLayout);
    auto* marginText = new QLabel("Margin:", this);
    this->player1MarginBox = new QSpinBox(this);
    this->player2MarginBox = new QSpinBox(this);
    this->player1MarginBox->setSuffix("%");
    this->player2MarginBox->setSuffix("%");
    this->player1MarginBox->setEnabled(false);
    this->player2MarginBox->setEnabled(false);
    this->player1MarginBox->setRange(0, 100);
    this->player2MarginBox->setRange(0, 100);
    lineLayout->addWidget(marginText);
    lineLayout->addWidget(this->player1MarginBox);
    lineLayout->addItem(new QSpacerItem(40, 0));
    lineLayout->addWidget(this->player2MarginBox);
}

void Window::displayLearningRate() {
    auto* lineLayout = new QHBoxLayout();
    this->menuLayout->addLayout(lineLayout);
    auto* learningRateText = new QLabel("Learning rate:", this);
    this->learningRateBox= new LearningRateBox(this);
    lineLayout->addWidget(learningRateText);
    lineLayout->addWidget(this->learningRateBox);
    lineLayout->addItem(new QSpacerItem(130, 0));
}

void Window::displaySaveButton() {
    auto* lineLayout = new QHBoxLayout();
    this->menuLayout->addLayout(lineLayout);
    auto* saveText = new QLabel("Save model:", this);
    this->saveBox = new QCheckBox("Only if better", this);
    auto* bestText = new QLabel("Best:", this);
    this->winRateText = new QLabel("--,--%", this);
    auto* resetButton = new QPushButton("Reset", this);
    resetButton->setFixedWidth(48);
    lineLayout->addWidget(saveText);
    lineLayout->addWidget(this->saveBox);
    lineLayout->addItem(new QSpacerItem(10, 0));
    lineLayout->addWidget(bestText);
    lineLayout->addWidget(winRateText);
    lineLayout->addWidget(resetButton);
    this->connect(resetButton, &QPushButton::clicked, this, [=]() {
        const auto ai1 = dynamic_cast<Ai*>(this->game->blackPlayer.get());
        if (ai1 != nullptr) {
            ai1->resetWinRate();
        }
        this->refreshWinRate();
    });
}

void Window::displayMoveTime() {
    auto* lineLayout = new QHBoxLayout();
    this->menuLayout->addLayout(lineLayout);
    QLabel* selectTimeText = new QLabel("Move time:", this);
    this->selectTime = new QComboBox(this);
    this->selectTime->insertItem(0, "0 ms", 0);
    this->selectTime->insertItem(1, "100 ms", 100);
    this->selectTime->insertItem(2, "300 ms", 300);
    this->selectTime->insertItem(3, "500 ms", 500);
    this->selectTime->insertItem(4, "1000 ms", 1000);
    lineLayout->addWidget(selectTimeText);
    lineLayout->addWidget(selectTime);
    lineLayout->addItem(new QSpacerItem(100, 0));
}

void Window::displayPlayButton() {
    auto* lineLayout = new QHBoxLayout();
    this->menuLayout->addLayout(lineLayout);
    auto* playOneButton = new QPushButton("Play one game", this);
    lineLayout->addWidget(playOneButton);
    this->connect(playOneButton, &QPushButton::clicked, this, [=]() {
        if (!this->future.isRunning()) {
            this->future = QtConcurrent::run([this]() {
                this->loadAiParameters();
                this->game->playOne();
            });
        }
        QTimer::singleShot(50, this, [=]() {
            this->tabWidget->setCurrentIndex(1);
        });
    });
}

void Window::displayTrainButton() {
    auto* lineLayout = new QHBoxLayout();
    this->menuLayout->addLayout(lineLayout);
    this->trainButton = new QPushButton("Train black player", this);
    lineLayout->addWidget(this->trainButton);
    this->connect(this->trainButton, &QPushButton::clicked, this, [=]() {
        if (!this->future.isRunning()) {
            this->future = QtConcurrent::run([this]() {
                this->loadAiParameters();
                this->game->trainBlack();
            });
        }
        QTimer::singleShot(50, this, [=]() {
            this->tabWidget->setCurrentIndex(1);
        });
    });
}

void Window::displayEvaluateButton() {
    auto* lineLayout = new QHBoxLayout();
    this->menuLayout->addLayout(lineLayout);
    this->evaluateButton = new QPushButton("Evaluate players against each other", this);
    lineLayout->addWidget(this->evaluateButton);
    this->connect(this->evaluateButton, &QPushButton::clicked, this, [=]() {
        if (!this->future.isRunning()) {
            this->future = QtConcurrent::run([this]() {
                this->loadAiParameters();
                this->game->evaluate();
            });
        }
        QTimer::singleShot(50, this, [=]() {
            this->tabWidget->setCurrentIndex(1);
        });
    });
}

void Window::displayCloseButton() {
    auto* lineLayout = new QHBoxLayout();
    this->menuLayout->addStretch();
    this->menuLayout->addLayout(lineLayout);
    auto* closeButton = new QPushButton("Close", this);
    lineLayout->addStretch();
    lineLayout->addWidget(closeButton);
    this->connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
}

void Window::displaySummaryText() {
    auto* lineLayout = new QHBoxLayout();
    this->summaryLayout->addLayout(lineLayout);
    this->summaryText = new QTextEdit(this);
    this->summaryText->setReadOnly(true);
    lineLayout->addWidget(this->summaryText, 1);
    this->summaryText->setLineWrapMode(QTextEdit::NoWrap);
    this->summaryText->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    QFont font("Courier New", 8);
    this->summaryText->setFont(font);
}

void Window::displayReturnButton() {
    auto* lineLayout = new QHBoxLayout();
    this->summaryLayout->addLayout(lineLayout);
    auto* returnButton = new QPushButton("Return", this);
    lineLayout->addWidget(returnButton, 1);
    this->connect(returnButton, &QPushButton::clicked, this, [=]() {
        this->tabWidget->setCurrentIndex(0);
        this->summaryText->clear();
    });
}
