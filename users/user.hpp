#pragma once

#include <string>

namespace users {

class User
{
public:
    User(const std::string& name, bool is_blocked, bool password_limit);
    User() = default;
    User(const User& user) = default;

    User& operator=(const User& user) = default;
    User& operator=(User&& user);

    bool operator==(const User& rhs) const;
    bool operator!=(const User& rhs) const;

    bool ChangePassword(const std::string& password);
    void SetIsBlocked(bool is_blocked);
    void SetPasswordLimit(bool password_limit);

    std::string GetName() const;
    std::string GetPassword() const;

private:
    std::string name_;
    std::string password_;
    bool is_blocked_;
    bool password_limit_;
};

} // namespace users
