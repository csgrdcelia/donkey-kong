CC=g++
CFLAGS = 
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system


DonkeyKong: DonkeyKong.cpp pch.cpp Entity.cpp Game.cpp LevelFactory.cpp Coin.cpp Player.cpp Block.cpp Ladder.cpp Enemy.cpp Level.cpp StringHelpers.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) -c $< $(CFLAGS) $(LDLIBS)

clean:
	-rm -rf $(TARGET)

