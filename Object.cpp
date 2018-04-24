#include "Object.h"

Object::Object(double x, double y, double w, double h){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

double Object::getX(){
	return x;
}
double Object::getY(){
	return y;
}
double Object::getW(){
	return w;
}
double Object::getH(){
	return h;
}


void Object::shiftX(double xShift){
	x += xShift;
}
void Object::shiftY(double yShift){
	y += yShift;
}
/*
Rect* Object::getRect(){
	return new Rect(x,y,w,h);
}
*/

bool Object::contains(Object* obj){
	
	double rx = obj->getX();
	double ry = obj->getY();
	double rw = obj->getW();
	double rh = obj->getH();
	
	if(containsPoint(rx, ry)) return true;
	else if(containsPoint(rx+rw, ry)) return true;
	else if(containsPoint(rx+rw, ry+rh)) return true;
	else if(containsPoint(rx, ry+rh)) return true;
	else if(obj->containsPoint(x, y)) return true;
	else if(obj->containsPoint(x+w, y)) return true;
	else if(obj->containsPoint(x, y+h)) return true;
	else if(obj->containsPoint(x+w, y+h)) return true;
	else return false;
}
bool Object::containsPoint(double px,double py){
	if((px > x) && (px < x+w) && (py > y) && (py < y+h)){
		return true;
	}
	else return false;
}

bool Object::nOverlap(Object* obj){
	return (obj->containsPoint(x,y) && obj->containsPoint(x+w, y));
}
bool Object::neOverlap(Object* obj){
	return (obj->containsPoint(x+w, y));
}
bool Object::eOverlap(Object* obj){
	return (obj->containsPoint(x+w,y) && obj->containsPoint(x+w, y+h));
}
bool Object::seOverlap(Object* obj){
	return (obj->containsPoint(x+w, y+h));
}
bool Object::sOverlap(Object* obj){
	return (obj->containsPoint(x,y+h) && obj->containsPoint(x+w, y+h));
}
bool Object::swOverlap(Object* obj){
	return (obj->containsPoint(x,y+h));
}
bool Object::wOverlap(Object* obj){
	return (obj->containsPoint(x,y) && obj->containsPoint(x, y+h));
}
bool Object::nwOverlap(Object* obj){
	return (obj->containsPoint(x,y));
}

double Object::getNOverlap(Object* obj){
	return (obj->getY()+obj->getH()-y);
}
double Object::getSOverlap(Object* obj){
	return obj->getY()-(y+h);
}
double Object::getEOverlap(Object* obj){
	return obj->getX()-(x+w);
}
double Object::getWOverlap(Object* obj){
	return (obj->getX()+obj->getW())-x;
}

Object::~Object(){
	
}
