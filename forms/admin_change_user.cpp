#include "admin_change_user.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QMessageBox>

namespace forms {

AdminChangeUser::AdminChangeUser(QWidget* main_widget)
    : main_form_(dynamic_cast<MainWindow*>(main_widget))
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QHBoxLayout* username_layout = new QHBoxLayout();
    QLabel* username_label = new QLabel("Имя пользователя");

    username_layout->addWidget(username_label);
    username_layout->addWidget(&this->username_);

    QHBoxLayout* blocked_layout = new QHBoxLayout();
    QLabel* blocked_label = new QLabel("Блокировка");

    blocked_layout->addWidget(blocked_label);
    blocked_layout->addWidget(&this->is_blocked_);

    QHBoxLayout* passord_layout = new QHBoxLayout();
    QLabel* password_label = new QLabel("Парольное ограничение");

    passord_layout->addWidget(password_label);
    passord_layout->addWidget(&this->is_limited_);

    QHBoxLayout* first_line_buttons = new QHBoxLayout();
    QPushButton* next = new QPushButton("Следующий");
    QPushButton* save = new QPushButton("Сохранить");

    first_line_buttons->addWidget(next);
    first_line_buttons->addWidget(save);

    QHBoxLayout* second_line_buttons = new QHBoxLayout();
    QPushButton* ok = new QPushButton("Ок");

    second_line_buttons->addWidget(ok);

    layout->addLayout(username_layout);
    layout->addLayout(blocked_layout);
    layout->addLayout(passord_layout);
    layout->addLayout(first_line_buttons);
    layout->addLayout(second_line_buttons);

    UpdateWidgetData("");


    connect(next, &QPushButton::clicked, [this](){
        this->main_form_->GetNextUser(this->username_.text().toStdString());
        UpdateWidgetData(this->username_.text().toStdString());
    });

    connect(save, &QPushButton::clicked, [this]() -> void {
        if (this->username_.text().isEmpty()) {
            QMessageBox message(QMessageBox::Icon::Critical, "Ошибка",
                                "Нельзя сохранить пользователя с пустым именем");
            message.setFocus();
            message.exec();
            return;
        }
        users::User user(this->username_.text().toStdString());

        if (this->is_blocked_.isChecked() && !this->main_form_->GetUserByName(this->username_.text().toStdString(), user)) {
            QMessageBox message(QMessageBox::Icon::Critical, "Ошибка",
                                "Нельзя создать заблокированного пользователя");
            message.setFocus();
            message.exec();
            return;
        }
        user.SetIsBlocked(this->is_blocked_.isChecked());
        user.SetPasswordLimit(this->is_limited_.isChecked());
        this->main_form_->UpdateUserValue(std::move(user));

    });

    connect(ok, &QPushButton::clicked, [this](){
        this->main_form_->ChangeState(States::kAdmin);
    });

}

void AdminChangeUser::UpdateWidgetData(const std::string& name) {
    auto user = main_form_->GetNextUser(name);
    username_.setText(user.GetName().c_str());
    is_blocked_.setChecked(user.GetIsBlocked());
    is_limited_.setChecked(user.GetIsLimited());
    this->update();
}

} // namespace forms
