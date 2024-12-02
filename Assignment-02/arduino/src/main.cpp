
#include <Arduino.h>
#include "set-up.h"
#include "core/Scheduler.h"
#include "core/MsgService.h"
#include "core/Logger.h"

#include "SWDSystem.h"

#include "tasks/api/DetectorTask.h"
#include "tasks/api/ServoTask.h"
#include "tasks/api/LedTask.h"
#include "tasks/api/PirTask.h"
#include "tasks/api/TempTask.h"

Scheduler sched;

SWDSystem* machine;

void setup(){
  MsgService.init();
  sched.init(100);

  machine = new SWDSystem();
  machine->init();

  Task* pDetectorTask = new DetectorTask(machine);
  pDetectorTask->init(100);

  Task* pServoTask = new ServoTask(machine);
  pServoTask->init(200);

  Task* pLedTask = new LedTask(machine);
  pLedTask->init(100);

  Task* pPir = new PirTask(machine);
  pPir->init(100);

  Task* pTempTask = new TempTask(machine);
  pTempTask->init(100);
  //

  sched.addTask(pServoTask);
//  sched.addTask(pLedTask);
  sched.addTask(pPir);


}

void loop(){
  sched.schedule();
}
