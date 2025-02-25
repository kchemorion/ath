// -----------------------------------------------------------------------------
//
// Copyright (C) 2021 CERN & University of Surrey for the benefit of the
// BioDynaMo collaboration. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
//
// See the LICENSE file distributed with this work for details.
// See the NOTICE file distributed with this work for additional information
// regarding copyright ownership.
//
// -----------------------------------------------------------------------------

//This file defines the agents in the atherosclerosis simulation

#ifndef BDM_AGENTS_H_
#define BDM_AGENTS_H_

#include "biodynamo.h"
#include "core/agent/cell.h"



namespace bdm {

// Define the endothelial cell
class EndothelialCell : public Cell {
  BDM_AGENT_HEADER(EndothelialCell, Cell, 1);

 public:
  EndothelialCell() {}
  explicit EndothelialCell(const Real3& position) : Base(position) {}
  virtual ~EndothelialCell() {}
  int cell_color_;
  void SetCellColor(int cell_color) { cell_color_ = cell_color; }
};

// Define the vascular smooth muscle cell

class SmoothMuscleCell : public Cell {
  BDM_AGENT_HEADER(SmoothMuscleCell, Cell, 1);

 public:
  int cell_color_;
  bool elastin_is_degraded;
  //active, switch, lipid counter
  
  SmoothMuscleCell() {}
  explicit SmoothMuscleCell(const Real3& position) : Base(position) {}
  virtual ~SmoothMuscleCell() {}
  
  void SetCellColor(int cell_color) { cell_color_ = cell_color; }
};


// Define the monocyte
class Monocyte : public Cell {
  BDM_AGENT_HEADER(Monocyte, Cell, 1);

 public:
  Monocyte() {}
  explicit Monocyte(const Real3& position) : Base(position) {}
  virtual ~Monocyte() {}
  int cell_color_;
  void SetCellColor(int cell_color) { cell_color_ = cell_color; }
  
  //birth
};

//define the macrophage
class Macrophage : public Cell {
  BDM_AGENT_HEADER(Macrophage, Cell, 1);
  
 public:
  Macrophage() {}
  explicit Macrophage(const Real3& position) : Base(position) {}
  virtual ~Macrophage() {}
  int cell_color_;
  void SetCellColor(int cell_color) { cell_color_ = cell_color; }
  
  bool is_active ();
  //age, lifespan, ingested lipid counter
};

//define the T cell
class Tcell : public Cell {
  BDM_AGENT_HEADER(Tcell, Cell, 1);

 public:
  Tcell() {}
  explicit Tcell(const Real3& position) : Base(position) {}
  virtual ~Tcell() {}
  int cell_color_;
  void SetCellColor(int cell_color) { cell_color_ = cell_color; }
  
  //age
};

//define the foam cell
class FoamCell : public Cell {
  BDM_AGENT_HEADER(FoamCell, Cell, 1);

 public:
  FoamCell() {}
  explicit FoamCell(const Real3& position) : Base(position) {}
  virtual ~FoamCell() {}
  int cell_color_;
  void SetCellColor(int cell_color) { cell_color_ = cell_color; }
  
  bool is_dead {false};
  //age, lipid counter, bursts counter
};

//define low density lipoprotein (LDL)
class LDL : public Cell {   
  BDM_AGENT_HEADER(LDL, Cell, 1);

 public:
  LDL() {}
  explicit LDL(const Real3& position) : Base(position) {}
  virtual ~LDL() {}
  const double LDL_molecular_weight {386.65}; // molecular weight of LDL (g/mol)
  int LDL_concentration {100}; // concentration of LDL in mg/dL, which can vary based on simulation scenario
  int cell_color_;
  void SetCellColor(int cell_color) { cell_color_ = cell_color; }
  
};

//define high density lipoprotein (HDL)
class HDL : public Cell {   
  BDM_AGENT_HEADER(HDL, Cell, 1);

 public:
  HDL() {}
  explicit HDL(const Real3& position) : Base(position) {}
  virtual ~HDL() {}
  
  const double HDL_molecular_weight {386.65}; // molecular weight of HDL 
  int HDL_concentration {}; // concentration of HDL in mg/dL, which can vary based on simulation scenario
  int cell_color_;
  void SetCellColor(int cell_color) { cell_color_ = cell_color; }
  
  
  
};

//define auto-antibodies (AAB)
class AAB : public Cell {   
  BDM_AGENT_HEADER(AAB, Cell, 1);

 public:
  AAB() {}
  explicit AAB(const Real3& position) : Base(position) {}
  virtual ~AAB() {}
  
  const int AAB_molecular_weight {150000}; // molecular weight of auto-antibodies (grams per mole)
  const int AAB_concentration {500}; // concentration of AAB in mU, which is the same in all simulation cases
  int cell_color_;
  void SetCellColor(int cell_color) { cell_color_ = cell_color; }
  
  //lipid counter
  
};


}

 





#endif  // BDM_AGENTS_H_





