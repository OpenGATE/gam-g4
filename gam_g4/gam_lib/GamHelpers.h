/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#ifndef GamHelpers_h
#define GamHelpers_h

#include <iostream>
#include <pybind11/stl.h>
#include <G4ThreeVector.hh>
//#include <fmt/core.h>
//#include <fmt/color.h>
#include "GamSourceManager.h"

namespace py = pybind11;

void Fatal(std::string s);

#define DD(a) std::cout << #a << " = [ " << a << " ]\n";

#define DDD(a) std::cout << "GAM [" << G4Threading::G4GetThreadId() << "] (" << __func__ << ") ==> " << #a << " = [ " << a << " ]\n";

int GetThreadIndex();

// Log verbose (with color and level)

template<typename S, typename... Args>
void Log(int level, const S &format_str, Args &&... args);

template<typename S, typename... Args>
void LogDebug(int level, const S &format_str, Args &&... args);

static int LogLevel_RUN = 20;
static int LogLevel_EVENT = 50;

#include "GamHelpers.txx"

#endif // GamHelpers_h
