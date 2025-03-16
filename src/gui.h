#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QPushButton>
#include <QTabWidget>

#include "goban_widget.h"

constexpr int gobanImageSize = 429;

constexpr int RaspberryScreenWidth = 320;
constexpr int RaspberryScreenHeight = 480;

class Window : public QMainWindow {
  private:
    std::tuple<QHBoxLayout*, QVBoxLayout*> getTabLayouts() {
        auto* tabWidget = new QTabWidget;
        this->setCentralWidget(tabWidget);

        this->setFixedSize(RaspberryScreenWidth, RaspberryScreenHeight);
        this->centralWidget()->setFixedSize(this->size());

        QWidget *mainTab = new QWidget(this);
        auto* mainLayout = new QHBoxLayout(mainTab);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);
        mainLayout->setAlignment(Qt::AlignTop);
        mainTab->setLayout(mainLayout);
        tabWidget->addTab(mainTab, "Main");

        QWidget *menuTab = new QWidget(this);
        auto* menuLayout = new QVBoxLayout(menuTab);
        menuLayout->setContentsMargins(8, 8, 8, 8);
        menuLayout->setSpacing(8);
        menuLayout->setAlignment(Qt::AlignTop);
        menuTab->setLayout(menuLayout);
        tabWidget->addTab(menuTab, "Menu");

        return {mainLayout, menuLayout};
    }

    void displayGoban(QHBoxLayout* layout) {
        auto* gobanWidget = new GobanWidget<9>(this);
        layout->addWidget(gobanWidget, Qt::AlignTop, Qt::AlignLeft);
    }

    void displayMenuLine1(QVBoxLayout* menuLayout) {
        auto* line1Layout = new QHBoxLayout();
        menuLayout->addLayout(line1Layout);
        QLabel* selectGobanText = new QLabel("Select Goban: ", this);
        QComboBox* selectGoban = new QComboBox(this);
        selectGoban->insertItem(0, "9x9", 9);
        selectGoban->insertItem(1, "13x13", 13);
        selectGoban->insertItem(2, "19x19", 19);
        line1Layout->addWidget(selectGobanText);
        line1Layout->addItem(new QSpacerItem(50, 0));
        line1Layout->addWidget(selectGoban);
    }

    void displayMenuLine2(QVBoxLayout* menuLayout) {
        auto* line2Layout = new QHBoxLayout();
        menuLayout->addLayout(line2Layout);
        QLabel* selectPlayersText = new QLabel("Select Players:", this);
        QComboBox* selectPlayer1 = new QComboBox(this);
        QLabel* vsText = new QLabel(" vs ", this);
        vsText->adjustSize();
        vsText->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        vsText->setMaximumWidth(vsText->sizeHint().width());
        QComboBox* selectPlayer2 = new QComboBox(this);
        line2Layout->addWidget(selectPlayersText);
        line2Layout->addItem(new QSpacerItem(50, 0));
        line2Layout->addWidget(selectPlayer1);
        line2Layout->addWidget(vsText);
        line2Layout->addWidget(selectPlayer2);
    }

    /*void displayMenuLine3(QVBoxLayout* menuLayout) {
        auto* line2Layout = new QHBoxLayout(this);
        menuLayout->addLayout(line2Layout);
        QLabel* select_players_text = new QLabel("Select Players:", this);
        line2Layout->addWidget(select_players_text);
    }*/

  public:
    Window(QWidget* parent = nullptr) : QMainWindow(parent) {
        QHBoxLayout* mainLayout = nullptr;
        QVBoxLayout* menuLayout = nullptr;
        std::tie(mainLayout, menuLayout) = getTabLayouts();
        displayMenuLine1(menuLayout);
        displayMenuLine2(menuLayout);
        displayGoban(mainLayout);
        //displayMenuLine3(menuLayout);
    }
};
