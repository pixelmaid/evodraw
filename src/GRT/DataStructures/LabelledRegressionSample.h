/**
 @file
 @author  Nicholas Gillian <ngillian@media.mit.edu>
 @version 1.0
 
 @section LICENSE
 GRT MIT License
 Copyright (c) <2012> <Nicholas Gillian, Media Lab, MIT>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 and associated documentation files (the "Software"), to deal in the Software without restriction, 
 including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial 
 portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
 LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 @section DESCRIPTION
 */

#ifndef GRT_LABELLED_REGRESSION_SAMPLE_HEADER
#define GRT_LABELLED_REGRESSION_SAMPLE_HEADER

#include "../Util/GRTCommon.h"

namespace GRT{

class LabelledRegressionSample{
public:
	LabelledRegressionSample();
	LabelledRegressionSample(const VectorDouble &inputVector,const VectorDouble &targetVector);
	LabelledRegressionSample(const LabelledRegressionSample &rhs);
	~LabelledRegressionSample();

	LabelledRegressionSample& operator= (const LabelledRegressionSample &rhs){
		if( this != &rhs){
			this->inputVector = rhs.inputVector;
			this->targetVector = rhs.targetVector;
		}
		return *this;
	}
	
	
	static bool sortByInputVectorAscending(const LabelledRegressionSample &a,const LabelledRegressionSample &b){
        return a.inputVector < b.inputVector;
    }

    static bool sortByInputVectorDescending(const LabelledRegressionSample &a,const LabelledRegressionSample &b){
        return a.inputVector > b.inputVector;
    }

	void clear();
	void set(const VectorDouble &inputVector,const VectorDouble &targetVector);

	UINT getNumInputDimensions(){ return (UINT)inputVector.size(); }
	UINT getNumTargetDimensions(){ return (UINT)targetVector.size(); }
    double getInputVectorValue(UINT index);
    double getTargetVectorValue(UINT index);
    VectorDouble getInputVector(){ return inputVector; }
    VectorDouble getTargetVector(){ return targetVector; }

private:
	VectorDouble inputVector;
	VectorDouble targetVector;
};

} //End of namespace GRT

#endif //GRT_LABELLED_REGRESSION_SAMPLE_HEADER
