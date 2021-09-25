#pragma once

#include "main_window.hpp"

#include <QWidget>
#include <QLineEdit>

namespace forms {

class Promt : public QWidget
{
public:
    Promt(QWidget* main_widget);

private slots:
    void CheckPassword();

private:
    QLineEdit username_;
    QLineEdit password_;
    MainWindow* main_form_;

private:
    void SendUser(int& retry_count);

};

} // namespace forms
