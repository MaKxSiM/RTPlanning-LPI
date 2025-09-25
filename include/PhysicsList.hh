#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"
#include "QBBC.hh"


class PhysicsList: public QBBC//public G4VModularPhysicsList
{

public:

  PhysicsList();

  virtual ~PhysicsList();

  virtual void SetCuts();

};

#endif
