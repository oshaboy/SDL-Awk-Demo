BEGIN {
	SDL_Init()
	window=SDL_CreateWindow("SDL Awk Demo", 0,0,640,480,2)
	renderer=SDL_CreateRenderer(window, -1,1)
	SDL_SetRenderDrawColor(renderer, 255,255,255,255)
	SDL_RenderClear(renderer);
	quit=0
	while(!quit){
		r=rand()*256
		g=rand()*256
		b=rand()*256
		printf("(%d,%d,%d)\n",r,g,b)
		SDL_SetRenderDrawColor(renderer,r,g,b,255);

		x1=rand()*640
		y1=rand()*480
		x2=rand()*640
		y2=rand()*480
		printf("(%d,%d,%d,%d)\n",x1,y1,x2,y2)
		SDL_RenderDrawLine(renderer,x1,y1,x2,y2)
		event=SDL_PollEvent()
		while(event!=0){
			t=SDL_GetEventType(event);
			if(t==256){
				quit=1
			}
			event=SDL_PollEvent()
		}
		SDL_RenderPresent(renderer)
		SDL_Delay(1)
	}

}
