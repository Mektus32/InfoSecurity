#pragma once

#include "main_window.hpp"

#include <QWidget>

namespace forms {

class Admin : public QWidget
{
public:
    Admin(QWidget* main_widget);

private:
    MainWindow* main_form_;
};

} // namespace forms
