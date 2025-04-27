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
bool validSched(const AvailabilityMatrix& available, size_t day, Worker_T worker, const std::map<Worker_T, size_t>& workerShifts, size_t maxShifts)
{
    if(!available[day][worker]){
        return false; //check if worker is available on the current day
    }

    auto it = workerShifts.find(worker);
    size_t shifts = (it != workerShifts.end()) ? it->second : 0;

    return shifts < maxShifts;

    // size_t shifts = 0;
    // std::map<Worker_T, size_t> workerShifts;
    // shifts = workerShifts[worker];

    // if(shifts >= maxShifts){
    //     return false;
    // } else {
    //     shifts++;
    //     workerShifts[worker] = shifts;
    //     return true;
    // }
}

bool scheduleHelper(const AvailabilityMatrix& available, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, std::map<Worker_T, size_t>& workerShifts, size_t day, size_t workerSlot)
{
    size_t numWorkers = available[0].size();
    size_t numDays = available.size();

    if(day == numDays){
        return true;
    }

    if(workerSlot == dailyNeed){
      return scheduleHelper(available, dailyNeed, maxShifts, sched, workerShifts, day+1, 0);
    }

    for(size_t worker = 0; worker < numWorkers; ++worker){
      if(std::find(sched[day].begin(), sched[day].end(), worker) != sched[day].end()){
        continue;
      }

      if(validSched(available, day, worker, workerShifts, maxShifts)){
        sched[day].push_back(worker);
        workerShifts[worker]++;

        if(scheduleHelper(available,dailyNeed,maxShifts,sched,workerShifts,day,workerSlot+1)){
          return true;
        }

        sched[day].pop_back();
        workerShifts[worker]--;
      }
    }
    // for(size_t worker = 0; worker < numWorkers; ++worker){
    //     if(workerShifts[worker] < maxShifts && validSched(available, sched, day, worker, dailyNeed, maxShifts)){
    //         sched[day].push_back(worker);
    //         workerShifts[worker] += 1;

    //         if(sched[day].size() == dailyNeed){
    //             if(scheduleHelper(available, dailyNeed, day+1, maxShifts, sched, workerShifts)){
    //                 return true;
    //             }
    //         } else {
    //             if (scheduleHelper(available, dailyNeed, day+1, maxShifts, sched, workerShifts)){
    //                 return true;
    //             }
    //         }

    //         sched[day].pop_back();
    //         workerShifts[worker] -= 1;
    //     }
    // }

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
    if(avail.empty()){
      return false;
    }

    size_t numDays = avail.size();

    sched.clear();
    sched.resize(numDays);

    std::map<Worker_T,size_t> workerShifts;
    return scheduleHelper(avail,dailyNeed,maxShifts,sched,workerShifts,0,0);

    // if(avail.size() == 0U){
    //     return false;
    // }
    // sched.clear();
    // // Add your code below

    // if(avail.empty()){
    //     return false;
    // }

    // size_t numDays = avail.size();

    // sched.clear();
    // sched.resize(numDays);

    // std::map<Worker_T, size_t> workerShifts;
    // return scheduleHelper(avail, dailyNeed, 0, maxShifts, sched, workerShifts);
}

