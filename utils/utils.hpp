#pragma once

#include <QMenuBar>

namespace utils {

QMenuBar* CreateMenuBar(QWidget *parent);
void Encrypt();
bool Decrypt(const std::string& password);

} // namespace utils
