/*
 GRT MIT License
 Copyright (c) <2013> <Nicholas Gillian, Media Lab, MIT>
 
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
 
 */

#ifndef GRT_EVOLUTIONARY_ALGORITHM_HEADER
#define GRT_EVOLUTIONARY_ALGORITHM_HEADER

#include "Individual.h"

namespace GRT{

template <typename INDIVIDUAL>
class EvolutionaryAlgorithm{

public:
    /**
     Default Constructor, if the populationSize and geneSize parameters are greater than zero then the algorithm will
     be initialized.
     
     @param UINT populationSize: the number of individuals in the population. Default value = 0
     @param UINT geneSize: the number of elements in each individuals gene. Default value = 0
     */
    EvolutionaryAlgorithm(UINT populationSize = 0,UINT geneSize = 0){
        maxIteration = 1000;
        storeRate = 1;
        mutationRate = 0.01;
        minChange = 1.0e-5;
        initialized = false;
        useElitism = true;
        storeHistory = true;
        
        initPopulation( populationSize, geneSize );
    }
    
    /**
     Default Destructor.
     */
    virtual ~EvolutionaryAlgorithm(){
        
    }
    
    /**
     This operator allows you to directly access each individual in the population. The user must ensure that index is a valid number
     in the range of [0 populationSize-1].
     
     @param const UINT index: the index of the individual you want to access
     @return returns a reference to the individual in the population at the specific index
     */
    INDIVIDUAL& operator[](const UINT &index){
        return population[ index ];
    }
    
    /**
     This function initalizes the population, setting each individual's genes to a random value in the range [0.0 1.0].
     Both the populationSize and geneSize parameters must be greater than zero.
     
     @param UINT populationSize: the number of individuals in the population
     @param UINT geneSize: the number of elements in each individuals gene
     @return returns true if the population was initalized, false otherwise
     */
    virtual bool initPopulation(UINT populationSize,UINT geneSize){
        
        initialized = false;
        this->populationSize = 0;
        this->geneSize = 0;
        population.clear();
        populationWeights.clear();
        accumSumLookup.clear();
        
        if( populationSize == 0 || geneSize == 0 ) return false;
        
        //Init the memory
        this->populationSize = populationSize;
        this->geneSize = geneSize;
        population.resize( populationSize );
        populationWeights.resize( populationSize );
        accumSumLookup.resize( populationSize );
        
        //Init each individual
        UINT i = 0;
        UINT index = 0;
        typename vector< INDIVIDUAL >::iterator populationIter = population.begin();
        vector< IndexedDouble >::iterator weightsIter = populationWeights.begin();
        vector< double >::iterator geneIter;
        
        while( populationIter != population.end() ){
            populationIter->fitness = 0;
            populationIter->gene.resize( geneSize );
            
            //Randomize the gene
            for(i=0; i<geneSize; i++){
                populationIter->gene[ i ] = rand.getRandomNumberUniform(0.0,1.0);
            }
            
            weightsIter->value = populationIter->fitness;
            weightsIter->index = index++;
            
            populationIter++;
            weightsIter++;
        }
        
        //Save the initial population as the parents
        parents = population;
        
        initialized = true;
        
        return true;
    }
    
    /**
     This function estimates the populations fitness, based on the training data. It will return a reference to the bestFitness value
     and the index of the individual with the best fitness.
     
     @param const MatrixDouble &trainingData: a reference to the trainingData that will be used to estimate the fitness
     @param double &bestFitness: a reference that will return the best fitness value
     @param UINT &bestIndex: a reference that will return the index of the individual with the best fitness
     @return returns true if the population fitness was estimated, false otherwise
     */
    virtual bool estimatePopulationFitness( const MatrixDouble &trainingData, double &bestFitness, UINT &bestIndex ){
        
        UINT index = 0;
        bestFitness = 0;
        bestIndex = 0;
        
        if( !initialized ) return false;
        
        typename vector< INDIVIDUAL >::iterator populationIter = population.begin();
        vector< IndexedDouble >::iterator weightsIter = populationWeights.begin();
        
        while( populationIter != population.end() ){
            //Compute the fitness of the current individual
            weightsIter->value = evaluateFitness( *populationIter, trainingData );
            weightsIter->index = index++;
            
            //Check to see if this is the best fitness so far
            if( weightsIter->value > bestFitness ){
                bestFitness = weightsIter->value;
                bestIndex = weightsIter->index;
            }
            
            //Update the iterators
            populationIter++;
            weightsIter++;
        }
        
        return true;
    }
    
    /**
     This function evolves the current population, based on the fitness of each individual.  You should compute the fitness of each individual 
     first before using this function.
     
     @return returns true if the population was evolved, false otherwise
     */
    virtual bool evolvePopulation(){
        
        if( !initialized ) return false;
        
        UINT i=0;
        UINT index = 0;
        UINT mom = 0;
        UINT dad = 0;
        UINT crossOverPoint = 0;
        typename vector< INDIVIDUAL >::iterator populationIter = population.begin();
        vector< IndexedDouble >::iterator weightsIter = populationWeights.begin();
        
        //Get the current weights values
        weightsIter = populationWeights.begin();
        while( populationIter != population.end() ){
            weightsIter->value = populationIter->fitness;
            weightsIter->index = index++;
            
            populationIter++;
            weightsIter++;
        }
        
        //Sort the weighted values by value in ascending order (so the least likely value is first, the second most likely is second, etc...
        sort(populationWeights.begin(),populationWeights.end(),IndexedDouble::sortIndexedDoubleByValueAscending);
        
        //Create the accumulated sum lookup table
        accumSumLookup[0] = populationWeights[0].value;
        for(unsigned int i=1; i<populationSize; i++){
            accumSumLookup[i] = accumSumLookup[i-1] + populationWeights[i].value;
        }
        
        //Reset the population iterator
        populationIter = population.begin();
        
        if( useElitism ){
            //The first child is simply a copy of the best parent
            populationIter->gene = parents[ populationSize-1 ].gene;
            populationIter++;
        }
        
        //This is the main evolve loop
        while( populationIter != population.end() ){
            
            //Randomly select the parents, individuals with higher weights will have a better chance of being selected
            mom = rand.getRandomNumberWeighted( populationWeights, accumSumLookup );
            dad = rand.getRandomNumberWeighted( populationWeights, accumSumLookup );
            
            //Generate the new individual using cross over
            crossOverPoint = rand.getRandomNumberInt(0, geneSize);
            for(i=0; i<geneSize; i++){
                if( i < crossOverPoint ) populationIter->gene[i] = parents[ mom ].gene[i];
                else populationIter->gene[i] = parents[ dad ].gene[i];
            }
            
            //Perform random mutation
            for(i=0; i<geneSize; i++){
                if( rand.getRandomNumberUniform(0.0,1.0) <= mutationRate ){
                    populationIter->gene[ i ] = rand.getRandomNumberUniform(0.0,1.0);
                }
            }
            
            populationIter++;
        }
        
        //Store the parents for the next iteration
        parents = population;
        
        return true;
    }
    
    /**
     This function evaluates the fitness of an individual, using the training data.  This function assumes that each row in the
     training data is an example, each column must therefore match the geneSize.  
     
     @param INDIVIDUAL &individual: a reference to the individual you want to compute the fitness for
     @param const MatrixDouble &trainingData: a reference to the training data that will be used to compute the individual's fitness
     @return returns the fitness of the individual
     */
    virtual double evaluateFitness( INDIVIDUAL &individual, const MatrixDouble &trainingData ){
        
        individual.fitness = 0;
        
        if( !initialized ) return 0;
        
        if( trainingData.getNumCols() != geneSize ) return 0;
        
        UINT M = trainingData.getNumRows();
        double error = 0;
        double minError = numeric_limits< double >::max();
        
        double target = 0;
        double estimate = 0;
        for(UINT i=0; i<M; i++){
            error = 0;
            //Compute the squared distance
            for(UINT j=0; j<geneSize; j++){
                error += ( trainingData[i][j] - individual.gene[j] ) * ( trainingData[i][j] - individual.gene[j] );
            }
            if( error < minError ) minError = error;
        }
        //Make sure the minError is not zero
        minError += 0.00001;
        minError /= double(geneSize);
        
        //Good individuals should have a high fitness
        individual.fitness = 1.0/(minError*minError);
        
        return individual.fitness;
    }

    virtual bool train(MatrixDouble &trainingData){
        
        if( !initialized ) return false;
        
        UINT currentIteration = 0;
        UINT bestIndex = 0;
        bool keepTraining = true;
        double lastBestFitness = 0;
        double bestFitness = 0;
        
        geneSize = trainingData.getNumCols();
        populationHistory.clear();
        fitnessHistory.clear();
        
        if( storeHistory ){
            populationHistory.reserve( maxIteration/storeRate );
            fitnessHistory.reserve( maxIteration/storeRate );
        }
        
        //Init the population
        initPopulation( populationSize, geneSize );
        
        //Compute the fitness of the initial population
        estimatePopulationFitness( trainingData, bestFitness, bestIndex );
        lastBestFitness = bestFitness;
        
        if( storeHistory ){
            populationHistory.push_back( population );
            fitnessHistory.push_back( IndexedDouble(0, bestFitness) );
        }
        
        //Start the main loop
        while( keepTraining ){
            
            //Perform the selection
            if( !evolvePopulation() ){
                return false;
            }
            
            //Compute population fitness
            if( !estimatePopulationFitness( trainingData, bestFitness, bestIndex ) ){
                return false;
            }
            
            double delta = fabs( bestFitness-lastBestFitness );
            lastBestFitness = bestFitness;
            
            cout << "Iteration: " << currentIteration << "\tBestFitness: " << bestFitness << "\tBestIndex: " << bestIndex << "\tDelta: " << delta << endl;
            
            if( ++currentIteration >= maxIteration ) keepTraining = false;
            
            if( delta <= minChange ) keepTraining = false;
            
            //Save the current population
            if( currentIteration % storeRate == 0 && storeHistory ){
                populationHistory.push_back( population );
                fitnessHistory.push_back( IndexedDouble(bestIndex, bestFitness) );
            }
        }
        
        return true;
    }
    
    UINT getPopulationSize(){
        return populationSize;
    }
    
    bool getInitialized(){
        return initialized;
    }
    
    vector< INDIVIDUAL > getPopulation(){
        return population;
    }
    
    bool setPopulationSize(UINT populationSize){
        this->populationSize = populationSize;
        return true;
    }
    
    bool setMaxIterations(UINT maxIteration){
        this->maxIteration = maxIteration;
        return true;
    }
    
    bool setStoreRate(UINT storeRate){
        this->storeRate = storeRate;
        return true;
    }
    
    bool setMutationRate(double mutationRate){
        this->mutationRate = mutationRate;
        return true;
    }
    
    bool setMinChange(double minChange){
        this->minChange = minChange;
        return true;
    }
    
    bool setPopulation( vector< INDIVIDUAL > &newPopulation ){
        
        if( newPopulation.size() == 0 ) return false;
        
        population = newPopulation;
        populationSize = (UINT)population.size();
        populationWeights.resize( populationSize );
        accumSumLookup.resize( populationSize );
        
        UINT i = 0;
        UINT index = 0;
        typename vector< INDIVIDUAL >::iterator populationIter = population.begin();
        vector< IndexedDouble >::iterator weightsIter = populationWeights.begin();
        vector< double >::iterator geneIter;
    
        while( populationIter != population.end() ){
            weightsIter->value = populationIter->fitness;
            weightsIter->index = index++;
            
            populationIter++;
            weightsIter++;
        }
        
        return true;
    }
    
public:
    UINT populationSize;
    UINT geneSize;
    UINT maxIteration;
    UINT storeRate;
    Random rand;
    double mutationRate;
    double minChange;
    bool initialized;
    bool useElitism;
    bool storeHistory;
    vector< INDIVIDUAL > population;
    vector< INDIVIDUAL > parents;
    vector< IndexedDouble > populationWeights;
    vector< vector< INDIVIDUAL > > populationHistory;
    vector< IndexedDouble > fitnessHistory;
    vector< double > accumSumLookup;
};
    
}

#endif //GRT_EVOLUTIONARY_ALGORITHM_HEADER
