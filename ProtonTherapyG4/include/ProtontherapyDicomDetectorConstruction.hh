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
// $Id: DicomNestedParamDetectorConstruction.hh 74809 2013-10-22 09:49:26Z gcosmo $
//
/// \file medical/DICOM/include/DicomNestedParamDetectorConstruction.hh
/// \brief Definition of the DicomNestedParamDetectorConstruction class
//

#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "DicomDetectorConstruction.hh"

#ifndef ProtontherapyDicomDetectorConstruction_h
#define ProtontherapyDicomDetectorConstruction_h 1


//*******************************************************
/// Construct the phantom using DicomPhantomParameterisationColour
//*******************************************************

class ProtontherapyDicomDetectorConstruction : public DicomDetectorConstruction
{
public:

  ProtontherapyDicomDetectorConstruction(G4LogicalVolume*);
  ~ProtontherapyDicomDetectorConstruction();

private:

  virtual void ConstructPhantom();

};

#endif
