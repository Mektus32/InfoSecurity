#include "user.hpp"

#include <QRegularExpression>

namespace users {

User::User(const std::string& name, bool is_blocked, bool password_limit)
    : name_(name), is_blocked_(is_blocked), password_limit_(password_limit)
{

}

User& User::operator=(User &&user) {
    this->name_ = user.name_;
    this->password_ = user.password_;
    this->is_blocked_ = user.is_blocked_;
    this->password_limit_ = user.password_limit_;

    {
        user.name_.clear();
        user.password_.clear();
        user.is_blocked_ = false;
        user.password_limit_ = false;
    }

    return *this;
}

bool User::operator==(const User &rhs) const {
    return name_ == rhs.name_;
}

bool User::operator!=(const User &rhs) const {
    return !(*this == rhs);
}

bool User::ChangePassword(const std::string& password) {
    QRegularExpression regex("^([A-Za-z]+)([\\.;,:\\-\\?\\!\"\\'\\(\\)]+)([A-Za-z]+)$");
    if ((password_limit_ && !regex.match(QString(password.c_str())).hasMatch())
            || password.empty()) {
        return false;
    }
    password_ = password;
    return true;
}

void User::SetIsBlocked(bool is_blocked) {
    is_blocked_ = is_blocked;
}

void User::SetPasswordLimit(bool password_limit) {
    password_limit_ = password_limit;
}

std::string User::GetName() const {
    return name_;
}

std::string User::GetPassword() const {
    return password_;
}

} // namespace users
