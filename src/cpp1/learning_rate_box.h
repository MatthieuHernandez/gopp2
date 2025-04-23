#pragma once
#define QT_NO_KEYWORDS
#include <QDoubleSpinBox>
#include <QString>
#include <QLocale>

class LearningRateBox : public QDoubleSpinBox {
    Q_OBJECT

public:
    explicit LearningRateBox(QWidget* parent = nullptr)
        : QDoubleSpinBox(parent) {
            this->setDecimals(9);
            this->setValue(1e-4);
            this->setRange(0, 1);
        }

protected:
    QString textFromValue(double value) const override {
        return QString::number(value, 'e', 2);
    }

    double valueFromText(const QString& text) const override {
        bool ok;
        double val = QLocale().toDouble(text, &ok);
        return ok ? val : 0.0;
    }

    void stepBy(int steps) override {
        auto val = value();
        auto step = dynamicStep(val);
        step = (val + steps * step) == 0 ? step / 10.0 : step;
        double newVal = val + steps * step;
        newVal = std::clamp(newVal, minimum(), maximum());
        setValue(newVal);
    }

    double dynamicStep(double v) const {
        if (v <= 0.0) return 1e-9;
        double exp = std::floor(std::log10(v));
        return std::pow(10.0, exp);
    }
};