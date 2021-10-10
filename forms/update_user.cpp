#include "update_user.hpp"

#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

namespace forms {

UpdateUser::UpdateUser(QWidget* main_widget)
    : main_form_(dynamic_cast<MainWindow*>(main_widget))
{
    QVBoxLayout* layout = new QVBoxLayout(this);


    QHBoxLayout* password_layout = new QHBoxLayout();
    QLabel* password_lable = new QLabel("Новый Пароль: ");
    QLineEdit* password_ledit = new QLineEdit();

    password_layout->addWidget(password_lable);
    password_layout->addWidget(password_ledit);


    QHBoxLayout* repeat_password_layout = new QHBoxLayout();
    QLabel* repeat_password_lable = new QLabel("Повторите пароль: ");
    QLineEdit* repeat_password_ledit = new QLineEdit();

    repeat_password_layout->addWidget(repeat_password_lable);
    repeat_password_layout->addWidget(repeat_password_ledit);


    QHBoxLayout* buttons_layout = new QHBoxLayout();
    QPushButton* confirm = new QPushButton("Подтвердить");
    QPushButton* cancel = new QPushButton("Отмена");

    buttons_layout->addWidget(confirm);
    buttons_layout->addWidget(cancel);

    layout->addLayout(password_layout);
    layout->addLayout(repeat_password_layout);
    layout->addLayout(buttons_layout);

    connect(confirm, &QPushButton::clicked,
            [this, password_ledit, repeat_password_ledit](){
        if (password_ledit->text() != repeat_password_ledit->text()) {
            QMessageBox message(QMessageBox::Icon::Warning, "Ошибка ввода пароля",
                                "Пароли не совпадают, попробуйте еще раз");
            message.setFocus();
            message.exec();
        } else {
           if (!this->main_form_->UpdateUserPassword(password_ledit->text().toStdString())) {
               QMessageBox message(QMessageBox::Icon::Warning, "Ошибка ввода пароля",
                                   "Пароль не удовлетворяет требования, попробуйте еще раз");
               message.setFocus();
               message.exec();
           } else {
               if (this->main_form_->CurrentUserIsAdmin()) {
                   this->main_form_->ChangeState(States::kAdmin);
               } else {
                   this->main_form_->ChangeState(States::kUserPromt);
               }
           }
        }
    });

    connect(cancel, &QPushButton::clicked, [this](){
        if (!this->main_form_->CurrentUserHasPassword()) {
            QMessageBox message(QMessageBox::Icon::Critical, "Ошибка ввода пароля",
                                "Нельзя выйти без смены пароля");
            message.setFocus();
            message.exec();
        } else {
            if (this->main_form_->CurrentUserIsAdmin()) {
                this->main_form_->ChangeState(States::kAdmin);
            } else {
                this->main_form_->ChangeState(States::kUserPromt);
            }
        }
    });


}

} // namespace forms
