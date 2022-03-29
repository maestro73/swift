//===--- MutexWin32.h - -----------------------------------------*- C++ -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2017 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//
//
// Mutex and Read/Write lock implementations using Windows Slim
// Reader/Writer Locks and Conditional Variables.
//
//===----------------------------------------------------------------------===//

#ifndef SWIFT_RUNTIME_MUTEX_WIN32_H
#define SWIFT_RUNTIME_MUTEX_WIN32_H

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

namespace swift {

typedef SRWLOCK MutexHandle;

#define SWIFT_MUTEX_SUPPORTS_CONSTEXPR 1

struct MutexPlatformHelper {
  static constexpr MutexHandle staticInit() { return SRWLOCK_INIT; }
  static void init(MutexHandle &mutex, bool checked = false) {
    InitializeSRWLock(&mutex);
  }
  static void destroy(MutexHandle &mutex) {}
  static void lock(MutexHandle &mutex) { AcquireSRWLockExclusive(&mutex); }
  static void unlock(MutexHandle &mutex) { ReleaseSRWLockExclusive(&mutex); }
  static bool try_lock(MutexHandle &mutex) {
    return TryAcquireSRWLockExclusive(&mutex) != 0;
  }
  // The unsafe versions don't do error checking.
  static void unsafeLock(MutexHandle &mutex) {
    AcquireSRWLockExclusive(&mutex);
  }
  static void unsafeUnlock(MutexHandle &mutex) {
    ReleaseSRWLockExclusive(&mutex);
  }
};

#endif
