/* 
 * File:   mrgss_viewport.h
 * Author: manuel
 *
 * Created on 8 de octubre de 2015, 16:29
 */

#ifndef MRGSS_VIEWPORT_H
#define	MRGSS_VIEWPORT_H

#include <SDL/SDL.h>
#include <mruby.h>

#ifdef	__cplusplus
extern "C" {
#endif

    void mrgss_viewport_init(mrb_state *mrb);
    
    typedef struct viewport {
        SDL_Rect *rect;
        mrb_bool visible;
        mrb_bool sorted;
        mrb_int z;
    } mrgss_viewport;


#ifdef	__cplusplus
}
#endif

#endif	/* MRGSS_VIEWPORT_H */

