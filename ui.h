#ifndef UI_H
#define UI_H

class Text3D;

class UI {
public:
    UI();
    ~UI();
    void update(double dt);
    void render();

private:
    Text3D *scoreText;
    double score;
    double angle = 0;
};

#endif // UI_H
