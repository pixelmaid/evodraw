/*
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
 */

#include "HierarchicalClustering.h"

namespace GRT{

HierarchicalClustering::HierarchicalClustering(){
    M = N = 0;
    trained = false;
}

HierarchicalClustering::~HierarchicalClustering(){

}

bool HierarchicalClustering::train(LabelledClassificationData &trainingData){
	
	if( trainingData.getNumSamples() == 0 ){
		return false;
	}

    //Convert the labelled training data to a training matrix
	M = trainingData.getNumSamples();
    N = trainingData.getNumDimensions();

    MatrixDouble data(M,N);
    for(UINT i=0; i<M; i++){
        for(UINT j=0; j<N; j++){
            data[i][j] = trainingData[i][j];
        }
    }

	return train(data);
}

bool HierarchicalClustering::train(UnlabelledClassificationData &trainingData){
    
    if( trainingData.getNumSamples() == 0 ){
		return false;
	}

    //Convert the training data into one matrix
	M = trainingData.getNumSamples();
    N = trainingData.getNumDimensions();

    MatrixDouble data(M,N);
    for(UINT i=0; i<M; i++){
        for(UINT j=0; j<N; j++){
            data[i][j] = trainingData[i][j];
        }
    }
	
	return train(data);
}

bool HierarchicalClustering::train(MatrixDouble &data){
	
	trained = false;
    clusters.clear();
    distanceMatrix.clear();
	M = data.getNumRows();
	N = data.getNumCols();
    
	if( data.getNumRows() == 0 || data.getNumCols() == 0 ){
		return false;
	} 
    
    //Build the distance matrix
    distanceMatrix.resize(M,M);

    //Build the distance matrix
    for(UINT i=0; i<M; i++){
        for(UINT j=0; j<M; j++){
            if( i== j ) distanceMatrix[i][j] = numeric_limits<double>::max();
            else{
                distanceMatrix[i][j] = squaredEuclideanDistance(data[i], data[j]);
            }
        }
    }

    //Build the initial clusters, at the start each sample gets its own cluster
    vector< ClusterInfo > clusterData(M);
    for(UINT i=0; i<M; i++){
        clusterData[i].uniqueClusterID = i;
        clusterData[i].addSampleToCluster(i);
    }
    
    //Create the first cluster level, each sample is it's own cluster
    UINT level = 0;
    ClusterLevel newLevel;
    newLevel.level = level;
    for(UINT i=0; i<M; i++){
        newLevel.clusters.push_back( clusterData[i] );
    }
    clusters.push_back( newLevel );
    
    //Move to level 1 and start the search
    level++;
    bool keepClustering = true;
    
    cout << "M: " << M << endl;
    
    while( keepClustering ){
        
        cout << "Level: " << level << "\tClusterDataSize: " << clusterData.size() << endl;
        
        //Find the closest two clusters within the cluster data
        double minDist = numeric_limits<double>::max();
        vector< vector< UINT > > clusterPairs;
        UINT K = (UINT)clusterData.size();
        for(UINT i=0; i<K; i++){
            for(UINT j=0; j<K; j++){
                if( i != j ){
                    double dist = computeClusterDistance( clusterData[i], clusterData[j]  );
                    if( dist == minDist ){
                        vector< UINT > clusterPair(2);
                        clusterPair[0] = i;
                        clusterPair[1] = j;
                        clusterPairs.push_back( clusterPair );
                    }else {
                        if( dist < minDist ){
                            minDist = dist;
                            clusterPairs.clear();
                            vector< UINT > clusterPair(2);
                            clusterPair[0] = i;
                            clusterPair[1] = j;
                            clusterPairs.push_back( clusterPair );
                        }
                    }
                }
            }
        }
        
        if( minDist == numeric_limits<double>::max() ){
            keepClustering = false;
            cout << "WARNING: Failed to find any cluster at level: " << level << endl;
        }else{
        
            //Merge the two closest clusters together and create a new level
            ClusterLevel newLevel;
            newLevel.level = level;
            
            //This level will have one cluster in it
            ClusterInfo newCluster;
            newCluster.uniqueClusterID = M+level;
            
            for(UINT k=0; k<clusterPairs.size(); k++){
                //Add the new level and cluster data to the main cluster buffer
                newLevel.clusters.push_back( newCluster );
                clusters.push_back( newLevel );
                
                //Grab a reference to the cluster buffer so we don't have to copy things too much
                ClusterInfo &clusterRef = clusters.back().clusters[k];
                
                //Add all the samples in the first cluster to the new cluster
                for(UINT i=0; i<clusterData[ clusterPairs[k][0] ].getNumSamplesInCluster(); i++){
                    clusterRef.addSampleToCluster( clusterData[ clusterPairs[k][0] ][ i ] );
                }
                
                //Add all the samples in the second cluster to the new cluster
                for(UINT i=0; i<clusterData[ clusterPairs[k][1] ].getNumSamplesInCluster(); i++){
                    clusterRef.addSampleToCluster( clusterData[ clusterPairs[k][1] ][ i ] );
                }
                
                //Compute the cluster variance
                clusters.back().clusters[k].clusterVariance = computeClusterVariance( clusterRef, data );
                
                UINT idA = clusterData[ clusterPairs[k][0] ].getUniqueClusterID();
                UINT idB = clusterData[ clusterPairs[k][1] ].getUniqueClusterID();
                UINT numRemoved = 0;
                vector< ClusterInfo >::iterator iter = clusterData.begin();
                while( iter != clusterData.end() ){
                    if( iter->getUniqueClusterID() == idA || iter->getUniqueClusterID() == idB ){
                        iter = clusterData.erase( iter );
                        if( ++numRemoved >= 2 ) break;
                    }else iter++;
                }
                
                //Add the merged cluster to the clusterData
                clusterData.push_back( clusterRef );

            }
            
            //Update the level
            level++;
            
        }
        
        //Check to see if we should stop clustering
        if( level >= M ){
            keepClustering = false;
        }
        
        if( clusterData.size() == 0 ){
            keepClustering = false;
        }
        
    }

	return true;
}
    
bool HierarchicalClustering::printModel(){
    
    UINT K = (UINT)clusters.size();
    
    cout << "Hierarchical Clustering Model\n\n";
    for(UINT k=0; k<K; k++){
        UINT numClusters = clusters[k].getNumClusters();
        UINT numSamples = 0;
        for(UINT i=0; i<numClusters; i++){
            numSamples += clusters[k][i].getNumSamplesInCluster();
            
        }
        
        cout << "Level: " << clusters[k].level << "\tNumClusters: " << numClusters << "\tNumSamples: " << numSamples << endl;
        for(UINT i=0; i<numClusters; i++){
            cout << "ClusterVariance: " << clusters[k][i].clusterVariance << endl;
            cout << "Indexs: ";
            UINT numSamplesInCluster = clusters[k][i].getNumSamplesInCluster();
            for(UINT j=0; j<numSamplesInCluster; j++){
                cout << clusters[k][i][j] << "\t";
            }
            cout << endl;
        }
    }
    
    return true;
}
    
double HierarchicalClustering::squaredEuclideanDistance(const double *a,const double *b){
    double dist = 0;
    for(UINT i=0; i<N; i++){
        dist += SQR( a[i] - b[i] );
    }
    return dist;
}
    
double HierarchicalClustering::computeClusterDistance( ClusterInfo &clusterA, ClusterInfo &clusterB ){
    
    double minDist = numeric_limits<double>::max();
    
    for(UINT i=0; i<clusterA.getNumSamplesInCluster(); i++){
        for(UINT j=0; j<clusterB.getNumSamplesInCluster(); j++){
            if( distanceMatrix[ clusterA[i] ][ clusterB[j] ] < minDist ){
                minDist = distanceMatrix[ clusterA[i] ][ clusterB[j] ];
            }
        }
    }
    
    return minDist;
}
    
double HierarchicalClustering::computeClusterVariance( ClusterInfo &cluster, MatrixDouble &data ){
    
    VectorDouble mean(N,0);
    VectorDouble std(N,0);
    
    //Compute the mean
    UINT numSamples = cluster.getNumSamplesInCluster();
    for(UINT j=0; j<N; j++){
        for(UINT i=0; i<numSamples; i++){
            mean[j] += data[ cluster[i] ][j];
        }
        mean[j] /= double( numSamples );
    }
    
    //Compute the std dev
    for(UINT j=0; j<N; j++){
        for(UINT i=0; i<numSamples; i++){
            std[j] += SQR( data[ cluster[i] ][j] - mean[j] );
        }
        std[j] = sqrt( std[j] / double( numSamples-1 ) );
    }
    
    double variance = 0;
    for(UINT j=0; j<N; j++){
        variance += std[j];
    }
    return variance/N;
}

}//End of namespace GRT
