#include "frame.h"
#include "pixel.h"
#include <iostream>
        // The default constructor creates an empty
        // frame (data = NULL) with zero dimensions
        Frame::Frame(){
        	data = NULL;
        	width = 0;
        	height = 0;
        } 

        // Creates a frame with the given dimensions.
        // data must be allocated but its contents
        // are irrelevant.
        Frame::Frame(int widt, int heigh){
         	data = new Pixel[widt*heigh];
        	this->width = widt;
        	this->height = heigh;

        }

        // Creates a frame with the given dimensions.
        // Each pixel must be set to the given pixel.
        Frame::Frame(int widt, int heigh, const Pixel& p){
        	data = new Pixel[widt*heigh];
        	for (int i = 0; i < widt*heigh; i++)
        	{
        		data[i] = p;
        	}        	

        	this->width = widt;
        	this->height = heigh;

        }

        // The copy constructor
        Frame::Frame(const Frame& rhs){
        	if(rhs.data != NULL){
        	data = new Pixel[rhs.width*rhs.height];
        	for (int i = 0; i < rhs.width*rhs.height; i++)
        	{
        		data[i] = rhs.data[i];
        	}
        	width = rhs.width;
        	height = rhs.height;
      		}
        	else{
        		data = NULL;
        		width =0;
        		height =0;
        	}

        }

        // The destructor
        Frame::~Frame(){
        	 delete[] data;

        }

        // The assignment operator. Note that it must
        // return the reference of the current frame to
        // allow chained assignments.
        Frame& Frame::operator=(const Frame& rhs){
        	
        	if(rhs.data == NULL){
        		data = NULL;
        		width = 0;
        		height = 0;

        	}

        	else if (this != &rhs){
       
        		delete[] data; //BURASI ÇALIŞIYO

				int dimension = rhs.width * rhs.height;
	        	data = new Pixel[rhs.width * rhs.height];
	       
	        	for (int i = 0; i < rhs.width * rhs.height; i++)
	        	{
	        		
	        		data[i] = rhs.data[i];
	        	}
	        	width = rhs.width;
	        	height = rhs.height;
			}
	        	return *this;	
        	
        }


        // Returns a reference of the pixel at position (x, y).
        // Can be used to set the value of a pixel.
        Pixel& Frame::operator()(int x, int y){
        	return data[y*width+x];
        }

        // Returns a constant reference of the pixel at 
        // position (x, y). Can be used to retrieve the
        // value of a pixel.
        const Pixel& Frame::operator()(int x, int y) const{
        	return data[y*width+x];

        }

        // Returns a sub-frame of the current frame. The sub-frame
        // position and dimensions is specified in the rect parameter.
        Frame Frame::operator()(const Rect& rect) const{
        	Frame  subframe = Frame(rect.w, rect.h);
        	int k = 0;
        	for (int j = 0; j < rect.h; ++j)
        	{
        		for (int i = 0; i < rect.w; ++i)
        		{
        			subframe.data[k] = data[(rect.y+j)*width+rect.x+i];
        			k++;
        		}
        	}
        	return subframe;

        }

        // Returns true if the current frame is equal to the
        // input frame (rhs). Conditions for equality are:
        // (1) their dimensions should match AND (2) they
        // must contain the same pixel data.
        bool Frame::operator==(const Frame& rhs) const{
        	if ((width == rhs.width )&& (height == rhs.height)){
        		for (int i = 0; i < width*height; ++i)
        		{
        			if ((data[i].getR()== rhs.data[i].getR()) && (data[i].getG()== rhs.data[i].getG()) && (data[i].getB()== rhs.data[i].getB()))
        				continue;
        			else
        				return false;
        		}
        		return true;

        	}
        	return false;
        }

        // The opposite of the equality function
        bool Frame::operator!=(const Frame& rhs) const{
        	return !((*this)==rhs);
        }

        // Accessor functions for the width and height
        int Frame::getWidth() const{
        	return width;
        }
        int Frame::getHeight() const{
        	return height;
        }
        //BURADA DEEP COPY LAZIM MI ????
        // Clears the entire frame to the given pixel's color values
        // (Each pixel is updated with the given pixel's colors)
        void Frame::clear(const Pixel& p){
        	for (int i = 0; i < width*height; ++i)
        	{
        		data[i] = p;
        	}
        }

        // Clears the given sub-region inside the frame.
        // (Pixels within the given rectangle are updated
        // with the given colors).
        void Frame::clear(const Rect& rect, const Pixel& p){

        	for (int j = 0; j < rect.h; ++j)
        	{
        		for (int i = 0; i < rect.w; ++i)
        		{
        			data[(rect.y+j)*width+rect.x+i] = p;
        		}
        	}

        }
        //OLDU MU?
        // Crops the current frame to the given rectangle.
        void Frame::crop(const Rect& rect){
/*
        	Frame* subframe = new Frame(rect.w, rect.h);
        	int k =0;
        	for (int j = 0; j < rect.h; ++j)
        	{
        		for (int i = 0; i < rect.w; ++i)
        		{
        			subframe->data[k] = data[(rect.x+j)*width+rect.y+i];
        			k++;
        		}
        	}
        	//delete[] this->data;
        	this->data= subframe->data;*/
        	////delete subframe;
        	Frame * subframe = new Frame(rect.w, rect.h);
        	int k = 0;
        	for (int j = 0; j < rect.h; ++j)
        	{
        		for (int i = 0; i < rect.w; ++i)
        		{
        			subframe->data[k] = data[(rect.y+j)*width+rect.x+i];
        			k++;
        		}
        	}
        	*this = *subframe;
        	delete subframe;
        }

