#ifndef TEXT3D_H
#define TEXT3D_H

#include <QOpenGLFunctions>
#include <QString>
#include <QFont>
#include <QFontMetricsF>

// Source: https://wiki.qt.io/Draw_Text_as_3D_Objects_with_OpenGL
class Text3D {
public:
    Text3D();
    void initFont(QFont &f, float thickness);
    void print(QString text);

private:
    void buildGlyph(GLuint b, int c);
    QFont* font;
    QFontMetricsF* fm;
    float glyphthickness;
    GLuint base;
};

#endif // TEXT3D_H
