#include <QLabel>
#include <QPixmap>

template<int8_t Size>
class GobanWidget : public QWidget {
  private:

  public:
    GobanWidget(QWidget *parent = nullptr) : QWidget(parent) {
        QPixmap middle("C:/Programming/Git/gopp2/build/Release/bin/images/middle.png");
        QPixmap hoshi("C:/Programming/Git/gopp2/build/Release/bin/images/hoshi.png");
        QPixmap left("C:/Programming/Git/gopp2/build/Release/bin/images/left.png");
        QPixmap right("C:/Programming/Git/gopp2/build/Release/bin/images/right.png");
        QPixmap top("C:/Programming/Git/gopp2/build/Release/bin/images/top.png");
        QPixmap bottom("C:/Programming/Git/gopp2/build/Release/bin/images/bottom.png");
        QPixmap conerTopLeft("C:/Programming/Git/gopp2/build/Release/bin/images/coner_top_left.png");
        QPixmap conerBottomLeft("C:/Programming/Git/gopp2/build/Release/bin/images/coner_bottom_left.png");
        QPixmap conerTopRight("C:/Programming/Git/gopp2/build/Release/bin/images/coner_top_right.png");
        QPixmap conerBottomRight("C:/Programming/Git/gopp2/build/Release/bin/images/coner_bottom_right.png");
        QPixmap blackStone("C:/Programming/Git/gopp2/build/Release/bin/images/black_stone.png");
        QPixmap WhiteStone("C:/Programming/Git/gopp2/build/Release/bin/images/white_stone.png");

        auto *layout = new QGridLayout(this);
        layout->setSpacing(0);

        std::array<QLabel*, Size*Size> labels = {nullptr};

        int8_t maxIndex = Size - 1;
        QPixmap* img = nullptr;
        for (int8_t row = 0; row < Size; ++row) {
            for (int8_t col = 0; col < Size; ++col) {
                if ((Size == 9 &&
                    ((row == 2 && (col == 2 || col == 6)) ||
                    (row ==  6 && (col == 2 || col == 6)))) ||
                    (Size == 19 &&
                    ((row == 15 && (col == 3 || col == 9 || col == 15)) ||
                    (row == 9 && (col == 3 || col == 9 || col == 15)) ||
                    (row ==  3 && (col == 3 || col == 9 || col == 15)))) ) {
                        img = &hoshi;
                } else {
                    if (row == maxIndex) {
                        if (col == 0) {
                            img = &conerBottomLeft;
                        } 
                        else if (col == maxIndex) {
                            img = &conerBottomRight;
                        } else {
                            img = &bottom;
                        }
                    } else if (row == 0) {
                        if (col == 0) {
                            img = &conerTopLeft;
                        } else if (col == maxIndex) {
                            img = &conerTopRight;
                        } else {
                            img = &top;
                        }
                    } else {
                        if (col == 0) {
                            img = &left;
                        } else if (col == maxIndex) {
                            img = &right;
                        } else {
                            img = &middle;
                        }
                    }
                }
                int8_t index = row * Size + col;
                labels[index] = new QLabel(this);
                labels[index]->setPixmap(*img);
                labels[index]->setScaledContents(true);
                layout->addWidget(labels[index], row, col);
            }
        }
        this->setLayout(layout);
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }
};