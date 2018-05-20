#ifndef UI_H
#define UI_H

class Text3D;

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
