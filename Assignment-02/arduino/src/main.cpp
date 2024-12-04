
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
#include "tasks/api/ComunicationTask.h"
//
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
  pPir->init(110);

  Task* pTempTask = new TempTask(machine);
  pTempTask->init(100);
  //
  Task* pComunicationTask = new ComunicationTask(machine);
  pComunicationTask->init(100);

  sched.addTask(pServoTask); //0
  sched.addTask(pLedTask); //1
  sched.addTask(pPir); //2
  sched.addTask(pTempTask); //3
  sched.addTask(pDetectorTask);  //4
  sched.addTask(pComunicationTask); //5


}

void loop(){
  sched.schedule();
}

