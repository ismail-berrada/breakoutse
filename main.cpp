#include <QApplication>
#include <ctime>
#include "game.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    QApplication app(argc, argv);
    Game game;
    game.show();
    return app.exec();
}
