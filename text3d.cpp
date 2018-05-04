#include <QFont>
#include <QList>
#include <QPainter>
#include <QOpenGLFunctions>
#include <QChar>
#include <gl/GLU.h>
#include "text3d.h"
#include <iostream>

typedef void (__stdcall *TessFuncPtr)();

Text3D::Text3D()
    : glyphthickness(1.0f), base(0) {

}

void Text3D::initFont(QFont& f, float thickness) {
    font = &f;
    fm = new QFontMetricsF(f);
    glyphthickness = thickness;
    if (base) {
        glDeleteLists(base, 256);
    }
    base = glGenLists(256);
    if (!base) {
        throw;
    }
    for (int i=0; i<256;++i) {
        buildGlyph(base+i, (char)i);
    }
}

void Text3D::print(QString text) {
    double width = fm->width(text);
    glPushMatrix();
    glTranslated(-width * .5, 0, 0);
    glPushAttrib(GL_LIST_BIT);
    glListBase(base);
    glCallLists(text.length(), GL_UNSIGNED_BYTE, text.toLocal8Bit());
    glPopAttrib();
    glPopMatrix();
}

void Text3D::buildGlyph(GLuint listbase, int c) {
    GLUtriangulatorObj *tobj;
    QPainterPath path;
    path.addText(QPointF(0,0), *font, QString((char)c));
    QList<QPolygonF> poly = path.toSubpathPolygons();
    tobj = gluNewTess();
    gluTessCallback(tobj, GLU_TESS_BEGIN, (TessFuncPtr)glBegin);
    gluTessCallback(tobj, GLU_TESS_VERTEX, (TessFuncPtr)glVertex3dv);
    gluTessCallback(tobj, GLU_TESS_END, (TessFuncPtr)glEnd);
    gluTessProperty(tobj, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_ODD);
    glNewList(listbase, GL_COMPILE);
    glShadeModel(GL_FLAT);
    gluTessBeginPolygon(tobj, 0 );
    int elements = 0;
    for (QList<QPolygonF>::iterator it = poly.begin(); it != poly.end(); it++) {
        elements += (*it).size();
    }
    GLdouble* vertices = (GLdouble*) malloc(elements * 3 * sizeof(GLdouble));
    int j = 0;
    for (QList<QPolygonF>::iterator it = poly.begin(); it != poly.end(); it++) {
        gluTessBeginContour(tobj);
        int i=0;
        for (QPolygonF::iterator p = (*it).begin(); p != it->end(); p++) {
            int off = j+i;
            vertices[off + 0] = p->rx();
            vertices[off + 1] = -p->ry();
            vertices[off + 2] = 0;
            gluTessVertex(tobj, &vertices[off], &vertices[off] );
            i += 3;
        }
        gluTessEndContour(tobj);
        j += (*it).size() * 3;
    }
    gluTessEndPolygon(tobj);
    gluTessBeginPolygon(tobj, 0 );
    j = 0;
    for (QList<QPolygonF>::iterator it = poly.begin(); it != poly.end(); it++) {
        gluTessBeginContour(tobj);
        int i = 0;
        for (QPolygonF::iterator p = (*it).begin(); p != it->end(); p++) {
            int off = j + i;
            vertices[off + 0] = p->rx();
            vertices[off + 1] = -p->ry();
            vertices[off + 2] = -glyphthickness;
            gluTessVertex(tobj, &vertices[off], &vertices[off] );
            i += 3;
        }
        gluTessEndContour(tobj);
        j += (*it).size()*3;
    }
    gluTessEndPolygon(tobj);
    free(vertices);
    for (QList<QPolygonF>::iterator it = poly.begin(); it != poly.end(); it++) {
        glBegin(GL_QUAD_STRIP);
        QPolygonF::iterator p;
        for (p = (*it).begin(); p != it->end(); p++) {
            glVertex3f(p->rx(), -p->ry(), 0.0f);
            glVertex3f(p->rx(), -p->ry(), -glyphthickness);
        }
        p = (*it).begin();
        glVertex3f(p->rx(), -p->ry(), 0.0f);
        glVertex3f(p->rx(), -p->ry(), -glyphthickness);
        glEnd();
    }
    GLfloat gwidth = (float)fm->width(QChar('c'));
    glTranslatef(gwidth ,0.0f,0.0f);
    glEndList();
    gluDeleteTess(tobj);
}
