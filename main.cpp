/* 
 * Copyright (C): None
 * Authors: Jimmy Baraglia
 * Public License for more details
*/

#include "src/BNet.h"
#include "src/BNode.h"
#include "src/BEdge.h"
#include "src/BPVector.h"

int main(int argc, char * argv[]) {
      
    BNet *BNetwork = new BNet(argc, argv);
    
    BPVector parentsVector; //This variable will be used to set conditionnal probabilities 
    
    //Create and add nodes to the bayesian network
    BNode *A = new BNode("A", 2); BNetwork->addNode(A);
    BNode *B = new BNode("B", 2); BNetwork->addNode(B);
    BNode *C = new BNode("C", 2); BNetwork->addNode(C);
    BNode *D = new BNode("D", 2); BNetwork->addNode(D);
    
    //Test that a node cannot be added twice:
    cout<<"Test 1 starts: Number of nodes is "<<BNetwork->getNumberOfNodes()<<endl;
    BNetwork->addNode(A);
    cout<<"Test 1 ends:   Number of nodes is "<<BNetwork->getNumberOfNodes()<<endl<<endl;
    
    
    //Create and add edges to the bayesian network
    BEdge *AB = new BEdge(A, B); BNetwork->addEdge(AB);
    BEdge *BC = new BEdge(B, C); BNetwork->addEdge(BC);
    BEdge *BD = new BEdge(B, D); BNetwork->addEdge(BD);
    
    //Test that an edge cannot be added twice:
    cout<<"Test 2 starts: Number of edges is "<<BNetwork->getNumberOfEdges()<<endl;
    BNetwork->addEdge(AB);
    cout<<"Test 2 ends: Number of edges is "<<BNetwork->getNumberOfEdges()<<endl<<endl;
      
    //Test adding parents to the BPVector    
    parentsVector.addParent(A, 0);
    cout<<"Test 3.1: The state of A is "<<parentsVector.getStateOf(A)<<endl;
    
    parentsVector.set(A, 1);
    cout<<"Test 3.2: The state of A is "<<parentsVector.getStateOf(A)<<endl;
    
    parentsVector.set(B, 0);
    cout<<"Test 3.2: The state of B is "<<parentsVector.getStateOf(B)<<endl;
    
    parentsVector.clear();
    cout<<"Test 3.3.1: The state of A is "<<parentsVector.getStateOf(A)<<endl;
    cout<<"Test 3.3.2: The state of B is "<<parentsVector.getStateOf(B)<<endl<<endl;

    //Test some accessor methods
    cout<<"Test 4.1: A has "<<BNetwork->getNumberOfParentsOf(A)<<" parents"<<endl;
    cout<<"Test 4.2: D has "<<BNetwork->getNumberOfParentsOf(D)<<" parents"<<endl;
    cout<<"Test 4.3: A is the node number "<<BNetwork->getIdOfNode(A)<<endl;
    cout<<"Test 4.4: D is the node number "<<BNetwork->getIdOfNode(D)<<endl<<endl;
    
    BNetwork->setNodeProbability(A, &parentsVector, 0, 0.2);
    BNetwork->setNodeProbability(A, &parentsVector, 1, 0.8);
    
    parentsVector.clear();
    parentsVector.set(A, 0);
    BNetwork->setNodeProbability(B, &parentsVector, 0, 0.1);
    parentsVector.set(A, 1);
    BNetwork->setNodeProbability(B, &parentsVector, 0, 0.3);
    parentsVector.set(A, 0);
    BNetwork->setNodeProbability(B, &parentsVector, 1, 0.9);
    parentsVector.set(A, 1);
    BNetwork->setNodeProbability(B, &parentsVector, 1, 0.7);
    
    parentsVector.clear();
    parentsVector.set(B, 0);
    BNetwork->setNodeProbability(C, &parentsVector, 0, 0.7);
    parentsVector.set(B, 1);
    BNetwork->setNodeProbability(C, &parentsVector, 0, 0.3);
    parentsVector.set(B, 0);
    BNetwork->setNodeProbability(C, &parentsVector, 1, 0.3);
    parentsVector.set(B, 1);
    BNetwork->setNodeProbability(C, &parentsVector, 1, 0.7);
    
    parentsVector.clear();
    parentsVector.set(B, 0);
    BNetwork->setNodeProbability(D, &parentsVector, 0, 0.6);
    parentsVector.set(B, 1);
    BNetwork->setNodeProbability(D, &parentsVector, 0, 0);
    parentsVector.set(B, 0);
    BNetwork->setNodeProbability(D, &parentsVector, 1, 0.4);
    parentsVector.set(B, 1);
    BNetwork->setNodeProbability(D, &parentsVector, 1, 1);
    
    parentsVector.set(B, 0);
    cout<<"Test 5.1: P(D=0|B=0) = "<<BNetwork->getNodeProbability(D, &parentsVector, 0)<<endl;
    parentsVector.set(B, 1);
    cout<<"Test 5.4: P(D=0|B=1) = "<<BNetwork->getNodeProbability(D, &parentsVector, 0)<<endl;
    
    parentsVector.clear();
    cout<<"Test 5.5: P(A=0) = "<<BNetwork->getNodeProbability(A, &parentsVector, 0)<<endl;
    cout<<"Test 5.6: P(A=1) = "<<BNetwork->getNodeProbability(A, &parentsVector, 1)<<endl;
    
    
    cout<<"Test 6.1: \n"<<BNetwork->toString()<<endl;
    
    BNetwork->run();
    
    cout<<"Test 6.2: \n"<<BNetwork->toString()<<endl;
    
    BNetwork->newEvidence(B, 1);
    BNetwork->run();
    
    cout<<"Test 7: Evidence B = 1\n"<<BNetwork->toString()<<endl;
    
    return 0;
}

