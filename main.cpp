#include <iostream>
#include <stdlib.h>

using namespace std;

const int MAX_CAPACITY = 10;
const int GROUND_FLOOR = 1;
const int TOP_FLOOR = 20;
const int TIMEOUT = 5;

class Elevator {
    char bank;
    int id;
    map<int,int> floorsIn; //floors where picking up
    map<int,int> floorsOut; //floors where dropping off
    int people = 0; //total number people queued
    int currFloor = 1;

    public:
        Elevator(char paramBank = 'A', int paramID = 1) {
            bank = paramBank;
            id = paramID;
        };

        void queueIn(int floorNo) { //queue pick ups
            if (floorNo > TOP_FLOOR || floorNo < GROUND_FLOOR) {
                throw "Invalid floor number.\n";
            }
            if (floorsIn.find(floorNo) != floorsIn.end()){ //if floor already queued
                floorsIn[floorNo]++;
            }
            else {
                floorsIn[floorNo] = 1;
            }
            people++;
        }

        void queueOut(int floorNo) { //queue drop offs
            if (floorNo > TOP_FLOOR || floorNo < GROUND_FLOOR) {
                throw "Invalid floor number.\n";
            }
            if (floorsOut.find(floorNo) != floorsOut.end()){ //if floor already queued
                floorsOut[floorNo]++;
            }
            else {
                floorsOut[floorNo] = 1;
            }
        }

        void pickUp(int floorNo) { //pick up people
            if (floorNo > TOP_FLOOR || floorsIn.find(floorNo) == floorsIn.end()) {
                throw "Invalid floor number.\n";
            }
            floorsIn.erase(floorNo);
        }

        void dropOff(int floorNo) { //drop off people
            if (floorNo > TOP_FLOOR || floorsOut.find(floorNo) == floorsOut.end()) {
                throw "Invalid floor number.\n";
            }
            people -= floorsOut[floorNo];
            floorsOut.erase(floorNo);
        }

        void goUp() { //travel up
            int waitTime = 0;
            //while (true) {
                if (people == MAX_CAPACITY || waitTime >= TIMEOUT) { //if cap reached or waited enough time
                    for (currFloor; currFloor <= TOP_FLOOR; currFloor++) { //go to each floor
                        if (floorsIn.find(currFloor) != floorsIn.end()) { //pick up if queued
                            pickUp(currFloor);
                        }
                        if (floorsOut.find(currFloor) != floorsOut.end()) { //drop off if queued
                            dropOff(currFloor);
                        }
                        wait(1);
                    }
                    waitTime = 0; //reset wait time
                }
                else {
                    if (people > 0) { //if elevator not empty, wait some time
                        waitTime++;
                    }
                    wait(1);
                }
            }
        }

        void goDown() { //travel down
            int waitTime = 0;
            //while (true) {
                if (people == MAX_CAPACITY || waitTime >= TIMEOUT) { //if cap reached or waited enough time
                    for (currFloor; currFloor <= GROUND_FLOOR; currFloor--) { //go to each floor
                        if (floorsIn.find(currFloor) != floorsIn.end()) { //pick up if queued
                            pickUp(currFloor);
                        }
                        if (floorsOut.find(currFloor) != floorsOut.end()) { //drop off if queued
                            dropOff(currFloor);
                        }
                        wait(1);
                    }
                    waitTime = 0; //reset wait time
                }
                else {
                    if (people > 0) { //if elevator not empty, wait some time
                        waitTime++;
                    }
                    wait(1);
                }
            }
        }
}

int main() {
    return 0;
}
