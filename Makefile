
all: release

release:
	zip QTAquarius.zip QTAquarius/include/* QTAquarius/src/* QTAquarius/main.cpp QTAquarius/QTAquarius.pro

clean:
	rm -rf QTAquarius.zip