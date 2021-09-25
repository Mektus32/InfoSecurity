#include "admin.hpp"

#include <QVBoxLayout>
#include <QPushButton>

namespace forms {

Admin::Admin(QWidget* main_widget)
    : main_form_(dynamic_cast<MainWindow*>(main_widget))
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QPushButton* change_password = new QPushButton("Смена пароля");
    QPushButton* admin_work = new QPushButton("Редактирование пользователей");
    QPushButton* cancel = new QPushButton("Отмена");

    layout->addWidget(change_password);
    layout->addWidget(admin_work);
    layout->addWidget(cancel);

}

} // namespace forms
