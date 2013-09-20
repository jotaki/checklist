all:
	g++ -o checklist checklist.cpp icons.cpp main.cpp -W -Wall -s -O2 \
		`fox-1.7-config --cflags --libs`

clean:
	rm -f checklist

new_icons:
	rm -f icons.h icons.cpp
	@echo "#include \"icons.h\"" > icons.cpp
	reswrap -i -o icons.h icons/*.png
	reswrap -oa icons.cpp icons/*.png
