@echo off
echo Building code.c ...

gcc -c src/main.c -o build/main.o -Iinclude
gcc -c src/init.c -o build/init.o -Iinclude
gcc -c src/game.c -o build/game.o -Iinclude
gcc -c src/character.c -o build/character.o -Iinclude
gcc -c src/combat.c -o build/combat.o -Iinclude
gcc -c src/ai.c -o build/ai.o -Iinclude

gcc build/main.o build/init.o build/character.o build/game.o build/combat.o build/ai.o -o bin/main.exe

echo Build complete!

pause