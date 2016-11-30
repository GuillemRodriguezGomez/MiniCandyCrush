#include <SDL\SDL.h>
#include <SDL\SDL_image.h>

int main(int, char*[]) {
	//SDL_Log("Executable built in %s", SDL_GetBasePath());
	try {
		//INIT
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw SDL_GetError();
		const Uint8 imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		if (!(IMG_Init(imgFlags)&imgFlags)) throw IMG_GetError();
		//WINDOW
		const int WIDTH = 1280, HEIGHT = 960;
		SDL_Window *window = SDL_CreateWindow("Hello SDL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
		if(window == nullptr) throw SDL_GetError();
		
		//RENDERER
		SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		//SPRITES
		SDL_Texture *bgTexture = IMG_LoadTexture(renderer,"../../res/gfx/dankBg.jpg");
		SDL_Texture *playerTexture = IMG_LoadTexture(renderer, "../../res/gfx/Pepanic.png");
		if (bgTexture == nullptr) throw SDL_GetError();
		SDL_Rect bgRect = { 0, 0, WIDTH, HEIGHT };
		SDL_Rect playerRect = { (WIDTH>>1)-100, (HEIGHT>>1)-100, 200, 200 };
		SDL_Rect playerTarget = { 0,0,100,100 };
		//GAME LOOP
		SDL_Event evnt;
		for (bool isRunning = true; isRunning;) {
			//INIT RENDERER
			while (SDL_PollEvent(&evnt)) {
				switch (evnt.type) {
				case SDL_QUIT: isRunning = false; break;
				case SDL_MOUSEMOTION: playerTarget.x = evnt.motion.x - 100; playerTarget.y = evnt.motion.y - 100;
				default:;
				}
			}
			//UPDATE
			playerRect.x += (playerTarget.x - playerRect.x)*0.1f;
			playerRect.y += (playerTarget.y - playerRect.y)*0.1f;
			//DRAW
			SDL_RenderCopy(renderer, bgTexture,nullptr,&bgRect);
			SDL_RenderCopy(renderer, playerTexture, nullptr, &playerRect);
			SDL_RenderPresent(renderer);
		}
		//DESTROY
		SDL_DestroyTexture(bgTexture);
		SDL_DestroyTexture(playerTexture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}
	catch (const char *msg) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", msg);
	}
	IMG_Quit();
	SDL_Quit();
	return 0;
}