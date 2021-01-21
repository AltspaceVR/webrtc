/*
 *  Copyright (c) 2018 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef API_AUDIO_OPTIONS_H_
#define API_AUDIO_OPTIONS_H_

#include <string>

#include "absl/types/optional.h"

namespace cricket {

// Options that can be applied to a VoiceMediaChannel or a VoiceMediaEngine.
// Used to be flags, but that makes it hard to selectively apply options.
// We are moving all of the setting of options to structs like this,
// but some things currently still use flags.
struct AudioOptions {
  AudioOptions();
  ~AudioOptions();
  void SetAll(const AudioOptions& change);

  bool operator==(const AudioOptions& o) const;
  bool operator!=(const AudioOptions& o) const { return !(*this == o); }

  std::string ToString() const;

  // Audio processing that attempts to filter away the output signal from
  // later inbound pickup.
  absl::optional<bool> echo_cancellation;
#if defined(WEBRTC_IOS)
  // Forces software echo cancellation on iOS. This is a temporary workaround
  // (until Apple fixes the bug) for a device with non-functioning AEC. May
  // improve performance on that particular device, but will cause unpredictable
  // behavior in all other cases. See http://bugs.webrtc.org/8682.
  absl::optional<bool> ios_force_software_aec_HACK;
#endif
  // Audio processing to adjust the sensitivity of the local mic dynamically.
  absl::optional<bool> auto_gain_control;
  // Audio processing to filter out background noise.
  absl::optional<bool> noise_suppression;
  // Audio processing to remove background noise of lower frequencies.
  absl::optional<bool> highpass_filter;
  // Audio processing to swap the left and right channels.
  absl::optional<bool> stereo_swapping;
  // Audio receiver jitter buffer (NetEq) max capacity in number of packets.
  absl::optional<int> audio_jitter_buffer_max_packets;
  // Audio receiver jitter buffer (NetEq) fast accelerate mode.
  absl::optional<bool> audio_jitter_buffer_fast_accelerate;
  // Audio processing to detect typing.
  absl::optional<bool> typing_detection;
  absl::optional<bool> aecm_generate_comfort_noise;
  absl::optional<bool> experimental_agc;
  absl::optional<bool> extended_filter_aec;
  absl::optional<bool> delay_agnostic_aec;
  absl::optional<bool> experimental_ns;
  // Note that tx_agc_* only applies to non-experimental AGC.
  absl::optional<bool> residual_echo_detector;
  absl::optional<uint16_t> tx_agc_target_dbov;
  absl::optional<uint16_t> tx_agc_digital_compression_gain;
  absl::optional<bool> tx_agc_limiter;
  // Enable combined audio+bandwidth BWE.
  // TODO(pthatcher): This flag is set from the
  // "googCombinedAudioVideoBwe", but not used anywhere. So delete it,
  // and check if any other AudioOptions members are unused.
  absl::optional<bool> combined_audio_video_bwe;
  // Enable audio network adaptor.
  absl::optional<bool> audio_network_adaptor;
  // Config string for audio network adaptor.
  absl::optional<std::string> audio_network_adaptor_config;
  absl::optional<std::string> audio_device_id;
  absl::optional<bool> audio_loopback;
};

}  // namespace cricket

#endif  // API_AUDIO_OPTIONS_H_
