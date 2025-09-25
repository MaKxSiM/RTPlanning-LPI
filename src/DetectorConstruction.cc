//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4MaterialPropertyVector.hh"
#include "G4MaterialTable.hh"
#include "G4Material.hh"

DetectorConstruction::DetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{
  delete fStepLimit;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();
  env_mat = nist->FindOrBuildMaterial(env_mat_name);
  world_mat = nist->FindOrBuildMaterial(world_mat_name);

  G4Box* solidWorld =
    new G4Box("World",
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);

    logicWorld =
    new G4LogicalVolume(solidWorld,
                        world_mat,
                        "World");

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,
                      G4ThreeVector(),
                      logicWorld,
                      "World",
                      0,
                      false,
                      0,
                      checkOverlaps);

  G4Box* solidEnv =
    new G4Box("Envelope",
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ);

  logicEnv =
    new G4LogicalVolume(solidEnv,
                        env_mat,
                        "Envelope");

  physEnv = new G4PVPlacement(0,
                    G4ThreeVector(),
                    logicEnv,
                    "Envelope",
                    logicWorld,
                    false,
                    0,
                    checkOverlaps);

  ConstructScoringVolumes();

  return physWorld;
}

void DetectorConstruction::ConstructScoringVolumes(){
    
    G4NistManager* nist = G4NistManager::Instance();

  G4int  N = int(env_sizeZ/sc_vol_st);
  G4Box* templatebox =  new G4Box("Layer", 0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*sc_vol_st);

  logictempl = new G4LogicalVolume(templatebox,
                        nist->FindOrBuildMaterial(env_mat_name),
                        "Layer");
  G4String temp_str;
  const G4String pref = "Layer";

  G4VPhysicalVolume* phys_vol;


  for (G4int i = 0; i<N; i++){
      temp_str = pref + std::to_string(i);
          phys_vol = new G4PVPlacement(0,
                    G4ThreeVector(0, 0, -0.5*env_sizeZ + sc_vol_st/2 + sc_vol_st*i),
                    logictempl,
                    temp_str,
                    logicEnv,
                    false,
                    0,
                    checkOverlaps);
          fScoringVolumes.push_back(phys_vol);
  };

}
