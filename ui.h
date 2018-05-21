#ifndef UI_H
#define UI_H

class Text3D;

// A 3D user interface that displays the user score, extra balls and the title.
class UI {
public:
    UI();
    ~UI();
    void update(double dt);
    void render();
    void resetScore();

private:
    Text3D *text;
    double score;
    double angle = 0;
};

#endif // UI_H
