#ifndef PuzzlTree_h
#define PuzzlTree_h

#include "PuzzleState.h"

#define debug false

class PuzzleTree {

  public:
    PuzzleTree(PuzzleState* root) {
      Root = root;
    }

    PuzzleState* GenerateChild(unsigned long stateid, byte emptyposition, byte lastmovement, PuzzleState* puzzleparent) {
      PuzzleState* new_child = new PuzzleState(stateid, emptyposition, lastmovement);
      new_child->PuzzleParent = puzzleparent;

      return new_child;

    }




  private:
    PuzzleState* Root;






};










#endif
