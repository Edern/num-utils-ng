
#	File : Makefile
#	Compile all files in each directory

PROJECT	= num-utils-nv
DIST	= $(PROJECT)


TARFILE	= $(DIST).tar.gz

all:
	$(MAKE) -C src $@

clear : clean clearsrc

clearsrc : cleansrc
	$(RM) -f ./src/numaverage

clean : cleansrc

cleansrc :
	$(RM) -f ./src/*.o


dist: $(TARFILE)


$(TARFILE):
	rm -fr $(DIST)
	rm -f $(TARFILE)
	mkdir $(DIST)
	cp ./README $(DIST)
	cp ./Makefile $(DIST)
	cd $(DIST)
	mkdir $(DIST)/src
	cd ..
	cp ./src/*.c $(DIST)/src
	cp ./src/*.gz $(DIST)/src
	cp ./src/Makefile $(DIST)/src
	cp -R ./docs $(DIST) 
	tar zchf $(DIST).tar.gz $(DIST) --exclude CVS
	rm -r $(DIST)


