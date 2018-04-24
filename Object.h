#ifndef INCLUDED_OBJECT_H
#define INCLUDED_OBJECT_H

#include <stdio.h>

class Object{
	
	protected:
		double x,y,w,h;
	public:
		Object(double x, double y, double w, double h);
		double getX();
		double getY();
		double getW();
		double getH();
	
	
		void shiftX(double xShift);
		void shiftY(double yShift);
		
	
		bool contains(Object* rect);
		bool containsPoint(double px,double py);
	
		bool nOverlap(Object* rect);
		bool neOverlap(Object* rect);
		bool eOverlap(Object* rect);
		bool seOverlap(Object* rect);
		bool sOverlap(Object* rect);
		bool swOverlap(Object* rect);
		bool wOverlap(Object* rect);
		bool nwOverlap(Object* rect);
	
		double getNOverlap(Object* rect);
		double getSOverlap(Object* rect);
		double getEOverlap(Object* rect);
		double getWOverlap(Object* rect);
		
		virtual ~Object();
};

#endif
