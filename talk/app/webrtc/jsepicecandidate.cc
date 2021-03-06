/*
 * libjingle
 * Copyright 2012, Google Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "talk/app/webrtc/jsepicecandidate.h"

#include <vector>

#include "talk/app/webrtc/webrtcsdp.h"

namespace webrtc {

// TODO: Add locks if there are non-const methods added to the
// interface since it can be access from both the application and jsepsignaling.

JsepIceCandidate::JsepIceCandidate(const std::string& label)
    : label_(label) {
}

JsepIceCandidate::~JsepIceCandidate() {
}

void JsepIceCandidate::SetCandidate(const cricket::Candidate& candidates) {
  candidate_ = candidates;
}

bool JsepIceCandidate::Initialize(const std::string& sdp) {
  std::vector<cricket::Candidate> candidates;
  if (!SdpDeserializeCandidates(sdp, &candidates) || candidates.size() != 1) {
    return false;
  }
  candidate_ = candidates[0];
  return true;
}

bool JsepIceCandidate::ToString(std::string* out) const {
  if (!out)
    return false;
  std::vector<cricket::Candidate> candidates;
  candidates.push_back(candidate_);
  *out = SdpSerializeCandidates(candidates);
  return !out->empty();
}

}  // namespace webrtc
