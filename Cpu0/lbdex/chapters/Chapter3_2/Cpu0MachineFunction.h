//===-- Cpu0MachineFunctionInfo.h - Private data used for Cpu0 ----*- C++ -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the Cpu0 specific subclass of MachineFunctionInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CPU0_CPU0MACHINEFUNCTION_H
#define LLVM_LIB_TARGET_CPU0_CPU0MACHINEFUNCTION_H

#include "Cpu0Config.h"

#include "llvm/ADT/StringMap.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/CodeGen/PseudoSourceValue.h"
#include "llvm/IR/GlobalValue.h"
#include "llvm/IR/ValueMap.h"
#include "llvm/Target/TargetFrameLowering.h"
#include "llvm/Target/TargetMachine.h"
#include <map>
#include <string>
#include <utility>

namespace llvm {

/// \brief A class derived from PseudoSourceValue that represents a GOT entry
/// resolved by lazy-binding.
class Cpu0CallEntry : public PseudoSourceValue {
public:
  explicit Cpu0CallEntry(StringRef N);
  explicit Cpu0CallEntry(const GlobalValue *V);
  bool isConstant(const MachineFrameInfo *) const override;
  bool isAliased(const MachineFrameInfo *) const override;
  bool mayAlias(const MachineFrameInfo *) const override;

private:
  void printCustom(raw_ostream &O) const override;
#ifndef NDEBUG
  std::string Name;
  const GlobalValue *Val;
#endif
};

//@1 {
/// Cpu0FunctionInfo - This class is derived from MachineFunction private
/// Cpu0 target-specific information for each MachineFunction.
class Cpu0FunctionInfo : public MachineFunctionInfo {
public:
  Cpu0FunctionInfo(MachineFunction& MF)
  : MF(MF), 
    VarArgsFrameIndex(0), 
    EmitNOAT(false),
    MaxCallFrameSize(0)
    {}

  ~Cpu0FunctionInfo();

  int getVarArgsFrameIndex() const { return VarArgsFrameIndex; }
  void setVarArgsFrameIndex(int Index) { VarArgsFrameIndex = Index; }

  bool getEmitNOAT() const { return EmitNOAT; }
  void setEmitNOAT() { EmitNOAT = true; }

private:
  virtual void anchor();

  MachineFunction& MF;

    /// VarArgsFrameIndex - FrameIndex for start of varargs area.
  int VarArgsFrameIndex;

  bool EmitNOAT;
  unsigned MaxCallFrameSize;

  /// Cpu0CallEntry maps.
  StringMap<std::unique_ptr<const Cpu0CallEntry>> ExternalCallEntries;
  ValueMap<const GlobalValue *, std::unique_ptr<const Cpu0CallEntry>>
      GlobalCallEntries;
};
//@1 }

} // end of namespace llvm

#endif // CPU0_MACHINE_FUNCTION_INFO_H

