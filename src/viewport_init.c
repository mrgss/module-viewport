#include <mruby.h>
#include <mrgss/mrgss.h>
#include <mrgss/mrgss_viewport.h>

void
mrb_mrgss_viewport_gem_init(mrb_state *mrb) {
    mrgss_viewport_init(mrb);
}

void
mrb_mrgss_viewport_gem_final(mrb_state* mrb) {
    /* finalizer */
}
