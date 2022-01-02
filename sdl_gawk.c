#include <stddef.h>
#include <stdio.h>
#include <sys/stat.h>
#include <SDL2/SDL.h>
#include <gmp.h>
#include <gawkapi.h>
int plugin_is_GPL_compatible;

static gawk_api_t * api;
static awk_ext_id_t ext_id;
static char *ext_version = NULL; /* or ... = "some string" */
awk_value_t * gawk_SDL_Init (int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo);
awk_value_t * gawk_SDL_CreateWindow (int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo);
awk_value_t * gawk_SDL_CreateRenderer(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo);
awk_value_t * gawk_SDL_RenderDrawLine(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo);
awk_value_t * gawk_SDL_SetRenderDrawColor(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo);
awk_value_t * gawk_SDL_RenderClear(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo);
awk_value_t * gawk_SDL_RenderPresent(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo);
awk_value_t * gawk_SDL_Delay(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo);
awk_value_t * gawk_SDL_FreeEvent(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo);
awk_value_t * gawk_SDL_GetEventType(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo);
awk_value_t * gawk_SDL_PollEvent(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo);
static awk_ext_func_t func_table[] = {
	{ "SDL_Init", gawk_SDL_Init, 0,0,0,NULL },
	{ "SDL_CreateWindow", gawk_SDL_CreateWindow, 6,6,0,NULL },
  { "SDL_CreateRenderer", gawk_SDL_CreateRenderer, 3,3,0,NULL},
  { "SDL_SetRenderDrawColor", gawk_SDL_SetRenderDrawColor, 5,5,0,NULL},

  { "SDL_RenderDrawLine", gawk_SDL_RenderDrawLine, 5,5,0,NULL},
  { "SDL_RenderClear", gawk_SDL_RenderClear, 1,1,0,NULL},
  { "SDL_Delay", gawk_SDL_Delay, 1,1,0,NULL},
  { "SDL_RenderPresent", gawk_SDL_RenderPresent, 1,1,0,NULL},
  { "SDL_FreeEvent", gawk_SDL_FreeEvent, 1,1,0,NULL},
  { "SDL_GetEventType", gawk_SDL_GetEventType, 1,1,0,NULL},
  { "SDL_PollEvent", gawk_SDL_PollEvent, 0,0,0,NULL},

  
};
//awk_bool_t my_init();

static awk_bool_t (*init_func)(void) = NULL;



dl_load_func(func_table, a, "");


/* My Code */
awk_value_t * ptr_to_awk(void * ptr, awk_value_t *result){
  double d;
  memcpy(&d,&ptr,sizeof(void *));
  return make_number(d,result);
}
void * awk_to_ptr( awk_value_t * value){
  void * ptr;
  memcpy(&ptr,&(value->num_value),sizeof(void *));
  return ptr;
  
}
awk_value_t * gawk_SDL_Init (int num_actual_args,awk_value_t *result, struct awk_ext_func *finfo){
  return make_number((double)SDL_Init(SDL_INIT_EVERYTHING),result);
}
awk_value_t * gawk_SDL_CreateWindow (int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){
  SDL_Window * window;
  awk_value_t container;
  get_argument (0, AWK_STRING, &container);
  char * title = container.str_value.str;
  get_argument (1, AWK_NUMBER, &container);
  int x=container.num_value;
  get_argument (2, AWK_NUMBER, &container);
  int y=container.num_value;
  get_argument (3, AWK_NUMBER, &container);
  int w=container.num_value;
  get_argument (4, AWK_NUMBER, &container);
  int h=container.num_value;
  get_argument (5, AWK_NUMBER, &container);
  uint32_t flags=container.num_value;
  window=SDL_CreateWindow(title, x, y, w, h, flags);
  return ptr_to_awk(window,result);
}

awk_value_t * gawk_SDL_CreateRenderer(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){
  awk_value_t container;

  get_argument (0, AWK_NUMBER, &container);
  SDL_Window * window=awk_to_ptr(&container);
  get_argument (1, AWK_NUMBER, &container);
  int index=container.num_value;
  get_argument (2, AWK_NUMBER, &container);
  uint32_t flags=container.num_value;
  SDL_Renderer * renderer=SDL_CreateRenderer(window, index, flags); 
  return ptr_to_awk(renderer,result);
}


awk_value_t * gawk_SDL_RenderDrawLine(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){
  awk_value_t container;
  get_argument (0, AWK_NUMBER, &container);
  SDL_Renderer * renderer = awk_to_ptr(&container);
  get_argument (1, AWK_NUMBER, &container);
  int x1=container.num_value;
  get_argument (2, AWK_NUMBER, &container);
  int y1=container.num_value;
  get_argument (3, AWK_NUMBER, &container);
  int x2=container.num_value;
  get_argument (4, AWK_NUMBER, &container);
  int y2=container.num_value;
  return make_number((double)SDL_RenderDrawLine(renderer, x1, y1, x2, y2),result);
}


awk_value_t * gawk_SDL_SetRenderDrawColor(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){
  awk_value_t container;

  get_argument (0, AWK_NUMBER, &container);
  SDL_Renderer * renderer = awk_to_ptr(&container);
  get_argument (1, AWK_NUMBER, &container);
  uint8_t r=container.num_value;
  get_argument (2, AWK_NUMBER, &container);
  uint8_t g=container.num_value;
  get_argument (3, AWK_NUMBER, &container);
  uint8_t b=container.num_value;
  get_argument (4, AWK_NUMBER, &container);
  uint8_t a=container.num_value;

  return make_number((double)SDL_SetRenderDrawColor(renderer, r,g,b,a),result);


}
 
awk_value_t * gawk_SDL_RenderClear(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){

  awk_value_t container;
  get_argument (0, AWK_NUMBER, &container);
  SDL_Renderer * renderer = awk_to_ptr(&container);
  return make_number((double)SDL_RenderClear(renderer),result);
}
awk_value_t * gawk_SDL_RenderPresent(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){

  awk_value_t container;
  get_argument (0, AWK_NUMBER, &container);
  SDL_Renderer * renderer = awk_to_ptr(&container);
  SDL_RenderPresent(renderer);
  return result;

}
awk_value_t * gawk_SDL_Delay(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){
  awk_value_t container;
  get_argument (0, AWK_NUMBER, &container);
  SDL_Delay((unsigned int)container.num_value);
  return result;

}
/*awk_value_t * gawk_SDL_CheckQuit(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){
  SDL_Event e;
  while(SDL_PollEvent(&e)){
    if(e.type==SDL_QUIT){
      printf("quit\n");
      return make_number(1, result);
    }
  }
  
  return make_number(0, result);
}*/


awk_value_t * gawk_SDL_PollEvent(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){
  SDL_Event * e=malloc(sizeof(SDL_Event));
  if(SDL_PollEvent(e)){

    return ptr_to_awk(e,result);
  }
  return ptr_to_awk(NULL,result);
  
}

awk_value_t * gawk_SDL_GetEventType(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){
  awk_value_t container;
  get_argument (0, AWK_NUMBER, &container);
  SDL_Event * e=awk_to_ptr(&container);
  return make_number(e->type,result);
  
}

awk_value_t * gawk_SDL_FreeEvent(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){
  awk_value_t container;
  get_argument (0, AWK_NUMBER, &container);
  free(awk_to_ptr(&container));
  return result;
  
}