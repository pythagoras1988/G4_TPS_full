#include "globals.hh"
#include <vector>
#include <map>
#include <string>

using namespace std;

#ifndef ScanningProtonBeamSpecification_hh
#define ScanningProtonBeamSpecification_hh 1

class ScanningProtonBeamSpecification {
  public:
    ScanningProtonBeamSpecification();
    ~ScanningProtonBeamSpecification();

    map<G4int,vector<G4double>> GetWeightDataMap();
    vector<double> GetEnergyList();
    G4int GetNumberOfEvents();

  private:
    string fDirectory;
    int numEnergyLayers;
    vector<double> energyList;
    bool constantWeight;
    bool constantEnergy;
    G4double fFluenceConstant;
    G4double fConstantWeightValue;
    G4double fTotalWeight;
    G4double numberOfEvents;
    map<G4int,vector<G4double>> fWeightData;

    void CalibrateEnergy();
    void ReadEnergyListFile();
    void ReadWeightDataToMemory();

};
#endif
