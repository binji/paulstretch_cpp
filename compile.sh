#!/bin/bash
~/dev/wasm/wasm-install/bin/em++ --bind -s ALLOW_MEMORY_GROWTH=1 -DKISSFFT -I./contrib -I$HOME/dev/mxml ProcessedStretch.cpp Stretch.cpp FreeEdit.cpp globals.cpp Player.cpp Thread.cpp Mutex.cpp BinauralBeats.cpp api.cpp -x c contrib/kiss_fft.c contrib/kiss_fftr.c -x c++ -o emscripten/paulstretch.js -L$HOME/dev/mxml -lmxml
