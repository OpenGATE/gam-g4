
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "G4Version.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4VPVParameterisation.hh"

namespace py = pybind11;


// https://pybind11.readthedocs.io/en/stable/advanced/classes.html
// Needed helper class because of the pure virtual method
class PyG4VPhysicalVolume : public G4VPhysicalVolume {
public:
  /* Inherit the constructors */
  using G4VPhysicalVolume::G4VPhysicalVolume;

  /* Trampoline (need one for each virtual function) */
  G4int GetCopyNo() const override {
    std::cout << "I am in PyG4VPhysicalVolume::GetCopyNo" << std::endl;
    PYBIND11_OVERLOAD_PURE(G4int, // Return type 
                           G4VPhysicalVolume, // Parent class 
                           GetCopyNo, // Name of function in C++ (must match Python name) 
                           // No argument here  
                           );
  }
};

/*
  virtual EVolume VolumeType() const = 0;
  // Characterise the type of volume - normal/replicated/parameterised.
  virtual G4bool IsMany() const = 0;
  // Return true if the volume is MANY (not implemented yet).
  virtual G4int GetCopyNo() const = 0;
  // Return the volumes copy number.
  virtual void  SetCopyNo(G4int CopyNo) = 0;
  // Set the volumes copy number.
  virtual G4bool IsReplicated() const = 0;
  // Return true if replicated (single object instance represents
  // many real volumes), else false.
  virtual G4bool IsParameterised() const = 0;
  // Return true if parameterised (single object instance represents
  // many real parameterised volumes), else false.
  virtual G4VPVParameterisation* GetParameterisation() const = 0;
  // Return replicas parameterisation object (able to compute dimensions
  // and transformations of replicas), or NULL if not applicable.
  virtual void GetReplicationData(EAxis& axis,
  G4int& nReplicas,
  G4double& width,
  G4double& offset,
  G4bool& consuming) const = 0;
  // Return replication information. No-op for no replicated volumes.
  virtual G4bool IsRegularStructure() const = 0;
  // Returns true if the underlying volume structure is regular.
  virtual G4int GetRegularStructureId() const = 0;
*/





void init_G4VPhysicalVolume(py::module & m) {

  py::class_<G4VPhysicalVolume, PyG4VPhysicalVolume>(m, "G4VPhysicalVolume")

    .def("SetTranslation",       &G4VPhysicalVolume::SetTranslation)
    .def("GetTranslation",       &G4VPhysicalVolume::GetTranslation, py::return_value_policy::copy)
    // return_value_policy<return_by_value>())
    
    .def("GetObjectTranslation", &G4VPhysicalVolume::GetObjectTranslation)
    .def("GetFrameTranslation",  &G4VPhysicalVolume::GetObjectTranslation)

    .def("SetRotation",          &G4VPhysicalVolume::SetRotation)


    // FIXME 
    // .def("GetRotation",          f1_GetRotation,
    //      return_internal_reference<>())
    // .def("GetRotation",          f2_GetRotation,
    //      return_internal_reference<>())
    /*
      .def("GetRotation", 
      py::overload_cast<const G4RotationMatrix*>(&G4VPhysicalVolume::GetRotation), py::const_)
      .def("GetRotation", 
      py::overload_cast<const G4RotationMatrix*>(&G4VPhysicalVolume::GetRotation), py::const_)
    */

    
    
    .def("GetObjectRotationValue", &G4VPhysicalVolume::GetObjectRotationValue)
    .def("GetFrameRotation",       &G4VPhysicalVolume::GetFrameRotation, py::return_value_policy::reference_internal)

    .def("SetLogicalVolume",     &G4VPhysicalVolume::SetLogicalVolume)
    .def("SetMotherLogical",     &G4VPhysicalVolume::SetMotherLogical)
    .def("GetLogicalVolume",     &G4VPhysicalVolume::GetLogicalVolume, py::return_value_policy::reference_internal)
    .def("GetMotherLogical",     &G4VPhysicalVolume::GetMotherLogical, py::return_value_policy::reference_internal)
    
    .def("SetName",             &G4VPhysicalVolume::SetName)
    .def("GetName",             &G4VPhysicalVolume::GetName, py::return_value_policy::copy)
    //      return_value_policy<return_by_value>())

    .def("SetCopyNo",           &G4VPhysicalVolume::SetCopyNo)

    .def("GetCopyNo",           &G4VPhysicalVolume::GetCopyNo)
    /*
    .def("GetCopyNo",  [](const G4VPhysicalVolume * base) {
                         std::cout << "G4VPhysicalVolume:: GetCopyNo" << std::endl;
                         return base->GetCopyNo();
                       })
    */
    
    .def("IsMany",              &G4VPhysicalVolume::IsMany)
    .def("IsReplicated",        &G4VPhysicalVolume::IsReplicated)
    .def("IsParameterised",     &G4VPhysicalVolume::IsParameterised)
    .def("GetMultiplicity",     &G4VPhysicalVolume::GetMultiplicity)
    .def("GetParameterisation", &G4VPhysicalVolume::GetParameterisation, py::return_value_policy::reference)
    //      return_value_policy<reference_existing_object>())

    // debug destructor
    .def("__del__",
         [](const G4VPhysicalVolume&) -> void { 
           std::cerr << "---------------> deleting G4VPhysicalVolume" << std::endl;
         })

    
    ;
}