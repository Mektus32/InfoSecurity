#include "utils.hpp"

#include <QMessageBox>

namespace utils {

QMenuBar* CreateMenuBar(QWidget *parent) {

    QMenuBar* menu_bar = new QMenuBar(parent);
    QMenu* info_menu = new QMenu("Справка");
    QAction* info_action = new QAction("О программе");
    QObject::connect(info_action, &QAction::triggered, [](){
        QMessageBox message(QMessageBox::Icon::Information, "О программе",
                            "Автор: Тарасьян М.Г. ИДБ-18-02\n"
                            "Задание: Чередование букв, знаков препинания и снова букв");
        message.setFocus();
        message.exec();
    });
    info_menu->addAction(info_action);
    menu_bar->addMenu(info_menu);
    return menu_bar;
}

} // namespace utils
