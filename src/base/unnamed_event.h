// Copyright 2010-2018, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef MOZC_BASE_UNNAMED_EVENT_H_
#define MOZC_BASE_UNNAMED_EVENT_H_

#include "base/scoped_handle.h"

#ifndef OS_WIN
#include <pthread.h>
#endif

namespace mozc {

// UnnamedEvent is a simple event object shared by multiple threads.
class UnnamedEvent {
 public:
  UnnamedEvent();
  virtual ~UnnamedEvent();

  // Waits an event. Can set a maximum timeout value.
  // Return true if the event object receives a notification event from
  // different thread.
  bool Wait(int msec);

  // Raises a notification event.
  bool Notify();

  // Returns true if this event object is available.
  bool IsAvailable() const;

 private:
#ifdef OS_WIN
  ScopedHandle handle_;
#else
  pthread_cond_t cond_;
  pthread_mutex_t mutex_;
  bool notified_;
#endif
};
}  // namespace mozc

#endif  // MOZC_BASE_UNNAMED_EVENT_H_
