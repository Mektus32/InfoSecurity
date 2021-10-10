#pragma once

#include "main_window.hpp"

#include <QLineEdit>

namespace forms {

class FileEncryptDecrypt : public QWidget
{
public:
    FileEncryptDecrypt(QWidget* main_widget);

private:
    MainWindow* main_form_;
    QLineEdit code_;
};

} // namespace forms
