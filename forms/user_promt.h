#pragma once

#include "main_window.hpp"

namespace forms {

class UserPromt : public QWidget
{
public:
    UserPromt(QWidget* main_widget);

private:
    MainWindow* main_form_;
};

} // namespace forms
