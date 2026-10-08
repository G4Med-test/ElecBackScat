#ifndef MATERIALS_HH
#define MATERIALS_HH

#include "globals.hh"
#include <vector>

class G4Material;


class Materials {

 public:
   static Materials* Instance();
   static void Destroy();
   
   G4Material* GetMaterial(G4String matName);
   
 protected:
   Materials();
   virtual ~Materials();

   Materials(const Materials& only);
   const Materials& operator=(const Materials& only);

 private:
   static Materials* instance;

   std::vector<G4Material*> materials;
};

#endif // MATERIALS_HH
