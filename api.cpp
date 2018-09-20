#if __EMSCRIPTEN__
#include <vector>

#include <emscripten/bind.h>

#include "Player.h"

#include "Input/JsInputS.h"

std::vector<float> audiobuffer;

using namespace emscripten;

EMSCRIPTEN_BINDINGS(my_module) {
  enum_<FILE_TYPE>("FILE_TYPE")
      .value("FILE_WAV", FILE_WAV)
      .value("FILE_VORBIS", FILE_VORBIS)
      .value("FILE_MP3", FILE_MP3);

  enum_<FFTWindow>("FFTWindow")
      .value("W_RECTANGULAR", W_RECTANGULAR)
      .value("W_HAMMING", W_HAMMING)
      .value("W_HANN", W_HANN)
      .value("W_BLACKMAN", W_BLACKMAN)
      .value("W_BLACKMAN_HARRIS", W_BLACKMAN_HARRIS);

  enum_<Player::ModeType>("ModeType")
      .value("MODE_PLAY", Player::MODE_PLAY)
      .value("MODE_STOP", Player::MODE_STOP)
      .value("MODE_PREPARING", Player::MODE_PREPARING)
      .value("MODE_PAUSE", Player::MODE_PAUSE);

  class_<InputS>("InputS")
      .function("open", &InputS::open, pure_virtual())
      .function("close", &InputS::close, pure_virtual())
      .function("read",
                optional_override([](InputS& self, const val& x) -> int {
                  __builtin_unreachable();
                }),
                pure_virtual())
      .function("skip", &InputS::skip)
      .function("seek", &InputS::seek, pure_virtual())
      .property("nsamples", &InputS::get_nsamples, &InputS::set_nsamples)
      .property("nchannels", &InputS::get_nchannels, &InputS::set_nchannels)
      .property("samplerate", &InputS::get_samplerate, &InputS::set_samplerate)
      .property("currentsample", &InputS::get_currentsample,
                &InputS::set_currentsample)
      .property("eof", &InputS::eof)
      .allow_subclass<JsInputS>("JsInputS");

  class_<ProcessParameters>("ProcessParameters").constructor<>();
  class_<BinauralBeatsParameters>("BinauralBeatsParameters").constructor<>();
  class_<Player>("Player")
      .constructor<>()
      .function("startplay", &Player::startplay, allow_raw_pointers())
      .function("stop", &Player::stop)
      .function("pause", &Player::pause)
      .function("freeze", &Player::freeze)
      .function("setrap", &Player::setrap)
      .function("seek", &Player::seek)
      .function("getaudiobuffer",
                optional_override([](Player& self, int nsamples) -> val {
                  int nelements = nsamples * 2;
                  if (audiobuffer.size() < nelements) {
                    audiobuffer.resize(nelements);
                  }
                  self.getaudiobuffer(nsamples, audiobuffer.data());
                  return val(typed_memory_view(nelements, audiobuffer.data()));
                }))
      .function("getmode", &Player::getmode)
      .function("is_freeze", &Player::is_freeze)
      .function("set_window_type", &Player::set_window_type)
      .function("set_volume", &Player::set_volume)
      .function("set_onset_detection_sensitivity",
                &Player::set_onset_detection_sensitivity)
      .function("set_process_parameters", &Player::set_process_parameters,
                allow_raw_pointers())
      .function("newtaskcheck", &Player::newtaskcheck)
      .function("computesamples", &Player::computesamples)
      .property("position", &Player::get_position)
      .property("playing", &Player::get_playing)
      .property("samplerate", &Player::get_samplerate)
      .property("eof", &Player::get_eof);
}
#endif
