#include "main_window.hpp"

#include <utils/utils.hpp>

#include "promt.hpp"
#include "update_user.hpp"
#include "admin.hpp"
#include "admin_change_user.hpp"

#include <QJsonDocument>
#include <QVBoxLayout>
#include <QPushButton>

#include <fstream>

namespace forms {

namespace {

const std::string kAdminName{"ADMIN"};

} // namespace

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
   all_users_[kAdminName] = users::User(kAdminName, false, false);


    QPushButton* button = new QPushButton("tmp");

    QVBoxLayout* layout = new QVBoxLayout(this);

    current_form_ = new forms::Promt(this);
    auto menu_bar = utils::CreateMenuBar(this);


    setCentralWidget(current_form_);

}

void MainWindow::ChangeState(States new_state) {
    delete current_form_;

    switch (new_state) {
        case States::kPromt: current_form_ = new forms::Promt(this); break;
        case States::kUpdateUser: current_form_ = new forms::UpdateUser(); break;
        case States::kAdmin: current_form_ = new forms::Admin(this); break;
        case States::kAdminChangeUser: current_form_ = new forms::AdminChangeUser(); break;
    }

    current_state_ = new_state;
    setCentralWidget(current_form_);
}

bool MainWindow::SetCurrentUser(const std::string &name,
                                const std::string &password) {
    if ((current_user_ = all_users_.find(name)) != all_users_.end()) {

        if (current_user_->second.GetPassword() == password) {
            if (name == kAdminName) {
                admin_ = current_user_->second;
            }

            return true;
        }
    }

    return false;
}

bool MainWindow::UpdateUserPassword(const std::string &new_password) {

    if (all_users_[current_user_->first].ChangePassword(new_password)) {
        current_user_->second.ChangePassword(new_password);
        admin_ = all_users_[current_user_->first];

        return true;
    }

    return false;

}

users::User MainWindow::GetNextUser() {

    if ((++current_user_)->second != admin_
            || current_user_ == all_users_.end()) {
        --current_user_;
    }

    if (++current_user_ == all_users_.end()) {
        current_user_ = all_users_.begin();
    }

    return current_user_->second;

}

bool MainWindow::UpdateUserValue(users::User &&user) {

    if (user.GetName() == kAdminName) {
        return false;
    }

    all_users_[user.GetName()] = std::move(user);

    return true;
}



} // namespace forms
