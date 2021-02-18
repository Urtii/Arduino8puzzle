#include "Queue.h"
#include "Stack.h"
#include "PuzzleState.h"
#include "BSTree.h"
#include "PuzzleTree.h"
#include "MemoryFree.h"

#define debug false
#define ANSWER 123456780

int incomingByte = 0;
unsigned long state;
unsigned int input_validation1 = 1, input_validation2 = 1;
bool WaitInput = false;
bool ReadComplete = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
#if(debug)
  Serial.print(freeMemory());
  Serial.println(" bytes of memory left.");
#endif
  //Ask user input once
  if (!WaitInput) {
    Serial.println("Please Enter Puzzle State:");
    //Serial.println(state);
    WaitInput = true;
    ReadComplete = false;
    state = 0;
  }
  else {
    while (incomingByte != -38) { //record input values untill "\n" value

      if ((Serial.available() > 0)) {
        // read the incoming byte:
        incomingByte = Serial.read() - 48;
        ReadComplete = true;
        //Serial.println(incomingByte);
        if (incomingByte >= 0)state = state * 10 + incomingByte;
        if (incomingByte > 0)input_validation1 *= incomingByte;   //this is equal to 8! for correct input
        input_validation2 *= incomingByte;                        //this is equal to 0 for correct input
      }
    }
    if (input_validation1 == 40320 && input_validation2 == 0 && state != ANSWER) {   //if true reset input parameters and start solving
      WaitInput = false;
      input_validation1 = 1;
      input_validation2 = 1;
      incomingByte = 0;
#if(debug)
      Serial.println("State is: ");
      Displaystate(state);
#endif
      Solve(state);
    }
    else {                                            //if false reset input parameters and ask again
      WaitInput = false;
      Serial.println("Wrong Input Type, Try Again");
      input_validation1 = 1;
      input_validation2 = 1;
      incomingByte = 0;
    }
  }
}

void Solve(unsigned long initstate) {

  //Find zero location
  int zero;
  if (initstate % 10 == 0) zero = 9;
  else if ((initstate / 10) % 10 == 0) zero = 8;
  else if ((initstate / 100) % 10 == 0) zero = 7;
  else if ((initstate / 1000) % 10 == 0) zero = 6;
  else if ((initstate / 10000) % 10 == 0) zero = 5;
  else if ((initstate / 100000) % 10 == 0) zero = 4;
  else if ((initstate / 1000000) % 10 == 0) zero = 3;
  else if ((initstate / 10000000) % 10 == 0) zero = 2;
  else if ((initstate / 100000000) % 10 == 0) zero = 1;
#if(debug)
  Serial.print("Zero location is: ");
  Serial.println(zero);
#endif

  //tool variables and objects
  Queue<PuzzleState*> PQue; //Queue for breath first algorithym

  PuzzleState* Root = new PuzzleState(initstate, zero, 9);
  PuzzleState* current;
  PuzzleState* child;
  unsigned long ChildId;

  //initial setup
  PQue.Qinsert(Root);
  BSTree BSTree(Root);
  PuzzleTree PTree(Root);

  while (1) {   //try untill answer is found
    current = PQue.Qdelete();
    if (current->GetID() == ANSWER) {     //if answer found print and break
      Serial.println("Result found");
      Result(current);
      Serial.println("");
      Serial.println("");
      //Serial.println(freeMemory());
      BSTree.BSTClean(Root);
      //Serial.println(freeMemory());
      PQue.ClearQueue();
      //Serial.println(freeMemory());
      break;
    }

    //If answer didn't found, generate child nodes
    if ((current->GetEmpty() == 2) || (current->GetEmpty() == 3) || (current->GetEmpty() == 5) ||
        (current->GetEmpty() == 6) || (current->GetEmpty() == 8) || (current->GetEmpty() == 9)) {

      ChildId = NewID(current->GetID(), current->GetEmpty(), 0);
      //Serial.print("Child ID is: ");
      //Serial.println(ChildId);

      child = PTree.GenerateChild(ChildId, (current->GetEmpty() - 1), 0, current);

#if(debug)
      Serial.println("Child is: ");
      Displaystate(child->GetID());
      Serial.println("Parent is: ");
      Displaystate(child->GetParent()->GetID());
#endif
      if (BSTree.BSTseach(child, Root)) {
        delete child;
        //Serial.println("Child deconstructed");
      }
      else {
        PQue.Qinsert(child);
#if(debug)
        Serial.println("Child added queue");
        Serial.println("");
#endif
      }
    }

    if ((current->GetEmpty() == 1) || (current->GetEmpty() == 2) || (current->GetEmpty() == 4) ||
        (current->GetEmpty() == 5) || (current->GetEmpty() == 7) || (current->GetEmpty() == 8)) {

      ChildId = NewID(current->GetID(), current->GetEmpty(), 1);
      //Serial.print("Child ID is: ");
      //Serial.println(ChildId);

      child = PTree.GenerateChild(ChildId, (current->GetEmpty() + 1), 1, current);

#if(debug)
      Serial.println("Child is: ");
      Displaystate(child->GetID());
      Serial.println("Parent is: ");
      Displaystate(child->GetParent()->GetID());
#endif
      if (BSTree.BSTseach(child, Root)) {
        delete child;
        //Serial.println("Child deconstructed");
      }
      else {
        PQue.Qinsert(child);
#if(debug)
        Serial.println("Child added queue");
        Serial.println("");
#endif
      }
    }

    if ((current->GetEmpty() == 4) || (current->GetEmpty() == 5) || (current->GetEmpty() == 6) ||
        (current->GetEmpty() == 7) || (current->GetEmpty() == 8) || (current->GetEmpty() == 9)) {

      ChildId = NewID(current->GetID(), current->GetEmpty(), 2);
      //Serial.print("Child ID is: ");
      //Serial.println(ChildId);

      child = PTree.GenerateChild(ChildId, (current->GetEmpty() - 3), 2, current);

#if(debug)
      Serial.println("Child is: ");
      Displaystate(child->GetID());
      Serial.println("Parent is: ");
      Displaystate(child->GetParent()->GetID());
#endif

      if (BSTree.BSTseach(child, Root)) {
        delete child;
        //Serial.println("Child deconstructed");
      }
      else {
        PQue.Qinsert(child);
#if(debug)
        Serial.println("Child added queue");
        Serial.println("");
#endif
      }
    }

    if ((current->GetEmpty() == 1) || (current->GetEmpty() == 2) || (current->GetEmpty() == 3) ||
        (current->GetEmpty() == 4) || (current->GetEmpty() == 5) || (current->GetEmpty() == 6)) {
      ChildId = NewID(current->GetID(), current->GetEmpty(), 3);
      //Serial.print("Child ID is: ");
      //Serial.println(ChildId);

      child = PTree.GenerateChild(ChildId, (current->GetEmpty() + 3), 3, current);

#if(debug)
      Serial.println("Child is: ");
      Displaystate(child->GetID());
      Serial.println("Parent is: ");
      Displaystate(child->GetParent()->GetID());
#endif
      if (BSTree.BSTseach(child, Root)) {
        delete child;
        //Serial.println("Child deconstructed");
      }
      else {
        PQue.Qinsert(child);
#if(debug)
        Serial.println("Child added queue");
        Serial.println("");
#endif
      }
    }
  }
}
                                                              //function to obtain child ID
unsigned long NewID(unsigned long id, int zero, int dir) {    //Parent ID, Parent Zero Location, Movement Direction
  zero = zero - 1;
  byte strng[9];
  for (int i = 8; i >= 0; i--) {
    strng[i] = id % 10;
    id /= 10;
  }
  if (dir == 0) {
    strng[zero] = strng[zero - 1];
    strng[zero - 1] = 0;

  }
  else if (dir == 1) {
    strng[zero] = strng[zero + 1];
    strng[zero + 1] = 0;

  }
  else if (dir == 2) {
    strng[zero] = strng[zero - 3];
    strng[zero - 3] = 0;

  }
  else if (dir == 3) {
    strng[zero] = strng[zero + 3];
    strng[zero + 3] = 0;

  }
  id = strng[0];
  for (int i = 1; i < 9; i++) {
    id = id * 10 + strng[i];
    //Serial.println(id);
  }
  return id;
}

void Result(PuzzleState* result) {            //function for printing result
  Stack<PuzzleState*> Rstack;
  do {                                        //first push to stack
    Rstack.Spush(result);
    result = result->GetParent();
  }
  while (result->GetParent() != NULL);

  Serial.println("Result is: ");
  Serial.println("");
  Displaystate(result->GetID());              //then print in correct order
  Serial.println("");
  while (!Rstack.SEmpty()) {
    result = Rstack.Spop();
    LastMoveDisplay(result->GetLastMove());
    Serial.println("");
    Displaystate(result->GetID());
    Serial.println("");
  }
}

void Displaystate(unsigned long id) {       //function to print states in matrix form
  unsigned long temp = id / 1000000;
  if (temp > 100) Serial.println(temp);
  else {
    Serial.print(0);
    Serial.println(temp);
  }
  id = id - temp * 1000000;
  temp = id / 1000;
  if (temp > 100) Serial.println(temp);
  else {
    Serial.print(0);
    Serial.println(temp);
  }
  temp = id - temp * 1000;
  if (temp > 100) Serial.println(temp);
  else {
    Serial.print(0);
    Serial.println(temp);
  }
}

void LastMoveDisplay(byte move_id) {                     //Function to display movement direction
  if (move_id == 0)Serial.println("Move 0 to Left");
  if (move_id == 1)Serial.println("Move 0 to Right");
  if (move_id == 2)Serial.println("Move 0 to Up");
  if (move_id == 3)Serial.println("Move 0 to Down");
}
