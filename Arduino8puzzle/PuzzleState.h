#ifndef Puzzlstate_h
#define Puzzlstate_h

#include "Arduino.h"

#define debug false

class PuzzleState {

    friend class BSTree;
    friend class PuzzleTree;

  private:
    unsigned long StateID;
    byte EmptyPosition;
    byte LastMovement; //1->Left, 2->Right, 3->Up, 4->Down, 9->root

    PuzzleState *BSTleftchild;
    PuzzleState *BSTrightchild;

    PuzzleState *PuzzleParent;

  public:
    //constructor
    PuzzleState(unsigned long stateid, byte emptyposition, byte lastmovement) {
      this->StateID = stateid;
      this->EmptyPosition = emptyposition;
      this->LastMovement = lastmovement;
      this->PuzzleParent = NULL;
      BSTleftchild = BSTrightchild = NULL;
#if(debug)
      Serial.println("New Child Generated");
      Serial.println("");
#endif
    }
/*
    ~PuzzleState() {
#if(debug)
      Serial.println("Child deconstructed");
      Serial.println("");
#endif
    }
*/
    //variable functions
    unsigned long GetID() {
      return StateID;
    }
    byte GetEmpty() {
      return EmptyPosition;
    }
    byte GetLastMove() {
      return LastMovement;
    }

    //Puzzle functions
    PuzzleState* GetParent() {
      return PuzzleParent;
    }

    //BST functions
    PuzzleState* GetBSTleftchild(void) {
      return BSTleftchild;
    }
    PuzzleState* GetBSTrightchild(void) {
      return BSTrightchild;
    }
};
#endif
