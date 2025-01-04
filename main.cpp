#include "main.h"

bool init()
{
  // Initialization flag
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  }
  else
  {
    // Create window
    gWindow = SDL_CreateWindow("YOU GOT RICK ROLLED", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (gWindow == NULL)
    {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    }
    else
    {
      // Get window surface
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }

  return success;
}

bool loadMedia()
{
  // Loading success flag
  bool success = true;

  // Load image
  gImage = SDL_LoadBMP("lib/rick.bmp");

  if (gImage == NULL)
  {
    printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
    success = false;
  }

  return success;
}

void close()
{
  // Deallocate surface
  SDL_FreeSurface(gImage);

  gImage = NULL;

  // Destroy window
  SDL_DestroyWindow(gWindow);

  gWindow = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}

int main(int argc, char *args[])
{
  // Start up SDL and create window
  if (!init())
  {
    printf("Failed to initialize!\n");
  }
  else
  {
    // Load media
    if (!loadMedia())
    {
      printf("Failed to load media!\n");
    }
    else
    {
      // Apply the image
      SDL_BlitSurface(gImage, NULL, gScreenSurface, NULL);

      // Update the surface
      SDL_UpdateWindowSurface(gWindow);

      // Hack to get window to stay up
      SDL_Event e;
      bool quit = false;
      while (quit == false)
      {
        while (SDL_PollEvent(&e))
        {
          if (e.type == SDL_QUIT)
            quit = true;
        }
      }
    }
  }

  // Free resources and close SDL
  close();

  return 0;
}