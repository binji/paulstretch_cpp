#include "InputS.h"

#include <emscripten/bind.h>

class JsInputS : public emscripten::wrapper<InputS> {
 public:
  EMSCRIPTEN_WRAPPER(JsInputS);

  static JsInputS* make() {
    return emscripten::val::global()
        .call<emscripten::val>("makeJsInputS")
        .as<JsInputS*>(emscripten::allow_raw_pointers());
  }

  bool open(std::string filename) override {
    // Initialize InputS values.
    info.nsamples = 0;
    info.nchannels = 0;
    info.samplerate = 0;
    info.currentsample = 0;
    eof = false;

    return call<bool>("open", filename);
  }

  void close() override { call<void>("close"); }

  int read(int nsmps, short int* smps) override {
    return call<int>("read", emscripten::typed_memory_view(nsmps * 2, smps));
  }

  void seek(double pos) override { call<void>("seek", pos); }
};
