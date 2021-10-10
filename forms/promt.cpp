#include "promt.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

namespace forms {

namespace {

const std::string kAdminName{"ADMIN"};

} // namespace

Promt::Promt(QWidget* main_widget)
    : main_form_(dynamic_cast<MainWindow*>(main_widget))
{   
    QVBoxLayout* layout = new QVBoxLayout();

    QHBoxLayout* username_layout = new QHBoxLayout();
    QLabel* name_lable = new QLabel("Имя пользователя: ");
    username_layout->addWidget(name_lable);
    username_layout->addWidget(&username_);

    QHBoxLayout* password_layout = new QHBoxLayout();
    QLabel* password_lable = new QLabel("Пароль: ");
    password_layout->addWidget(password_lable);
    password_layout->addWidget(&password_);
    password_.setEchoMode(QLineEdit::Password);

    QPushButton* button = new QPushButton("Войти");

    connect(button, &QPushButton::clicked, this, &Promt::CheckPassword);

    layout->addLayout(username_layout);
    layout->addLayout(password_layout);
    layout->addWidget(button);

    setLayout(layout);
}

void Promt::CheckPassword() {
    static int retry_count;
    static QString name;
    if (name == this->username_.text()) {
        SendUser(retry_count);
    } else {
        name = this->username_.text();
        retry_count = 0;
        SendUser(retry_count);
    }
}

void Promt::SendUser(int& retry_count) {
    [[maube_unused]]users::User tmp;
    if (!main_form_->SetCurrentUser(
                this->username_.text().toStdString(),
                this->password_.text().toStdString())) {
        if (!this->username_.text().size()
                   || !this->main_form_->GetUserByName(this->username_.text().toStdString(), tmp)) {
            QMessageBox message(QMessageBox::Icon::Critical, "Ошибка ввода пароля",
                                "Неправильное имя пользователя");
            message.setFocus();
            message.exec();
        } else {
            std::string text("Неправильный пароль!\n Осталось попыток: ");
            QMessageBox message(QMessageBox::Icon::Critical, "Ошибка ввода пароля",
                                (text  + std::to_string(2 - retry_count)).c_str());
            message.setFocus();
            message.exec();
        }

        if (++retry_count == 3) {
            QMessageBox message(QMessageBox::Icon::Critical, "Ошибка ввода пароля",
                                "Будет выполнен выход из программы!");
            message.setFocus();
            message.exec();
            exit(0);
        }
    } else if (this->main_form_->CurrentUserIsBlocked()) {
        QMessageBox message(QMessageBox::Icon::Critical, "Ошибка",
                            "Вы заблокированы!\nОбратитесь к администратору");
        message.setFocus();
        message.exec();
    } else {
        retry_count = 0;
        if (password_.text().isEmpty() || (this->username_.text().toStdString() != kAdminName && !main_form_->CurrentUserHasPassword())) {
            main_form_->ChangeState(States::kUpdateUser);
        } else if (this->username_.text().toStdString() != kAdminName) {
            main_form_->ChangeState(States::kUserPromt);
        } else {
            main_form_->ChangeState(States::kAdmin);
        }
    }
}

} // namespace forms
