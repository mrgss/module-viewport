#include <mruby.h>
#include <mrgss.h>
#include <mrgss/mrgss-types.h>
#include <mrgss/mrgss-viewport.h>

void
mrb_mrgss_viewport_gem_init(mrb_state *mrb) {
    mrgss_init_viewport(mrb);
}

void
mrb_mrgss_viewport_gem_final(mrb_state* mrb) {
    /* finalizer */
}

mrb_value mrgss_viewport_new(mrb_state *mrb, mrb_int x, mrb_int y, mrb_int w, mrb_int h) {
    mrb_value param[] = {mrb_fixnum_value(x), mrb_fixnum_value(y),mrb_fixnum_value(w),mrb_fixnum_value(h)};
    mrb_value rect = mrgss_obj_new(mrb, "Rect", 4, param);
    return mrgss_obj_new(mrb, "Viewport", 1, &rect);
}