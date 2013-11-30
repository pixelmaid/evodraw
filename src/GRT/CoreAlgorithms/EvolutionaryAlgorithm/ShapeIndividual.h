//
//  ShapeIndividual.h
//  evodraw1
//
//  Created by jennifer mary jacobs on 11/14/13.
//
//

#ifndef evodraw1_ShapeIndividual_h
#define evodraw1_ShapeIndividual_h

#include "../../Util/GRTCommon.h"

namespace GRT{
    
    class ShapeIndividual{
    public:
        ShapeIndividual(){
            fitness = 0;
        }
        
        ShapeIndividual(const Individual &rhs){
            *this = rhs;
        }
        
        ~ShapeIndividual(){
            
        }
        
        ShapeIndividual& operator=(const ShapeIndividual &rhs){
            if( this != &rhs ){
                this->fitness = rhs.fitness;
                this->gene = rhs.gene;
            }
            return *this;
        }
        
        double fitness;
        VectorDouble gene;
    };
    
}

#endif //GRT_INDIVIDUAL_HEADER


