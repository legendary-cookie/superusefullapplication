#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>
#include <SDL.h>
#include <SDL_mixer.h>

int main(int argc, char *argv[])
{
    //init
    consoleInit(NULL);
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    PadState pad;
    padInitializeDefault(&pad);
    Result rc = romfsInit();
    if (R_FAILED(rc))
        printf("romfsInit: %08X\n", rc);
    else
        printf("Press A to init!\n");
    //sdl
    SDL_Init(SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    Mix_Music *audio = Mix_LoadMUS("romfs:/justanormalsound.mp3");
    while (appletMainLoop())
    {
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);
        if (kDown & HidNpadButton_Plus)
            break;
        if (kDown & HidNpadButton_A)
            Mix_PlayMusic(audio, 1); 
        consoleUpdate(NULL);
    }
//cleanup
    Mix_FreeMusic(audio);
    SDL_Quit();
    romfsExit();
    consoleExit(NULL);
    return 0;
}
