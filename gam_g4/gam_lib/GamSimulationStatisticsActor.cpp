/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */


#include <chrono>
#include <vector>
#include "G4AccumulableManager.hh"
#include "GamSimulationStatisticsActor.h"
#include "GamHelpers.h"

GamSimulationStatisticsActor::GamSimulationStatisticsActor(std::string type_name)
        : GamVActor(type_name),
          fRunCount("Run", 0),
          fEventCount("Event", 0),
          fTrackCount("Track", 0),
          fStepCount("Step", 0) {
    actions.push_back("BeginOfRunAction");
    actions.push_back("EndOfRunAction");
    actions.push_back("PreUserTrackingAction");
    actions.push_back("ProcessHits");
}

GamSimulationStatisticsActor::~GamSimulationStatisticsActor() = default;

// Called when the simulation start
void GamSimulationStatisticsActor::StartSimulationAction() {
    fStartTime = std::chrono::steady_clock::now();
    fRunCount.Reset();
    fEventCount.Reset();
    fTrackCount.Reset();
    fStepCount.Reset();
    G4AccumulableManager *accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->RegisterAccumulable(fRunCount);
    accumulableManager->RegisterAccumulable(fEventCount);
    accumulableManager->RegisterAccumulable(fTrackCount);
    accumulableManager->RegisterAccumulable(fStepCount);
}

// Called when the simulation end
void GamSimulationStatisticsActor::EndSimulationAction() {
    fStopTime = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(fStopTime - fStartTime).count();
    duration = duration * CLHEP::microsecond;
}

// Called every time a Run starts
void GamSimulationStatisticsActor::BeginOfRunAction(const G4Run * /*run*/) {
    // It is better to start time measurement at begin of (first) run,
    // because there is some time between StartSimulation and BeginOfRun
    // (it is only significant for short simulation)
    //start_time = std::chrono::steady_clock::now();
}

// Called every time a Run starts
void GamSimulationStatisticsActor::EndOfRunAction(const G4Run *run) {
    fRunCount++;
    fEventCount += run->GetNumberOfEvent();
}

// Called every time a Track starts
void GamSimulationStatisticsActor::PreUserTrackingAction(const G4Track * /*track*/) {
    fTrackCount++;
}

// Called every time a batch of step must be processed
void GamSimulationStatisticsActor::SteppingAction(G4Step *, G4TouchableHistory *) {
    fStepCount++;
}
