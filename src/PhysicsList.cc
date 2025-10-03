#include "PhysicsList.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4NuclideTable.hh"
//#include "HadronElasticPhysicsHP.hh"
//#include "G4HadronPhysicsFTFP_BERT_HP.hh"
//#include "G4HadronPhysicsQGSP_BIC_HP.hh"
//##include "G4HadronInelasticQBBC.hh"
#include "QBBC.hh"

//#include "G4HadronPhysicsINCLXX.hh"
#include "G4IonElasticPhysics.hh"
//#include "G4IonPhysicsXS.hh"
//#include "G4IonINCLXXPhysics.hh"
#include "G4StoppingPhysics.hh"

#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option1.hh"
//#include "G4DecayPhysics.hh"
//#include "G4RadioactiveDecayPhysics.hh"

#include "G4StepLimiterPhysics.hh"

PhysicsList::PhysicsList()
:QBBC()
//:G4VModularPhysicsList()

{

  G4int verb = 1;
  SetVerboseLevel(verb);

//  RegisterPhysics(new G4EmStandardPhysics_option3(verb));
//  RegisterPhysics(new G4IonElasticPhysics());
//  RegisterPhysics(new G4StoppingPhysics());
//  RegisterPhysics(new G4StepLimiterPhysics());
   G4StepLimiterPhysics* steplimph = new G4StepLimiterPhysics();
   steplimph->SetApplyToAll(true);
  RegisterPhysics(steplimph); //!!!

  const G4double meanLife = 1*nanosecond, halfLife = meanLife*std::log(2);

  G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(halfLife);
//  const G4double meanLife = 1*nanosecond, halfLife = meanLife*std::log(2);

//  G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(halfLife);


}

PhysicsList::~PhysicsList()

{ }

void PhysicsList::SetCuts()

{

  // SetCutValue(0*mm, "proton");
  // SetCutValue(10*km, "e-");
  // SetCutValue(10*km, "e+");
  // SetCutValue(10*km, "gamma");

}
