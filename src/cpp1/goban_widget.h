#pragma once
#include <QLabel>
#include <QObject>
#include <QPixmap>
#include <QGridLayout>
#include <QMouseEvent>

#include "engine.h"
#include "color.h"

class GobanWidget : public QWidget {
    Q_OBJECT
  private:
    QPixmap* middle = nullptr;
    QPixmap* hoshi = nullptr;
    QPixmap* left = nullptr;
    QPixmap* right = nullptr;
    QPixmap* top = nullptr;
    QPixmap* bottom = nullptr;
    QPixmap* conerTopLeft = nullptr;
    QPixmap* conerBottomLeft = nullptr;
    QPixmap* conerTopRight = nullptr;
    QPixmap* conerBottomRight = nullptr;
    QPixmap* blackStone = nullptr;
    QPixmap* whiteStone = nullptr;

    QGridLayout* gridLayout = nullptr;

    std::map<QLabel*, Move> moveMap;

    void resetLayout() {
        if (this->gridLayout == nullptr) {
            return;
        }
        while (this->gridLayout->count() > 0) {
            auto* item = this->gridLayout->takeAt(0);
            if (item != nullptr && item->widget() != nullptr) {
                item->widget()->deleteLater();
                delete item;
            }
        }
    }

  public:
    GobanWidget(QWidget *parent = nullptr)
        : QWidget(parent) {
        this->middle = new QPixmap("C:/Programming/Git/gopp2/build/Release/bin/images/middle.png");
        this->hoshi = new QPixmap("C:/Programming/Git/gopp2/build/Release/bin/images/hoshi.png");
        this->left = new QPixmap("C:/Programming/Git/gopp2/build/Release/bin/images/left.png");
        this->right = new QPixmap("C:/Programming/Git/gopp2/build/Release/bin/images/right.png");
        this->top = new QPixmap("C:/Programming/Git/gopp2/build/Release/bin/images/top.png");
        this->bottom = new QPixmap("C:/Programming/Git/gopp2/build/Release/bin/images/bottom.png");
        this->conerTopLeft = new QPixmap("C:/Programming/Git/gopp2/build/Release/bin/images/coner_top_left.png");
        this->conerBottomLeft = new QPixmap("C:/Programming/Git/gopp2/build/Release/bin/images/coner_bottom_left.png");
        this->conerTopRight = new QPixmap("C:/Programming/Git/gopp2/build/Release/bin/images/coner_top_right.png");
        this->conerBottomRight = new QPixmap("C:/Programming/Git/gopp2/build/Release/bin/images/coner_bottom_right.png");
        this->blackStone = new QPixmap("C:/Programming/Git/gopp2/build/Release/bin/images/black_stone.png");
        this->whiteStone = new QPixmap("C:/Programming/Git/gopp2/build/Release/bin/images/white_stone.png");

        this->gridLayout = new QGridLayout(this);
        this->gridLayout->setContentsMargins(0, 0, 0, 0);
        this->gridLayout->setSpacing(0);
        this->gridLayout->setAlignment(Qt::AlignTop);

        this->setLayout(this->gridLayout);
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }

    template<int8_t Size>
    void refresh(std::shared_ptr<Engine<Size>> engine) {
        const auto& goban = engine->goban;
        int numberOfLib = 0;
        for (int8_t col = 0; col < Size; ++col) {
            for (int8_t row = 0; row < Size; ++row) {
                if (goban.state[col][row].color != ColorBlack && 
                    goban.state[col][row].color != ColorWhite){
                    numberOfLib++;
                }
            }
        }
        this->resetLayout();
        constexpr int8_t maxIndex = Size - 1;
        QPixmap* img = nullptr;
        int8_t row;
        for (int8_t col = 0; col < Size; col++) {
            for (int8_t x = 0; x < Size; x++) {
                row = maxIndex - (x % Size);
                if (goban.state[col][x].color == ColorBlack) {
                    img = this->blackStone;
                } else if (goban.state[col][x].color == ColorWhite){
                    img = this->whiteStone;
                } else {
                    if ((Size == 9 &&
                        ((row == 2 && (col == 2 || col == 6)) ||
                        (row ==  6 && (col == 2 || col == 6)))) ||
                        (Size == 13 &&
                        ((row == 9 && (col == 3 || col == 6 || col == 9)) ||
                        (row == 6 && (col == 3 || col == 6 || col == 9)) ||
                        (row ==  3 && (col == 3 || col == 6 || col == 9)))) ||
                        (Size == 19 &&
                        ((row == 15 && (col == 3 || col == 9 || col == 15)) ||
                        (row == 9 && (col == 3 || col == 9 || col == 15)) ||
                        (row ==  3 && (col == 3 || col == 9 || col == 15)))) ) {
                            img = hoshi;
                    } else {
                        if (row == maxIndex) {
                            if (col == 0) {
                                img = this->conerBottomLeft;
                            } 
                            else if (col == maxIndex) {
                                img = this->conerBottomRight;
                            } else {
                                img = this->bottom;
                            }
                        } else if (row == 0) {
                            if (col == 0) {
                                img = this->conerTopLeft;
                            } else if (col == maxIndex) {
                                img = this->conerTopRight;
                            } else {
                                img = this->top;
                            }
                        } else {
                            if (col == 0) {
                                img = this->left;
                            } else if (col == maxIndex) {
                                img = this->right;
                            } else {
                                img = this->middle;
                            }
                        }
                    }
                }
                int8_t index = row * Size + col;
                auto label = new QLabel(this);
                label->setPixmap(*img);
                label->setScaledContents(true);
                this->gridLayout->addWidget(label, row, col);
            }
        }
    }

    void mousePressEvent(QMouseEvent *event) override {
        QWidget* child = childAt(event->pos());
        QLabel* label = qobject_cast<QLabel*>(child);
        if (label) {
            auto size = static_cast<int8_t>(std::sqrt(static_cast<float>(gridLayout->count())));
            for (int i = 0; i < gridLayout->count(); ++i) {
                const auto* item = gridLayout->itemAt(i);
                if (item && item->widget() == label) {
                    int x, col, rowSpan, colSpan;
                    gridLayout->getItemPosition(i, &x, &col, &rowSpan, &colSpan);
                    auto row = (size - 1) - (x % size);
                    auto m = Move(ColorNone, col, row);
                    emit clicked(m);
                    return;
                }
            }
        }
    }

  signals:
    void clicked(Move move);
};