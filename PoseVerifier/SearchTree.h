#ifndef SEARCHTREE_H
#define SEARCHTREE_H

#include<Arduino.h>

//PLEASE EDIT HERE BEFORE EDITING DATA
#define Rows 1            // # of Poses
#define Columns 8         // # of Float values for each Pose
#define Error 1           // Acceptable distance from registered value

class SearchTree
{
  private:
    //Remember: 1 Line = 1 pose = 48 bytes = 4 bytes from 1 float * 3 parameters * 4 Accelerometers, we only have 25,656 remaining bytes
    const float DATA[Rows][Columns] = {
      {24.06, 64.22, 34.56, 5.56, 6.58, 10.6, 0.02, 6.58} //Sample Pose Data
    };
  public:
    SearchTree();
    int search(float value[Columns]);
};

#endif
