/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#ifndef GamBranches_h
#define GamBranches_h

#include <pybind11/stl.h>
#include "G4GenericAnalysisManager.hh"
#include "G4Cache.hh"
#include "GamVActor.h"
#include "GamHelpers.h"

namespace py = pybind11;

class GamBranches {
public:

    // pre declare the structure
    struct BranchFillStepStruct;

    // function that will fill data during a step
    typedef std::function<void(G4GenericAnalysisManager *,
                               BranchFillStepStruct &,
                               G4Step *,
                               G4TouchableHistory *)> StepFillFunction;

    typedef struct BranchFillStepStruct {
        std::string name;
        char type;
        int i;
        StepFillFunction fill;
        bool enabled = false;
    } BranchFillStepStruct;

    static void BuildAllBranches();

    static void AddFillStep(std::string name, char type, StepFillFunction f);

    static void GetSelectedBranches(const std::vector<std::string> &names,
                                    G4GenericAnalysisManager *analysisManager,
                                    std::vector<BranchFillStepStruct> &selectedBranches);

    static std::vector<BranchFillStepStruct> fAllBranches;
};

#define STEP_FILL_FUNCTION [=](G4GenericAnalysisManager *am, BranchFillStepStruct &e, G4Step *step, G4TouchableHistory * )

// Same than previous one, only to avoid warning with the 'step'
// argument when not used
#define STEP_FILL_FUNCTION2 [=](G4GenericAnalysisManager *am, BranchFillStepStruct &e, G4Step *, G4TouchableHistory * )

#endif // GamBranches_h