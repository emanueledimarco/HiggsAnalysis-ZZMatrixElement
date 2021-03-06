#include <ZZMatrixElement/MELA/interface/PDGHelpers.h>

namespace PDGHelpers{
  double HVVmass = Zmass;
}

bool PDGHelpers::isAJet(const int id){
  if (PDGHelpers::isAnUnknownJet(id) || PDGHelpers::isAQuark(id) || PDGHelpers::isAGluon(id)) return true;
  else return false;
}
bool PDGHelpers::isAnUnknownJet(const int id){
  if (id==0) return true;
  else return false;
}
bool PDGHelpers::isInvalid(const int id){
  if (id==-9000) return true;
  else return false;
}
bool PDGHelpers::isAQuark(const int id){
  if (std::abs(id)<=6 && std::abs(id)>0) return true;
  else return false;
}
bool PDGHelpers::isUpTypeQuark(const int id){
  if (std::abs(id)==2 || std::abs(id)==4 || std::abs(id)==6) return true;
  else return false;
}
bool PDGHelpers::isDownTypeQuark(const int id){
  if (std::abs(id)==1 || std::abs(id)==3 || std::abs(id)==5) return true;
  else return false;
}
bool PDGHelpers::isALepton(const int id){
  if (std::abs(id)==11 || std::abs(id)==13 || std::abs(id)==15) return true;
  else return false;
}
bool PDGHelpers::isANeutrino(const int id){
  if (std::abs(id)==12 || std::abs(id)==14 || std::abs(id)==16) return true;
  else return false;
}
bool PDGHelpers::isAGluon(const int id){
  if (std::abs(id)==21) return true;
  else return false;
}
bool PDGHelpers::isAPhoton(const int id){
  if (std::abs(id)==22) return true;
  else return false;
}
bool PDGHelpers::isAZBoson(const int id){
  if (std::abs(id)==23) return true;
  else return false;
}
bool PDGHelpers::isAWBoson(const int id){
  if (std::abs(id)==24) return true;
  else return false;
}
bool PDGHelpers::isAHiggs(const int id){
  if (std::abs(id)==25) return true;
  else return false;
}
void PDGHelpers::setHVVmass(double mymass){
  PDGHelpers::HVVmass=mymass;
}
// Test everything in outgoing conventions, do not pass ud or uu for example, pass outgoing u,-(incoming d) or outgoing u,-(incoming u)
int PDGHelpers::getCoupledVertex(const int idfirst, const int idsecond, int* hel, int* useAHcoupl){
  int ids[2]={ idfirst, idsecond };
  int ids_jhu[2]={ -9000, -9000 };
  for (unsigned int ip=0; ip<2; ip++){ if (!PDGHelpers::isInvalid(ids[ip])) ids_jhu[ip] = convertLHEreverse(&(ids[ip])); }
  int zahswitch=0;
  if (useAHcoupl!=0) zahswitch = *useAHcoupl;
  // Left-handed couplings always exist; right handed ones may or may not exist. This is why the default below is -1 for left-handed.
  // Example: Z->nu nub does not have Z->nu_R nub_L counterpart because nu_R or nub_L do not exist!
  int heleff=-1;
  if (hel!=0) heleff = *hel;
  int Vid_jhu = CoupledVertex(ids_jhu, &heleff, &zahswitch);
  return convertLHE(&Vid_jhu);
}
int PDGHelpers::convertPythiaStatus(int pSt){
  if (pSt==0) return 1;
  else if (pSt==1 || pSt==23) return 1;
  else if (pSt==21) return -1;
  else if (pSt==22 || pSt==62) return 2;
  else{
    std::cerr << "Unknown Pythia particle status: " << pSt << std::endl;
    return -99;
  }
}


