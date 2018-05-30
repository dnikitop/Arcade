#----------------------

SOURCE=Asteroids.cpp centipede.cpp flythrough.cpp FroggerFinalVersionDone.cpp fssimplewindow.cpp galaga.cpp pacman.cpp Tetris.cpp Tron.cpp ysglfontdata.c yspng.cpp ysglmaketextbitmap.c

MYPROGRAM=flythrough.exe


#----------------------------------


all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)
	cl /EHsc $(SOURCE) -o$(MYPROGRAM)
#	del *.obj
clean:
	del *.obj
