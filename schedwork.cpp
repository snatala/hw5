#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool validSched(const AvailabilityMatrix& available, const DailySchedule& sched, size_t day, Worker_T worker, size_t dailyNeed, size_t maxShifts)
{
    if(!available[day][worker]){
        return false; //check if worker is available on the current day
    }

    size_t shifts = 0;
    std::map<Worker_T, size_t> workerShifts;
    shifts = workerShifts[worker];

    if(shifts >= maxShifts){
        return false;
    } else {
        shifts++;
        workerShifts[worker] = shifts;
        return true;
    }
}

bool scheduleHelper(const AvailabilityMatrix& available, size_t dailyNeed, size_t day, size_t maxShifts, DailySchedule& sched, std::map<Worker_T, size_t> workerShifts)
{
    size_t numWorkers = available[0].size();
    size_t numDays = available.size();

    if(day == numDays){
        return true;
    }

    for(size_t worker = 0; worker < numWorkers; ++worker){
        if(workerShifts[worker] < maxShifts && validSched(available, sched, day, worker, dailyNeed, maxShifts)){
            sched[day].push_back(worker);
            workerShifts[worker] += 1;

            if(sched[day].size() == dailyNeed){
                if(scheduleHelper(available, dailyNeed, day+1, maxShifts, sched, workerShifts)){
                    return true;
                }
            } else {
                if (scheduleHelper(available, dailyNeed, day+1, maxShifts, sched, workerShifts)){
                    return true;
                }
            }

            sched[day].pop_back();
            workerShifts[worker] -= 1;
        }
    }

    return false;
}


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    if(avail.empty()){
        return false;
    }

    size_t numDays = avail.size();

    sched.clear();
    sched.resize(numDays);

    std::map<Worker_T, size_t> workerShifts;
    return scheduleHelper(avail, dailyNeed, 0, maxShifts, sched, workerShifts);
}

