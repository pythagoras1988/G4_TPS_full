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
// $Id: DicomNestedParamDetectorConstruction.cc 101905 2016-12-07 11:34:39Z gunter $
//
/// \file medical/DICOM/src/DicomNestedParamDetectorConstruction.cc
/// \brief Implementation of the DicomNestedParamDetectorConstruction class
//
// History:
//        Pedro Arce
//
//*******************************************************

#include "globals.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Region.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "ScanningProtonBeamLine.hh"

#include "ProtontherapyDicomDetectorConstruction.hh"
#include "ProtontherapyDicomParameterisation.hh"
#include "DicomDetectorConstruction.hh"

#include "G4VisAttributes.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ProtontherapyDicomDetectorConstruction::ProtontherapyDicomDetectorConstruction(G4LogicalVolume* logicTreatmentRoom)
:DicomDetectorConstruction(logicTreatmentRoom)
{
  ConstructPhantom();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ProtontherapyDicomDetectorConstruction::~ProtontherapyDicomDetectorConstruction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ProtontherapyDicomDetectorConstruction::ConstructPhantom()
{
    //----- Replication of Water Phantom Volume.
    //--- Y Slice
    G4String yRepName("RepY");
    G4VSolid* solYRep = new G4Box(yRepName,fNVoxelX*fVoxelHalfDimX,
                                  fVoxelHalfDimY,
                                  fNVoxelZ*fVoxelHalfDimZ);
    G4LogicalVolume* logYRep = new G4LogicalVolume(solYRep,fAir,yRepName);
    new G4PVReplica(yRepName,logYRep,fContainer_logic,kYAxis,
                    fNVoxelY,fVoxelHalfDimY*2.); // With reference to the container!

    logYRep->SetVisAttributes(new G4VisAttributes(G4VisAttributes::GetInvisible()));

    //--- X Slice
    G4String xRepName("RepX");
    G4VSolid* solXRep = new G4Box(xRepName,fVoxelHalfDimX,fVoxelHalfDimY,
                                  fNVoxelZ*fVoxelHalfDimZ);
    G4LogicalVolume* logXRep = new G4LogicalVolume(solXRep,fAir,xRepName);
    new G4PVReplica(xRepName,logXRep,logYRep,kXAxis,fNVoxelX,fVoxelHalfDimX*2.);

    logXRep->SetVisAttributes(new G4VisAttributes(G4VisAttributes::GetInvisible()));

    //----- Voxel solid and logical volumes
    //--- Z Slice
    G4VSolid* solVoxel = new G4Box("phantom",fVoxelHalfDimX,
                                  fVoxelHalfDimY,fVoxelHalfDimZ);
    G4LogicalVolume* logicVoxel = new G4LogicalVolume(solVoxel,fAir,"phantom");

    logicVoxel->
    SetVisAttributes(new G4VisAttributes(G4VisAttributes::GetInvisible()));

    //
    // Parameterisation for transformation of voxels.
    //  (voxel size is fixed in this example.
    //    e.g. nested parameterisation handles material
    //    and transfomation of voxels.)
    G4ThreeVector voxelSize(fVoxelHalfDimX,fVoxelHalfDimY,fVoxelHalfDimZ);
    ProtontherapyDicomParameterisation* param = new ProtontherapyDicomParameterisation(voxelSize,
                                                fMaterials, fMasterHUData,
                                                fHUThresholdVector);

    new G4PVParameterised("phantom",    // their name
                          logicVoxel, // their logical volume
                          logXRep,      // Mother logical volume
                          kZAxis,       // Are placed along this axis
                          //kUndefined,
                          // Are placed along this axis
                          fNVoxelZ,      // Number of cells
                          param);       // Parameterisation.
  	G4cout<<fNVoxelY <<G4endl;
    param->SetNoVoxel( fNVoxelX, fNVoxelY, fNVoxelZ );

    SetScorer(logicVoxel);
}
