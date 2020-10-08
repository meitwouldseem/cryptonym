nasm bootsec.asm -f bin -o bootsec.bin
nasm stageone.asm -f bin -o stageone.bin
copy /b bootsec.bin+stageone.bin bootloader.flp
pause