cd
mkdir forza4
mkdir forza4/images
cd forza4/images
wget http://bssec.altervista.org/images/forza4/giallo.png
wget http://bssec.altervista.org/images/forza4/rosso.png
wget http://bssec.altervista.org/images/forza4/vuoto.png
cd ..
wget https://raw.githubusercontent.com/bssec/Forza4/master/forza4.c
gcc forza4.c $(pkg-config --cflags --libs gtk+-3.0) -o forza4
