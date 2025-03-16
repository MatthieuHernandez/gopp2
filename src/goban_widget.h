#include <QLabel>
#include <QPixmap>

template<int8_t Size>
class GobanWidget : public QWidget {
  public:
    GobanWidget(QWidget *parent = nullptr) : QWidget(parent) {
        constexpr int16_t size = Size * Size;
        auto *layout = new QGridLayout(this);
        layout->setSpacing(0);
        std::array<QLabel*, size> labels;
        QPixmap img("C:/Programming/Git/gopp2/build/Release/bin/images/goban_part1.png");
        if (img.isNull()) {
            qWarning("Cannot display goban.");
            return;
        }

        for (int8_t row = 0; row < Size; ++row) {
            for (int8_t col = 0; col < Size; ++col) {
                int8_t index = row * Size + col;
                labels[index] = new QLabel(this);
                labels[index]->setPixmap(img);
                labels[index]->setScaledContents(true);
                layout->addWidget(labels[index], row, col);
            }
        }

        this->setLayout(layout);
    }
};