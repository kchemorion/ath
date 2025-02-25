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
#ifndef ATHEROSCLEROSIS_H_
#define ATHEROSCLEROSIS_H_

#include "biodynamo.h"
#include "Agents.h"
#include "Agent_motion.h"
#include "core/agent/cell.h"
#include "core/environment/environment.h"
#include "core/simulation.h"
#include "core/param/param.h"
#include "core/util/random.h"
#include <cmath>


namespace bdm {

//define the boundary conditions of the 3D environment (a cube with periodic boundaries)

inline int Simulate(int argc, const char** argv) {
  auto set_param = [](Param* param) {
    param->bound_space = Param::BoundSpaceMode::kTorus;
    param->min_bound = 0; 
    param->max_bound = 260; 
    param->simulation_time_step = 1;  
  };

  Simulation simulation(argc, argv, set_param);
  auto* ctxt = simulation.GetExecutionContext();
  
  size_t spacing = 20; // Spacing between cells
  
  
  real_t x_coordEC, y_coordEC, z_coordEC; // endothelial cell coordinates
   
  // Create endothelial cells in the 3D grid
  
  for (double x = 0.5; x < 13.5; ++x) {
    for (double z = 0.5; z < 13.5; ++z) {
      x_coordEC = x * spacing; // x-coordinate
      z_coordEC = z * spacing; // z-coordinate
      y_coordEC = 12.5 * spacing; // y-coordinate 
      // Create a new cell
      EndothelialCell* cell = new EndothelialCell({x_coordEC, y_coordEC, z_coordEC});
      cell->SetDiameter(20);
      cell->SetCellColor(0);
     
      ctxt->AddAgent(cell);  // put the created endothelial cells in our cell structure
  
  }
  }
  
  real_t x_coordSMC, y_coordSMC, z_coordSMC; // smooth muscle cell coordinates

  // Create smooth muscle cells in the 3D grid
  
  for (double x = 0.5; x < 13.5; ++x) {
    for (double y = 0.5; y < 6.5; ++y) {
      for (double z = 0.5; z < 13.5; ++z) {
        x_coordSMC = x * spacing; // x-coordinate
        y_coordSMC = y * spacing; // y-coordinate
        z_coordSMC = z * spacing; // z-coordinate 
        SmoothMuscleCell* cell = new SmoothMuscleCell({x_coordSMC, y_coordSMC, z_coordSMC});
        cell->SetDiameter(20);
        cell->SetCellColor(1);
        ctxt->AddAgent(cell);  // put the created smooth muscle cells in our 3D  environment
     
      }
    }
  }
  
 real_t x_coord_monocyte, y_coord_monocyte, z_coord_monocyte; // random coordinates for the single monocyte initially in the intimal space
 
 // Initialize a single monocyte randomly postioned within the boundaries of the intimal space
 
  auto* random = simulation.GetRandom();

   x_coord_monocyte = random->Uniform(0.0, 260.0);  //boundaries of the intima
   y_coord_monocyte = random->Uniform(120, 240.0);
   z_coord_monocyte = random->Uniform(0.0, 260.0);
   Monocyte* cell = new Monocyte({x_coord_monocyte, y_coord_monocyte, z_coord_monocyte});
    // set cell parameters
   cell->SetDiameter(8);
   cell->SetCellColor(2);
   cell->AddBehavior(new BrownianMotion());
   ctxt->AddAgent(cell);  // put the created cell in our cell structure
  
 //create LDL particles in the intima
  
  constexpr double Avogadro_number = 6.022e23; // the Avogadro number is used to translate concentrations into the number of particles in the intima
  constexpr double intimal_volume = 8.112e6;       //the volume of the intima in micrometers cubed
  constexpr double mgdL_to_gmicrom = 1e-17;        // converts mg/dL to gram per micrometer cubed
  int LDL_concentration = 100;
  const double molecular_weight = 386.65; //grams per mole
  double LDL_mgdl_to_particles = (LDL_concentration * mgdL_to_gmicrom * Avogadro_number * intimal_volume) / molecular_weight;
  int LDL_particles = static_cast<int>(std::round(LDL_mgdl_to_particles / 1e9));
  
  std::cout << "number of LDL particles is " << LDL_particles << std::endl;

  real_t x_coord_LDL, y_coord_LDL, z_coord_LDL; // random coordinates for the LDL particles in the intimal space
  
  //Initialize LDL particles randomly positioned within the boundaries of the intimal space
  
  for (int i=0; i<LDL_particles; ++i) {
    x_coord_LDL = random->Uniform(0.0, 260.0);  //boundaries of the intima
    y_coord_LDL = random->Uniform(120.0, 240.0);
    z_coord_LDL = random->Uniform(0.0, 260.0);
    LDL* cell = new LDL({x_coord_LDL, y_coord_LDL, z_coord_LDL});
  // set particle parameters
    cell->SetDiameter(0.5);
    cell->SetCellColor(3);
    cell->AddBehavior(new BrownianMotion());
    ctxt->AddAgent(cell);  // put the created molecules in our cell structure
  }
  
  //create HDL particles in the intima
  
  int HDL_concentration = 50;
  
  double HDL_mgdl_to_particles = (HDL_concentration * mgdL_to_gmicrom * Avogadro_number * intimal_volume) / molecular_weight;
  int HDL_particles = static_cast<int>(std::round(HDL_mgdl_to_particles / 1e9));
  
  std::cout << "number of HDL particles is " << HDL_particles << std::endl;

  real_t x_coord_HDL, y_coord_HDL, z_coord_HDL; // random coordinates for the HDL particles in the intimal space
  
  //Initialize HDL particles randomly positioned within the boundaries of the intimal space
  
  for (int i=0; i<HDL_particles; ++i) {
    x_coord_HDL = random->Uniform(0.0, 260.0);  //boundaries of the intima
    y_coord_HDL = random->Uniform(120.0, 240.0);
    z_coord_HDL = random->Uniform(0.0, 260.0);
    HDL* cell = new HDL({x_coord_HDL, y_coord_HDL, z_coord_HDL});
  // set particle parameters
    cell->SetDiameter(0.5);
    cell->SetCellColor(4);
    cell->AddBehavior(new BrownianMotion());
    ctxt->AddAgent(cell);  // put the created lipid molecules in our cell structure
  }

 //Initialize auto-antibodies in the intima
  
  const double AAB_molecular_weight {1.5e5}; // molecular weight of auto-antibodies (grams per mole)
  const int AAB_concentration {500};
  double mcg_mcl_AAB = AAB_concentration * 3.84 / 100; //converts the AAB concentration in mU to microgram/microliter
  double AAB_molecules = 1e5 * (mcg_mcl_AAB * mgdL_to_gmicrom * Avogadro_number * intimal_volume) / AAB_molecular_weight;
  int AAB_particles = static_cast<int>(std::round(AAB_molecules / 1e12));
  
  std::cout << "number of AAB particles is " << AAB_particles << std::endl;

  real_t x_coord_AAB, y_coord_AAB, z_coord_AAB; // random coordinates for the AAB particles in the intimal space
  
  //Create AAB particles randomly positioned within the boundaries of the intimal space
  
  for (int i=0; i<AAB_particles; ++i) {
    x_coord_AAB = random->Uniform(0.0, 260.0);  //boundaries of the intima
    y_coord_AAB = random->Uniform(120.0, 240.0);
    z_coord_AAB = random->Uniform(0.0, 260.0);
    AAB* cell = new AAB({x_coord_AAB, y_coord_AAB, z_coord_AAB});
  // set particle parameters
    cell->SetDiameter(1.2);
    cell->SetCellColor(5);
    cell->AddBehavior(new BrownianMotion());
    ctxt->AddAgent(cell);  // put the created lipid molecules in our cell structure
  }
  // Run the simulations
  simulation.GetScheduler()->Simulate(100);
  
  // Ensure memory cleanup
  BrownianMotion::Cleanup();

  std::cout << "Simulation completed successfully!" << std::endl;
  return 0;
}

}  // namespace bdm

#endif  // ATHEROSCLEROSIS_H_



  
