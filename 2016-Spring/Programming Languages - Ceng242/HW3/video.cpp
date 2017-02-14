#include "video.h"
#include "frame.h"
#include <iostream>
        // The default constructor creates an empty video
        // (frames = NULL) and zero number of frames
        Video::Video(){
        	frames= NULL;
        	nFrames = 0;
        	mark=0;
        }

        // The copy constructor
        Video::Video(const Video& rhs){
        	nFrames = rhs.nFrames;
        	mark = rhs.mark;
        	frames = new Frame[rhs.nFrames];
        	for (int i = 0; i < nFrames; ++i)
        	 {
        			
        			frames[i] =rhs.frames[i];
        	 } 

        }

        // The destructor
        Video::~Video(){
        	delete[] frames;
        }

        // The assignment operator
        Video& Video::operator=(const Video& rhs){

        	if (this != &rhs)
        		
        	{
  	
        		nFrames = rhs.nFrames;
        		mark = rhs.mark;
        		delete[] frames;  
        		frames = new Frame[rhs.nFrames];
        		for (int i = 0; i < rhs.nFrames; ++i)
        		{
        			
        			frames[i] = rhs.frames[i];
        		}

        		return *this;
        	}
        }

        // Inserts the given frame at the end of this video.
        // Can be used by chaining: (video << frame1 << frame2 << ...)
        Video& Video::operator<<(const Frame& frame){
        	
        	Frame * temp = new Frame[nFrames+1];
        	for (int i = 0; i < nFrames; ++i)
        	{
        		temp[i] = frames[i];

        	}
        	
   
        	delete[] frames; //ÇALIŞIYO ????!!!


 			frames = temp;
        	 frames[nFrames] = frame;


        	 nFrames++;
        	return *this;

        }

        // Extracts a frame from the given video.
        // Can be used by chaining: (video >> frame1 >> frame2 >> ...)
        // Note that each application of this operator must return
        // the "next" frame.
        Video& Video::operator>>(Frame& frame){
        	frame = frames[mark];
        	mark++;
        	return *this;
        }

        // Resets the stream such that the first operator>> after a
        // call to this function will extract the first frame again.
        void Video::resetStream(){
        	mark=0;
        }

        // Retrieves the frame given by the frameIndex
        Frame Video::getFrame(int frameIndex) const{
        	return Frame(frames[frameIndex]);
        }

        // Removes the frame given by the frameIndex.
        // After removal there should be no "gaps" in the
        // video. That is, the following frames must be
        // shifted to fill this gap.
        //MEMORY LEAK VAR
        void Video::dropFrame(int frameIndex){

        	Frame * temp = new Frame[nFrames];
        	for (int i = 0; i < nFrames; ++i)
        	{
        		temp[i] = frames[i];
        	}
        	
        
        	delete[] frames; //ÇALIŞIYO
        	nFrames--;
        	frames = new Frame[nFrames];
        	for (int i = 0; i < nFrames; ++i)
        	{
        		if(i!=frameIndex)
        		frames[i] = (temp[i]);
        		else{
        				for (int j = i; j < nFrames-1; ++j)
        				{
        					frames[j] = (temp[j+1]);
        				}
        				break;
        		}

        		}
        
        	delete[] temp;
        	if (frameIndex < mark)
        	{
        		mark--;
        	}
        }

        // Trims the video such that it contains only the frames
        // between startIndex inclusive and endIndex exclusive.
        void Video::trim(int startIndex, int endIndex){
        	Frame * temp = new Frame[nFrames];
        	for (int i = 0; i < nFrames; ++i)
        	{
        		temp[i] = frames[i];
        	}
        	
        

        	delete[] frames; //ÇALIŞIYO

        	nFrames = endIndex - startIndex;
        	frames = new Frame[nFrames];
        	for (int i = 0; i < nFrames; ++i)
        	{
        		
        		frames[i] = temp[i+startIndex];
        	}
        	if(mark<=startIndex)
        		mark = 0;
        	else if (mark>startIndex && mark<endIndex)
        	{
        		mark = mark-startIndex;
        	}
        	else
        		mark;
        	delete[] temp;
        }