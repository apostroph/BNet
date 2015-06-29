/* 
 * Copyright (C): None
 * Authors: Jimmy Baraglia
 * Public License for more details
*/

#ifndef _BNET_H_
#define _BNET_H_

#include <string>
#include <vector>

#include <iostream>
#include <iomanip>

#include <eigen3/Eigen/Dense>

#include <unordered_map> //Only with C++ 11 or above


#include "BEdge.h"
#include "BNode.h"
#include "BPVector.h"

using namespace std;
using namespace Eigen;


class BNet{

public:
    /** 
     * document your methods too.
     */
    BNet(int argc, char * argv[]);
    
     /*
      * Look at the current state of each node and calculate the praboality of each node to be active
      */
     bool run();
    
    /*addNode(BNode *node)
     * Add a new node to the bayesian network.
     * returns 1 is successful
     * returns 0 is a node was already added with the same name
     * retunrs -1 if unknown error occured
     */
    int addNode(BNode* i_node);
    
    /*newEvidence(BNode* i_node, int i_state)
     * Add a state to a node
     * returns 1 is successful
     * retunrs -1 if unknown error occured
     */
    int newEvidence(BNode* i_node, int i_state);
    
    /*addEdge(BEdge *edge)
     * Add a new edge to the bayesian network.
     * returns 1 is successful
     * returns 0 is a edge was already added
     * retunrs -1 if unknown error occured
     * !! Changing the number of edges will results in changing the node's probability matrix size !!
     */
    int addEdge(BEdge* i_edge);
    
    
    /*setNodeProbability(BNode* i_node, BPVector i_parentsStates, int i_inputNodeState, int i_probability)
     * set the probability for a node to be a given state knowing the state of his parents
     * returns 1 is successful
     * retunrs -1 if unknown error occured
     * !! set nodes' probabilities everytime you add or remove an edge or node
     */
    int setNodeProbability(BNode* i_node, BPVector* i_parentsStates, int i_inputNodeState, float i_probability);
    
    ~BNet();

    //Get methods
    int getNumberOfNodes();
    int getNumberOfEdges();
    
    int getIdOfNode(BNode* i_node);
    int getNumberOfParentsOf(BNode* i_node);
    BNode* getParentNb(BNode* i_node, int parentIndex);
    
    float getNodeProbability(BNode* i_node, BPVector* i_parentsStates, int i_inputNodeState);
    
    string toString();

private:
    std::vector<BNode*> listOfNodes;
    std::vector<BEdge*> listOfEdges;
    
    MatrixXf* nodesProbability;
    
    std::vector<MatrixXf*> listOfNodeProbabilities;
    std::vector<VectorXd*> listOfNodeInputEdges;
        
    void setProbaNode(BNode* i_node);
    
    /*updateNodeProbabilityMatrices
     * Update the size of the matrice coreresponding to i_nodeNumber when a node or and edge is added/removed
     */
    void updateNodeProbabilityMatrice(int i_nodeNumber, int i_newEdgeFromNodeID);
    void initProbaMatrix();
    inline int getCol(BNode* i_node, BPVector* i_parentsStates);
};


#endif // _BNET_H_

//----- end-of-file --- ( next line intentionally left blank ) ------------------

