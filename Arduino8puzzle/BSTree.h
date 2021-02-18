#ifndef BSTree_h
#define BSTree_h

//#include "Arduino.h"
#include "PuzzleState.h"

#define debug false

class BSTree {
  public:
    BSTree(PuzzleState *root) {
      Root = root;
    }

    bool BSTseach(PuzzleState* child, PuzzleState* node) {
      //Serial.println(node->GetID());
      if  (child->GetID() == node->GetID()) return true;
      else if (child->GetID() < node->GetID()) {
#if(debug)
        Serial.println("Child ID is smaller");
#endif
        if (node->GetBSTleftchild() == NULL)node->BSTleftchild = child;
        else return BSTseach(child, node->BSTleftchild);
      }
      else if (child->GetID() > node->GetID()) {
#if(debug)
        Serial.println("Child ID is bigger");
#endif
        if (node->GetBSTrightchild() == NULL)node->BSTrightchild = child;
        else return BSTseach(child, node->BSTrightchild);
      }
    }
    
    void BSTClean(PuzzleState *node) {
      if (node == NULL) return;
      BSTClean(node->GetBSTleftchild());
      BSTClean(node->GetBSTrightchild());
      delete node;
      }
/*
    void BSTreverse(PuzzleState *node) {
      //Serial.println(node->GetID());
      if (node->GetBSTleftchild() != NULL)BSTreverse(node->GetBSTleftchild());
      //else Serial.println("Left is Empty");
      if (node->GetBSTrightchild() != NULL)BSTreverse(node->GetBSTrightchild());
      //else Serial.println("Right is Empty");
    }
*/
  private:
    PuzzleState* Root;
};

#endif
