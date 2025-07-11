#pragma once
#define QT_NO_KEYWORDS
#include <chrono>
#include <memory>
#include <variant>
#include <QCheckBox>
#include <QComboBox>
#include <QCoreApplication>
#include <QObject>
#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QtConcurrent>
#include <QTextEdit>
#include <QThread>

#include "goban_widget.h"
#include "learning_rate_box.h"

#include "interface.h"
#include "io.h"
#include "game.h"

using namespace std::chrono;
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
    QVBoxLayout* summaryLayout = nullptr;
    QComboBox* selectPlayer1 = nullptr;
    QComboBox* selectPlayer2 = nullptr;
    QPushButton* player1Button = nullptr;
    QPushButton* player2Button = nullptr;
    QSpinBox* player1TopKBox = nullptr;
    QSpinBox* player2TopKBox = nullptr;
    QSpinBox* player1MarginBox = nullptr;
    QSpinBox* player2MarginBox = nullptr;
    LearningRateBox* learningRateBox = nullptr;
    QCheckBox* saveBox = nullptr;
    QLabel* winRateText = nullptr;
    QComboBox* selectTime = nullptr;
    QComboBox* selectRefresh = nullptr;
    QPushButton* trainButton = nullptr;
    QPushButton* evaluateButton = nullptr;
    QTextEdit* logText = nullptr;
    QTextEdit* summaryText = nullptr;
    QEventLoop* loop = nullptr;
    QPushButton* undoButton = nullptr;
    QPushButton* passButton = nullptr;
    QTimer* scrollTimer = nullptr;
    QTimer* gobanTimer = nullptr;

    std::variant<std::shared_ptr<Engine<9>>, std::shared_ptr<Engine<13>>, std::shared_ptr<Engine<19>>> pendingEngine;
    bool pendingRefresh = false;
    QFuture<void> future;
    Interface* interface = nullptr;
    Game* game = nullptr;
    Move currentMove;
    bool bothPlayersAreHuman;

    void stop() {
        this->interface->stopGame(true);
        QThread::msleep(5);
        if (this->loop != nullptr && this->loop->isRunning()) {
            this->loop->quit();
            delete this->loop;
            this->loop = nullptr;
        }
        while (!this->game->canBeStopped()) {
            QCoreApplication::processEvents();
            QThread::msleep(10);
        }
        if (this->future.isRunning()) {
            this->future.cancel();
            this->future.waitForFinished();
        }
        this->refreshWinRate();
    }

    void closeEvent(QCloseEvent *event) override {
        this->stop();
        QThread::msleep(5);
        event->accept();
    }

    void loadAiParameters();

    void refreshWinRate();

    void refreshButtons();

    void refreshPlayer1List();

    void refreshPlayer2List();

    void displayTabLayouts();

    void displayGoban();

    void displayUndoButton();

    void displayPassButton();

    void displayStopButton();
 
    void displayLogText();

    void displayGobanButton();

    void displayPlayerSelection();

    void displayPlayerSummay();

    void displayTopK();

    void displayMargin();

    void displayLearningRate();

    void displaySaveButton();

    void displayMoveTime();

    void displayRefreshRate();

    void displayPlayButton();

    void displayTrainButton();

    void displayEvaluateButton();

    void displayCloseButton();

    void displaySummaryText();

    void displayReturnButton();

  public:

    Window(Interface* interface, Game* game, QWidget* parent = nullptr)
        : QMainWindow(parent),
          interface(interface),
          game(game) {
        this->displayTabLayouts();
        this->displayGobanButton();
        this->displayPlayerSelection();
        this->displayPlayerSummay();
        this->displayTopK();
        this->displayMargin();
        this->displayLearningRate();
        this->displaySaveButton();
        this->displayMoveTime();
        this->displayRefreshRate();
        this->displayPlayButton();
        this->displayTrainButton();
        this->displayEvaluateButton();
        this->displayGoban();
        this->displayUndoButton();
        this->displayPassButton();
        this->displayStopButton();
        this->displayLogText();
        this->refreshButtons();
        this->displaySummaryText();
        this->displayReturnButton();
        this->displayCloseButton();
    }

    virtual ~Window() = default;

    template<int8_t Size>
    void refreshGoban(std::shared_ptr<Engine<Size>> engine) {
        if (this->selectTime->currentData().toInt() > 0) {
            QThread::msleep(this->selectTime->currentData().toInt());
        }
        this->pendingEngine = engine;
        this->pendingRefresh = true;
    }

    void addLog(const std::string& message) {
        Q_EMIT addLogSignal(message);
    }

    void clearLog() {
        Q_EMIT clearLogSignal();
    }

    Move waitClickOnGoban() {
        this->loop = new QEventLoop();
        QObject::connect(gobanWidget, &GobanWidget::clicked, this,
            [&](Move m) {
                this->currentMove = m;
                this->loop->quit();
            });
        this->loop->exec();
        QThread::msleep(5);
        this->currentMove.stone.color = interface->colorTurn();
        return this->currentMove;
    }

  /*signals:*/
    Q_SIGNAL void refreshGoban9Signal(std::shared_ptr<Engine<9>> goban);
    Q_SIGNAL void refreshGoban13Signal(std::shared_ptr<Engine<13>> goban);
    Q_SIGNAL void refreshGoban19Signal(std::shared_ptr<Engine<19>> goban);

    Q_SIGNAL void addLogSignal(const std::string& message);
    Q_SIGNAL void clearLogSignal();
};

