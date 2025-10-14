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
/// \file DetectorConstruction.cc
/// \brief Implementation of the B1::DetectorConstruction class

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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
  delete fStepLimit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Envelope parameters
  //
  env_mat = nist->FindOrBuildMaterial(env_mat_name);

  // Option to switch on/off checking of volumes overlaps
  //


  world_mat = nist->FindOrBuildMaterial(world_mat_name);

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

    logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  //
  // Envelope
  //
  G4Box* solidEnv =
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size

  logicEnv =
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name

  physEnv = new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


G4Box* solidFe =
    new G4Box("Fe",                    //its name
        0.5*Fe_sizeXY, 0.5*Fe_sizeXY, 0.5*Fe_sizeZ); //its size

  logicFe =
    new G4LogicalVolume(solidFe,            //its solid
                        Fe_mat,             //its material
                        "Fe_log");         //its name

  physFe = new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,-0.5*env_sizeZ-0.5*Fe_sizeZ-gap),         //at (0,0,0)
                    logicFe,                //its logical volume
                    "Fe_phys",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking



  //ConstructScoringVolumes();



// Set maximal step size
  G4double maxStep = 0.01 * CLHEP::mm;
  fStepLimit = new G4UserLimits(maxStep);
  logicEnv->SetUserLimits(fStepLimit);
  //logictempl->SetUserLimits(fStepLimit);
  //logictemp_pl_plate->SetUserLimits(fStepLimit);
  //logicShape2->SetUserLimits(fStepLimit);
  //
  //always return the physical World
  //
  return physWorld;
}

/*void DetectorConstruction::ConstructScoringVolumes(){


  G4NistManager* nist = G4NistManager::Instance();

//========platic A-150-tissue  with incorporated Bi particles =======================
  G4double density =  admix_c + (rho_tissue/rho_admix)*(rho_admix - admix_c);
  G4double admix_fr = admix_c /density;// mass fractions
  G4int ncomp = 2;

  TissueWithAdmixture = new G4Material(TissueWithAdmixture_name, density, ncomp);
  //Tissue = nist->FindOrBuildMaterial(Tissue_name); //for standard NIST materials

  G4HumanPhantomMaterial* material = new G4HumanPhantomMaterial();
  ///material->DefineMaterials();
  Tissue  = material->GetMaterial(Tissue_name);

  Admixture = nist->FindOrBuildMaterial(Admixture_name);
  TissueWithAdmixture->AddMaterial(Tissue, 1 - admix_fr);
  TissueWithAdmixture->AddMaterial(Admixture, admix_fr);
  //============================================================================

  //


  G4int  N = int(env_sizeZ/sc_vol_st);

  G4Box* templatebox =  new G4Box("Layer", 0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*sc_vol_st);     //its size

  logictempl = new G4LogicalVolume(templatebox,          //its solid
                        nist->FindOrBuildMaterial(env_mat_name),           //its material
                        "Layer");
  G4String temp_str;
  const G4String pref = "Layer";

  G4VPhysicalVolume* phys_vol;


  for (G4int i = 0; i<N; i++){
      temp_str = pref + std::to_string(i);
          phys_vol = new G4PVPlacement(0,                    //no rotation
                    G4ThreeVector(0, 0, -0.5*env_sizeZ + sc_vol_st/2 + sc_vol_st*i),
                    logictempl,                //its logical volume
                    temp_str,                     //its name
                    logicEnv,                     //its mother  volume
                    false,                        //no boolean operation
                    0,                            //copy number
                    checkOverlaps);                        //overlaps checking
          fScoringVolumes.push_back(phys_vol);
  };

}*/
