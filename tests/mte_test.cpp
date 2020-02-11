/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include <bionic/mte.h>

__attribute__((no_sanitize("hwaddress")))
static void test_tag_mismatch() {
  ScopedDisableMTE x;
#if defined(__aarch64__)
  std::unique_ptr<int[]> p = std::make_unique<int[]>(4);
  p[0] = 1;
  int* mistagged_p = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(p.get()) + (1ULL << 56));
  volatile int load = *mistagged_p;
  (void)load;
#endif
}

TEST(mte_test, ScopedDisableMTE) {
  test_tag_mismatch();
}
