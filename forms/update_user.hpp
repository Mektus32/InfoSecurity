#pragma once

#include "main_window.hpp"

#include <QWidget>

namespace forms {

class UpdateUser : public QWidget
{
public:
    UpdateUser(QWidget* main_widget);

private:
    MainWindow* main_form_;
};

} // namespace forms
