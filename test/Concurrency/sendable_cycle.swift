// RUN: %target-swift-frontend %S/Inputs/sendable_cycle_other.swift  -disable-availability-checking %s -verify -emit-sil -o /dev/null
// RUN: %target-swift-frontend %S/Inputs/sendable_cycle_other.swift  -disable-availability-checking %s -verify -emit-sil -o /dev/null -strict-concurrency=targeted
// RUN: %target-swift-frontend %S/Inputs/sendable_cycle_other.swift  -disable-availability-checking %s -verify -emit-sil -o /dev/null -strict-concurrency=complete -verify-additional-prefix complete-
// RUN: %target-swift-frontend %S/Inputs/sendable_cycle_other.swift  -disable-availability-checking %s -verify -emit-sil -o /dev/null -strict-concurrency=complete -verify-additional-prefix complete- -enable-experimental-feature RegionBasedIsolation

// REQUIRES: concurrency
// REQUIRES: asserts

struct Bar {
  lazy var foo = { // expected-error {{escaping closure captures mutating 'self' parameter}}
    self.x() // expected-note {{captured here}}
  }

  func x() -> Int { 42 }
}
