//===-- Cpu0MachineFunctionInfo.cpp - Private data used for Cpu0 ----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Cpu0MachineFunction.h"

#include "MCTargetDesc/Cpu0BaseInfo.h"
#include "Cpu0InstrInfo.h"
#include "Cpu0Subtarget.h"
#include "llvm/IR/Function.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"

using namespace llvm;

bool FixGlobalBaseReg;

// class Cpu0CallEntry.
Cpu0CallEntry::Cpu0CallEntry(StringRef N) {
#ifndef NDEBUG
  Name = N;
  Val = nullptr;
#endif
}

Cpu0CallEntry::Cpu0CallEntry(const GlobalValue *V) {
#ifndef NDEBUG
  Val = V;
#endif
}

bool Cpu0CallEntry::isConstant(const MachineFrameInfo *) const {
  return false;
}

bool Cpu0CallEntry::isAliased(const MachineFrameInfo *) const {
  return false;
}

bool Cpu0CallEntry::mayAlias(const MachineFrameInfo *) const {
  return false;
}

void Cpu0CallEntry::printCustom(raw_ostream &O) const {
  O << "Cpu0CallEntry: ";
#ifndef NDEBUG
  if (Val)
    O << Val->getName();
  else
    O << Name;
#endif
}

Cpu0FunctionInfo::~Cpu0FunctionInfo() {}

bool Cpu0FunctionInfo::globalBaseRegFixed() const {
  return FixGlobalBaseReg;
}

bool Cpu0FunctionInfo::globalBaseRegSet() const {
  return GlobalBaseReg;
}

unsigned Cpu0FunctionInfo::getGlobalBaseReg() {
  return GlobalBaseReg = Cpu0::GP;
}

void Cpu0FunctionInfo::createEhDataRegsFI() {
  for (int I = 0; I < 2; ++I) {
    const TargetRegisterClass *RC = &Cpu0::CPURegsRegClass;

    EhDataRegFI[I] = MF.getFrameInfo()->CreateStackObject(RC->getSize(),
        RC->getAlignment(), false);
  }
}

MachinePointerInfo Cpu0FunctionInfo::callPtrInfo(StringRef Name) {
  std::unique_ptr<const Cpu0CallEntry> &E = ExternalCallEntries[Name];

  if (!E)
    E = llvm::make_unique<Cpu0CallEntry>(Name);

  return MachinePointerInfo(E.get());
}

MachinePointerInfo Cpu0FunctionInfo::callPtrInfo(const GlobalValue *Val) {
  std::unique_ptr<const Cpu0CallEntry> &E = GlobalCallEntries[Val];

  if (!E)
    E = llvm::make_unique<Cpu0CallEntry>(Val);

  return MachinePointerInfo(E.get());
}

void Cpu0FunctionInfo::anchor() { }

