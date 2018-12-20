CC=g++
CFLAGS = 
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system


DonkeyKong: DonkeyKong.cpp Entity.cpp EntityManager.cpp Game.cpp Coin.cpp Player.cpp Block.cpp Ladder.cpp Enemy.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) -c $< $(CFLAGS) $(LDLIBS)

clean:
	-rm -rf $(TARGET)

