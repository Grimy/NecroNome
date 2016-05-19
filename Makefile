CC = clang
CFLAGS += -std=c99 -pedantic -march=native -fstrict-aliasing -fstrict-overflow
CFLAGS += -Weverything -Werror -Wno-c++-compat
# CFLAGS += -Ofast -fno-asynchronous-unwind-tables
CFLAGS += -O1 -ggdb -fsanitize=address,leak,undefined
CFLAGS += -D_XOPEN_SOURCE=500

bpm: bpm.c
	$(CC) $(CFLAGS) -lm $< -o $@

raw/%.raw: beatmaps/%.txt bpm
	./bpm $< >$@

ogg/%.ogg: raw/%.raw
	sox -esigned-integer -Lb16 -r44100 $< $@
ogg/%c.ogg: raw/%.raw
	sox -esigned-integer -Lb16 -r44100 $< $@
ogg/%h.ogg: raw/%.raw
	sox -esigned-integer -Lb16 -r44100 $< $@

SOUNDTRACK = _3
.PHONY: all
all: ogg/boss_1$(SOUNDTRACK).ogg
all: ogg/boss_2$(SOUNDTRACK).ogg
all: ogg/boss_3$(SOUNDTRACK).ogg
all: ogg/boss_4$(SOUNDTRACK).ogg
all: ogg/boss_5$(SOUNDTRACK).ogg
all: ogg/boss_6$(SOUNDTRACK).ogg
all: ogg/boss_7$(SOUNDTRACK).ogg
all: ogg/boss_8$(SOUNDTRACK).ogg
all: ogg/lobby$(SOUNDTRACK).ogg
all: ogg/training$(SOUNDTRACK).ogg
all: ogg/zone1_1$(SOUNDTRACK).ogg
all: ogg/zone1_2$(SOUNDTRACK).ogg
all: ogg/zone1_3$(SOUNDTRACK).ogg
all: ogg/zone2_1$(SOUNDTRACK).ogg
all: ogg/zone2_2$(SOUNDTRACK).ogg
all: ogg/zone2_3$(SOUNDTRACK).ogg
all: ogg/zone3_1$(SOUNDTRACK)c.ogg
all: ogg/zone3_1$(SOUNDTRACK)h.ogg
all: ogg/zone3_2$(SOUNDTRACK)c.ogg
all: ogg/zone3_2$(SOUNDTRACK)h.ogg
all: ogg/zone3_3$(SOUNDTRACK)c.ogg
all: ogg/zone3_3$(SOUNDTRACK)h.ogg
all: ogg/zone4_1$(SOUNDTRACK).ogg
all: ogg/zone4_2$(SOUNDTRACK).ogg
all: ogg/zone4_3$(SOUNDTRACK).ogg
