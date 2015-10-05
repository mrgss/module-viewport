/* 
 * File:   mrgss-viewport.h
 * Author: FedeQ
 *
 * Created on 3 de octubre de 2015, 00:16
 */

#ifndef MRGSS_VIEWPORT_H
#define MRGSS_VIEWPORT_H

#include <mruby.h>

#ifdef __cplusplus
extern "C" {
#endif
    void mrb_mrgss_viewport_gem_init(mrb_state *mrb);
    void mrgss_init_viewport(mrb_state *mrb);
    
    mrb_value mrgss_viewport_new(mrb_state *mrb, mrb_int x, mrb_int y, mrb_int w, mrb_int h);
    
#ifdef __cplusplus
}
#endif

#endif /* MRGSS_TEXTURE_H */
