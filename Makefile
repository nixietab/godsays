CC = gcc
CFLAGS = -Os -Wall -Wextra
LDFLAGS = -s
OUT = godsays

HEADER = happy_txt.h
SOURCE = main.c

all: $(OUT)

$(HEADER): Happy.TXT
	@if command -v xxd >/dev/null 2>&1; then \
	    xxd -i Happy.TXT > $(HEADER); \
	else \
	    printf "unsigned char Happy_TXT[] = {" > $(HEADER); \
	    hexdump -v -e '1/1 "0x%02x,"' Happy.TXT >> $(HEADER); \
	    printf "};\nunsigned int Happy_TXT_len = sizeof(Happy_TXT);\n" >> $(HEADER); \
	fi

$(OUT): $(SOURCE) $(HEADER)
	$(CC) $(CFLAGS) $(SOURCE) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT) $(HEADER)

.PHONY: all clean