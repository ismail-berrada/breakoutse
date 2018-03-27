#include <QApplication>
#include <ctime>
#include "game.h"

int main(int argc, char *argv[]) {
    srand(time(nullptr));
    QApplication app(argc, argv);
    Game game;
    game.show();
    return app.exec();
}
