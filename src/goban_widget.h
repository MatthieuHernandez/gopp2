#include <QLabel>
#include <QPixmap>

template<int8_t Size>
class GobanWidget : public QWidget {
  public:
    GobanWidget(QWidget *parent = nullptr) : QWidget(parent) {
        constexpr int8_t size = (Size + 1) * (Size + 1);
        auto *layout = new QGridLayout(this);
        layout->setSpacing(0);
        std::array<QLabel*, 100> labels;
        QPixmap img("C:/Programming/Git/gopp2/build/Release/bin/images/goban_part1.png");
        if (img.isNull()) {
            qWarning("Cannot display goban.");
            return;
        }

        for (int8_t row = 0; row < (Size + 1); ++row) {
            for (int8_t col = 0; col < (Size + 1); ++col) {
                int8_t index = row * (Size + 1) + col;
                labels[index] = new QLabel(this);
                labels[index]->setPixmap(img);
                labels[index]->setScaledContents(true);
                layout->addWidget(labels[index], row, col);
            }
        }

        this->setLayout(layout);
    }
};