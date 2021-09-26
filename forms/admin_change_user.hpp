#pragma once

#include "main_window.hpp"

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>

namespace forms {

class AdminChangeUser : public QWidget
{
public:
    AdminChangeUser(QWidget* main_widget);

private:
    MainWindow* main_form_;
    QLineEdit username_;
    QCheckBox is_blocked_;
    QCheckBox is_limited_;


private:
    void UpdateWidgetData(const std::string& name);
};

} // namespace forms
