#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define LA 440
#define SAMPLE_RATE 44100
#define MAX_VOL 0x8000

// Returns the frequency of a note `t` half-tones above LA
#define HZ(ht) (LA * pow(2, (double) (ht) / 12))
#define HALF_TONES(t) ((int[]) {0, 2, 3, 5, 7, 8, 10} [(t) % 7] + (t) / 7 * 12 )

// Gives the `i`th sample for a note of frequency `hz`
#define FRAC(x) ((x) - (long) (x))
#define SAMPLE(i, hz) (fabs(2 - 4 * FRAC((i) * (hz) / SAMPLE_RATE)) - 1)
// #define SAMPLE(i, hz) (sin(2 * M_PI * (i) * (hz) / SAMPLE_RATE))

#define NORMALIZE(x, from, to) (((x) - (from)) / ((to) - (from)))
// #define EASE(x) (1 - (1 - x) * (1 - x) * (1 - x))
#define EASE(x) ((1 - cos((x) * M_PI)) / 2)
#define F(x, from, to) EASE(NORMALIZE(x, from, to))

#define ATTACK  .02
#define DECAY   .18
#define RELEASE .36
#define SUSTAIN .9

// major scale
// int scale[7] = {0, 2, 4, 5, 7, 9, 11};

static long i;
static long last_beat;
static unsigned int beat;

static void do_beat(long next_beat) {
	beat++;
	beat += next_beat > last_beat + 20000;
	double hz = HZ(HALF_TONES(__builtin_ctz(beat)) - 8);
	while (++i < next_beat) {
		double x = (double) (i - last_beat) / (next_beat - last_beat);
		double vol = x < ATTACK  ? F(x, 0, ATTACK) :
					x < DECAY   ? 1 - (1 - SUSTAIN) * F(x, ATTACK, DECAY) :
					x < RELEASE ? SUSTAIN * (1 - F(x, DECAY, RELEASE)) : 0;
		int out = (int) (MAX_VOL * vol * SAMPLE(i, hz));
		putchar(out & 255);
		putchar(out >> 8);
	}
	last_beat = i;
}

int main(int argc, char **argv) {
	// FILE* aplay = popen("aplay -fS16_LE -r44100", "w");
	FILE* beatmap = fopen(argv[argc - 1], "r");
	long next_beat = 0;

	while (fscanf(beatmap, "%ld,", &next_beat) > 0) {
		next_beat = next_beat * SAMPLE_RATE / 1000;
		do_beat((next_beat + last_beat) / 2);
		do_beat(next_beat);
	}
}
