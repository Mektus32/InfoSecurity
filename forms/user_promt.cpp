#include "user_promt.h"

#include <QHBoxLayout>
#include <QPushButton>

namespace forms {

UserPromt::UserPromt(QWidget* main_widget)
    : main_form_(dynamic_cast<MainWindow*>(main_widget))
{
    QHBoxLayout* layout = new QHBoxLayout();

    QPushButton* change_password = new QPushButton("Сменить пароль");

    connect(change_password, &QPushButton::clicked, [this](){
        this->main_form_->ChangeState(States::kUpdateUser);
    });

    QPushButton* cancel = new QPushButton("Отмена");

    connect(cancel, &QPushButton::clicked, [this](){
        this->main_form_->ChangeState(States::kPromt);
    });

    layout->addWidget(change_password);
    layout->addWidget(cancel);

    setLayout(layout);
}

} // namespace forms
