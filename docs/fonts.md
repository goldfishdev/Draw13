Ignore this for now. Gonna write more soon. Python script maybe. ID K

```c
// script that turns FONT.TXT into usable data
// see FONT.TXT
//
// font info
#define BYTES_PER_CHAR 6
#define CHAR_WIDTH 5
#define CHAR_HEIGHT 6
#define KERNING (CHAR_WIDTH + 1)

unsigned char FontName[256 * BYTES_PER_CHAR];

void export_font_to_c(const char* output_filename) {
	FILE* outfile = fopen(output_filename, "w");
	int i, j;

	if (!outfile) {
		printf("Error opening output file!\n");
		return;
	}

	fprintf(outfile, "/* Font data generated from FONT.TXT */\n");
	fprintf(outfile, "/* Each character is %d bytes */\n\n", BYTES_PER_CHAR);
	fprintf(outfile, "#define BYTES_PER_CHAR %d\n", BYTES_PER_CHAR);
	fprintf(outfile, "#define CHAR_WIDTH %d\n", CHAR_WIDTH);
	fprintf(outfile, "#define CHAR_HEIGHT %d\n", CHAR_HEIGHT);
	fprintf(outfile, "#define KERNING %d\n\n", KERNING);

	fprintf(outfile, "const unsigned char FontName[256 * BYTES_PER_CHAR] = {\n");

	for (i = 0; i < 256; i++) {
		fprintf(outfile, "    /* ASCII %3d", i);
		if (i >= 32 && i <= 126) {
			fprintf(outfile, " '%c'", (char)i);
		}
		fprintf(outfile, " */\n    ");

		for (j = 0; j < BYTES_PER_CHAR; j++) {
			fprintf(outfile, "0x%02X", FontName[i * BYTES_PER_CHAR + j]);

			if (i != 255 || j != BYTES_PER_CHAR - 1) {
				fprintf(outfile, ", ");
			}

			if (j == BYTES_PER_CHAR - 1 && i != 255) {
				fprintf(outfile, "\n");
			}
		}
	}

	fprintf(outfile, "\n};\n");
	fclose(outfile);
	printf("Font data exported to %s\n", output_filename);
}
```
