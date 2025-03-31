#pragma once
#include <QLabel>
#include <QPixmap>
#include <QGridLayout>

#include "../generate/goban.h"

class GobanWidget : public QWidget {
    //Q_OBJECT
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
        this->gridLayout->setSpacing(0);

        this->setLayout(this->gridLayout);
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }

    template<int8_t Size>
    void refresh(const Goban<Size>* goban) {
        this->resetLayout();
        std::array<QLabel*, Size*Size> labels = {nullptr};
        int8_t maxIndex = Size - 1;
        QPixmap* img = nullptr;
        for (int8_t col = 0; col < Size; ++col) {
            for (int8_t row = 0; row < Size; ++row) {
                if (goban->state[col][row].color == Color::Black) {
                    img = this->blackStone;
                } else if (goban->state[col][row].color == Color::White){
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
                labels[index] = new QLabel(this);
                labels[index]->setPixmap(*img);
                labels[index]->setScaledContents(true);
                this->gridLayout->addWidget(labels[index], row, col);
            }
        }
    }
};