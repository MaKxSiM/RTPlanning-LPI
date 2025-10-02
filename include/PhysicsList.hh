#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"
#include "QBBC.hh"


class PhysicsList:public G4VModularPhysicsList //public QBBC//
{

public:

  PhysicsList();

  virtual ~PhysicsList();

  virtual void SetCuts();

};

#endif
