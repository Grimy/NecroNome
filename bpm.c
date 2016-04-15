#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define LA 440
#define SAMPLE_RATE 44100
#define MAX_VOL 0x8000

// Returns the frequency of a note `t` half-tones above LA
#define HZ(t) (LA * pow(2, (double) t / 12))

// Gives the `i`th sample for a note of frequency `hz`
#define SAMPLE(i, hz) (cos((i) * (hz) * 2 * M_PI / SAMPLE_RATE))

#define NORMALIZE(x, from, to) (((x) - (from)) / ((to) - (from)))
#define EASE(x) (1 - (1 - (x)) * (1 - (x)))
#define F(x, from, to) EASE(NORMALIZE(x, from, to))

#define ATTACK  0.1
#define DECAY   0.2
#define RELEASE 0.9
#define SUSTAIN 0.8

// major scale
// int scale[7] = {0, 2, 4, 5, 7, 9, 11};
// minor scale
int scale[7] = {0, 2, 3, 5, 7, 8, 10};

int main(int argc, char **argv) {
	FILE* aplay = popen("aplay -fS16_LE -r44100", "w");
	long bpm = argc > 1 ? atoi(argv[1]) : 300;
	long spb = SAMPLE_RATE * 60 / bpm;
	long beat = 1;

	for (long i = 0; ++i;) {
		beat += !(i % spb);
		double hz = HZ(scale[__builtin_ctz(beat)]);
		double x = (double) (i % spb) / spb;
		double vol = x < ATTACK  ? F(x, 0, ATTACK) :
					 x < DECAY   ? 1 - (1 - SUSTAIN) * F(x, ATTACK, DECAY) :
					 x < RELEASE ? SUSTAIN * (1 - F(x, DECAY, RELEASE)) : 0;
		int out = MAX_VOL * vol * SAMPLE(i, hz);
		fwrite(&out, 2, 1, aplay);
	}
}
