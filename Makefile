# MakeFile for gallery
# server using C++ Microservice
# sudo mkdir /var/www/html/gallery
# sudo chown ubuntu /var/www/html/gallery

CC= g++

CFLAGS= -std=c++14  -Wno-deprecated-declarations

RM= /bin/rm -f

all: PutHTML gallery

colorEntry.o: colorEntry.cpp colorEntry.h
	$(CC) -c $(CFLAGS) colorEntry.cpp
	
galleryDB.o: galleryDB.cpp galleryDB.h
	$(CC) -c $(CFLAGS) -I/usr/include/cppconn galleryDB.cpp

gallery.o: gallery.cpp httplib.h
	$(CC) -c $(CFLAGS) gallery.cpp

gallery: gallery.o galleryDB.o colorEntry.o 
	$(CC) gallery.o galleryDB.o colorEntry.o -o gallery -L/usr/local/lib -lmariadbcpp
	


PutHTML:
	cp GalleryResponse.html /var/www/html/gallery/
	cp GalleryFeedback.html /var/www/html/gallery/
	cp -R css /var/www/html/gallery/
	cp gallery.js /var/www/html/gallery/
	cp GalleryLanding.html /var/www/html/gallery
	cp -R gund_img /var/www/html/gallery
	
	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/gallery/

clean:
	rm -f *.o gallery 
