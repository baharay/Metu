#include "pixel.h"
#include <iostream>
Pixel::Pixel(uchar r, uchar g, uchar b){
	red = r;
	green = g;
	blue = b;
}
        uchar& Pixel::operator[](int index){
        	if (index== 0)
        		return red;
        	else if (index == 1)
        		return green;
        	else
        		return blue;

        }

        const uchar& Pixel::operator[](int index) const{
        	if (index== 0)
        		return red;
        	else if (index == 1)
        		return green;
        	else
        		return blue;

        }

        // Alternative accessors functions
        uchar Pixel::getR() const{
        	return red;
        }
        uchar Pixel::getG() const{
        	return green;
        }
        uchar Pixel::getB() const{
        	return blue;
        }

        // Alternative mutator functions
        void Pixel::setR(uchar r){
        	red = r;
        }
        void Pixel::setG(uchar g){
        	green = g;
        }
        void Pixel::setB(uchar b){
        	blue = b;
        }

        std::ostream& operator<<(std::ostream& os, const Pixel& p){
        	std::cout<< "(" << int(p.red) << "," << int(p.green) << "," << int(p.blue) << ")";

        }
