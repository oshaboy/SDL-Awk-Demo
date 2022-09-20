#include <stddef.h>
#include <stdio.h>
#include <sys/stat.h>
#include <SDL2/SDL.h>
#include <gmp.h>
#include <gawkapi.h>
#include <mpfr.h>
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
  { "SDL_GetEventType", gawk_SDL_GetEventType, 1,1,0,NULL},
  { "SDL_PollEvent", gawk_SDL_PollEvent, 0,0,0,NULL},

  
};

static awk_bool_t (*init_func)(void) = NULL;



dl_load_func(func_table, a, "");


/* My Code */
awk_value_t * ui_to_awk(unsigned long int value, awk_value_t *result){
  mpz_t * d = get_mpz_ptr();
  mpz_set_ui(*d,(unsigned long int)value);
  return make_number_mpz(d, result);
}
awk_value_t * ptr_to_awk(void * ptr, awk_value_t *result){
  return ui_to_awk((unsigned long int ) ptr,result);
}
unsigned long int awk_to_ui(awk_value_t * value){
  switch (value->num_type){
    case AWK_NUMBER_TYPE_DOUBLE:
      return (unsigned int)value->num_value;
    case AWK_NUMBER_TYPE_MPFR:
    {
      mpfr_t * num = value->num_ptr;;
      return mpfr_get_ui(*num,MPFR_RNDN);
    }
    case AWK_NUMBER_TYPE_MPZ:
    {
      mpz_t * num = value->num_ptr;
      return mpz_get_ui(*num);
    }
  }
}
void * awk_to_ptr( awk_value_t * value){
  return (void *)awk_to_ui(value);
  
}
awk_value_t * gawk_SDL_Init (int num_actual_args,awk_value_t *result, struct awk_ext_func *finfo){
  return ui_to_awk(SDL_Init(SDL_INIT_EVERYTHING),result);
}
awk_value_t * gawk_SDL_CreateWindow (int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){
  SDL_Window * window;
  awk_value_t container;
  get_argument (0, AWK_STRING, &container);
  char * title = container.str_value.str;
  get_argument (1, AWK_NUMBER, &container);
  int x=awk_to_ui(&container);
  get_argument (2, AWK_NUMBER, &container);
  int y=awk_to_ui(&container);
  get_argument (3, AWK_NUMBER, &container);
  int w=awk_to_ui(&container);
  get_argument (4, AWK_NUMBER, &container);
  int h=awk_to_ui(&container);
  get_argument (5, AWK_NUMBER, &container);
  uint32_t flags=awk_to_ui(&container);
  window=SDL_CreateWindow(title, x, y, w, h, flags);
  return ptr_to_awk(window,result);
}

awk_value_t * gawk_SDL_CreateRenderer(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){
  awk_value_t container;

  get_argument (0, AWK_NUMBER, &container);
  SDL_Window * window=awk_to_ptr(&container);
  get_argument (1, AWK_NUMBER, &container);
  int index=awk_to_ui(&container);
  get_argument (2, AWK_NUMBER, &container);
  uint32_t flags=awk_to_ui(&container);
  SDL_Renderer * renderer=SDL_CreateRenderer(window, index, flags); 
  return ptr_to_awk(renderer,result);
}


awk_value_t * gawk_SDL_RenderDrawLine(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){
  awk_value_t container;
  get_argument (0, AWK_NUMBER, &container);
  SDL_Renderer * renderer = awk_to_ptr(&container);
  get_argument (1, AWK_NUMBER, &container);
  int x1=awk_to_ui(&container);
  get_argument (2, AWK_NUMBER, &container);
  int y1=awk_to_ui(&container);
  get_argument (3, AWK_NUMBER, &container);
  int x2=awk_to_ui(&container);
  get_argument (4, AWK_NUMBER, &container);
  int y2=awk_to_ui(&container);
  return ui_to_awk(SDL_RenderDrawLine(renderer, x1, y1, x2, y2),result);
}


awk_value_t * gawk_SDL_SetRenderDrawColor(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){
  awk_value_t container;

  get_argument (0, AWK_NUMBER, &container);
  SDL_Renderer * renderer = awk_to_ptr(&container);
  get_argument (1, AWK_NUMBER, &container);
  uint8_t r=awk_to_ui(&container);
  get_argument (2, AWK_NUMBER, &container);
  uint8_t g=awk_to_ui(&container);
  get_argument (3, AWK_NUMBER, &container);
  uint8_t b=awk_to_ui(&container);
  get_argument (4, AWK_NUMBER, &container);
  uint8_t a=awk_to_ui(&container);

  return ui_to_awk(SDL_SetRenderDrawColor(renderer, r,g,b,a),result);


}
 
awk_value_t * gawk_SDL_RenderClear(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){

  awk_value_t container;
  get_argument (0, AWK_NUMBER, &container);
  SDL_Renderer * renderer = awk_to_ptr(&container);
  return ui_to_awk(SDL_RenderClear(renderer),result);
}
awk_value_t * gawk_SDL_RenderPresent(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){

  awk_value_t container;
  get_argument (0, AWK_NUMBER, &container);
  SDL_Renderer * renderer = awk_to_ptr(&container);
  SDL_RenderPresent(renderer);
  return ui_to_awk(0,result);

}
awk_value_t * gawk_SDL_Delay(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){
  awk_value_t container;
  get_argument(0,AWK_NUMBER, &container);
  SDL_Delay(awk_to_ui(&container););
  return ui_to_awk(0,result);;

}



awk_value_t * gawk_SDL_PollEvent(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){
  SDL_Event * e=gawk_malloc(sizeof(SDL_Event));
  if(SDL_PollEvent(e)){

    return ptr_to_awk(e,result);
  }
  return ptr_to_awk(NULL,result);
  
}

awk_value_t * gawk_SDL_GetEventType(int num_actual_args, awk_value_t *result, struct awk_ext_func *finfo){
  awk_value_t container;
  get_argument (0, AWK_NUMBER, &container);
  SDL_Event * e=awk_to_ptr(&container);
  return ui_to_awk(e->type,result);
  
}

