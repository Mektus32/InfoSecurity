#include <forms/main_window.hpp>

#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    forms::MainWindow window;

    window.show();

    return app.exec();
}
