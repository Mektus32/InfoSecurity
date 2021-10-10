#include "file_encrypt_decrypt.h"

#include <utils/utils.hpp>

#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

namespace forms {

FileEncryptDecrypt::FileEncryptDecrypt(QWidget* main_widget)
    : main_form_(dynamic_cast<MainWindow*>(main_widget))
{
    QVBoxLayout* layout = new QVBoxLayout();
    code_.setEchoMode(QLineEdit::Password);

    QPushButton* button = new QPushButton("Ок");

    connect(button, &QPushButton::clicked, [this](){
        if (!utils::Decrypt(this->code_.text().toStdString())) {
            QMessageBox message(QMessageBox::Icon::Critical, "Ошибка данных",
                                "Неправильная паролевая фраза");
            message.setFocus();
            message.exec();
        } else {
            this->main_form_->ChangeState(States::kPromt);
        }
    });

    layout->addWidget(&code_);
    layout->addWidget(button);

    setLayout(layout);
}

} // namespace forms
