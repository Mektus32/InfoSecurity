#pragma once

#include <users/user.hpp>

#include <map>

#include <QMainWindow>

namespace forms{

enum class States {kPromt, kUpdateUser, kAdmin, kAdminChangeUser};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

    void ChangeState(States new_state);

    bool SetCurrentUser(const std::string& name,
                         const std::string& password);

    bool UpdateUserPassword(const std::string& new_password);

    users::User GetNextUser();

    bool UpdateUserValue(users::User&& user);


private:
    std::map<std::string, users::User> all_users_;
    std::map<std::string, users::User>::iterator current_user_;
    users::User admin_;
    States current_state_;
    QWidget* current_form_;
};

} // namespace forms
