#include "main_window.hpp"

#include <utils/utils.hpp>

#include "promt.hpp"
#include "update_user.hpp"
#include "admin.hpp"
#include "admin_change_user.hpp"
#include "user_promt.h"

#include <QJsonDocument>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>

#include <fstream>

namespace forms {

namespace {

const std::string kAdminName{"ADMIN"};
const std::string kFilePath{"data.json"};

} // namespace

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    GetDataFromFile();

    all_users_[""] = users::User(std::string(""));

    current_form_ = new forms::Promt(this);

    utils::CreateMenuBar(this);

    setCentralWidget(current_form_);

}

MainWindow::~MainWindow() {
    SetDataInFile();
}

void MainWindow::ChangeState(States new_state) {
    delete current_form_;

    switch (new_state) {
        case States::kPromt: current_form_ = new Promt(this); break;
        case States::kUpdateUser: current_form_ = new UpdateUser(this); break;
        case States::kAdmin: current_form_ = new Admin(this); break;
        case States::kAdminChangeUser: current_form_ = new AdminChangeUser(this); break;
    case States::kUserPromt:current_form_ = new UserPromt(this); break;
    }

    current_state_ = new_state;
    setCentralWidget(current_form_);
}

bool MainWindow::SetCurrentUser(const std::string &name,
                                const std::string &password) {
    if ((current_user_ = all_users_.find(name)) != all_users_.end() && name.size()) {

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

users::User MainWindow::GetNextUser(const std::string& name) {

    auto user = all_users_.find(name);
    if (user == all_users_.end()) {
        user = all_users_.begin();
    }

    if ((++user)->second != admin_
            || user == all_users_.end()) {
        --user;
    }

    if (++user == all_users_.end()) {
        user = all_users_.begin();
    }

    if (all_users_.size() > 2 && !user->first.size()) {
        qDebug() << user->first.c_str();
        user->second = GetNextUser(user->first);
    }

    return user->second;

}

bool MainWindow::UpdateUserValue(users::User &&user) {

    if (user.GetName() == kAdminName) {
        return false;
    }

    all_users_[user.GetName()] = std::move(user);

    return true;
}


bool MainWindow::CurrentUserIsAdmin() const {
    return current_user_->first == kAdminName;
}

bool MainWindow::CurrentUserHasPassword() const {
    if (current_user_->second.GetNeedChagePassword()) {
        return false;
    }

    return static_cast<bool>(current_user_->second.GetPassword().size());
}

bool MainWindow::CurrentUserIsBlocked() const {
    return current_user_->second.GetIsBlocked();
}

bool MainWindow::GetUserByName(const std::string &name, users::User& user) const {
    if (!all_users_.count(name) || !name.size()) {
        return false;
    }

    auto tmp = all_users_.at(name);
    user = tmp;

    return true;
}

void MainWindow::GetDataFromFile() {
    QFile file(kFilePath.c_str());

    system("pwd");

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox message(QMessageBox::Icon::Critical, "Ошибка данных",
                            "Внутренняя ошибка, прложение будет закрыто");
        message.setFocus();
        message.exec();
        exit(0);
    }

    auto byte_array = file.readAll();
    auto json_doc = QJsonDocument::fromJson(byte_array);

    for (const auto& elem : json_doc.object()["users"].toArray()) {
        users::User user(elem);
        all_users_[user.GetName()] = std::move(user);
    }
    file.close();
}

void MainWindow::SetDataInFile() {
    QFile file(kFilePath.c_str());

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox message(QMessageBox::Icon::Critical, "Ошибка данных",
                            "Внутренняя ошибка, прложение будет закрыто");
        message.setFocus();
        message.exec();
        exit(0);
    }

    QJsonDocument json_doc;
    QJsonArray json_array;
    for (const auto& [name, user] : all_users_) {
        if (name != "") {
            QJsonObject object;
            object["name"] = user.GetName().c_str();
            object["password"] = user.GetPassword().c_str();
            object["is_blocked"] = user.GetIsBlocked();
            object["is_limited"] = user.GetIsLimited();
            object["need_change_password"] = user.GetNeedChagePassword();
            json_array.append(object);
        }
    }
    QJsonObject object;
    object["users"] = json_array;
    json_doc.setObject(object);
    file.write(json_doc.toJson());

    file.close();
}

} // namespace forms
