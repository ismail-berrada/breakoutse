#include <QApplication>
#include <ctime>
#include "game.h"
#include "motiondetector.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    QApplication app(argc, argv);
    MotionDetector motionDetector;
    motionDetector.start();
    Game game(motionDetector);
    game.show();
    app.exec();
    motionDetector.quit();
    return 0;
}
