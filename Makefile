all:
	g++ -o checklist checklist.cpp icons.cpp main.cpp -W -Wall -s -O2 \
		`fox-1.7-config --cflags --libs`

clean:
	rm -f checklist
