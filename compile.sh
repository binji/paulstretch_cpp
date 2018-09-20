#!/bin/bash
~/dev/wasm-install/bin/em++ --bind -s WASM=1 -DKISSFFT -I./contrib -I$HOME/dev/github/mxml ProcessedStretch.cpp Stretch.cpp FreeEdit.cpp globals.cpp Player.cpp Thread.cpp Mutex.cpp BinauralBeats.cpp api.cpp -x c contrib/kiss_fft.c contrib/kiss_fftr.c -x c++ -o emscripten/paulstretch.js -L$HOME/dev/github/mxml -lmxml
