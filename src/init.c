#include <mruby.h>
#include <mrgss/mrgss-viewport.h>

void
mrb_mrgss_viewport_gem_init(mrb_state *mrb) {
    mrgss_init_viewport(mrb);
}

void
mrb_mrgss_viewport_gem_final(mrb_state* mrb) {
   /* finalizer */
}