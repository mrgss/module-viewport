#include <SDL/SDL.h>
#include <kazmath/kazmath.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/variable.h>
#include <mrgss/mrgss.h>
#include <mrgss/mrgss_viewport.h>

static kmMat4 matrices[3];

static void viewport_free(mrb_state *mrb, void *p) {
    if (p) {
        mrb_free(mrb, p);
    }
}
/**
 * free function structure
 */
struct mrb_data_type const mrbal_viewport_data_type = {"Viewport", viewport_free};

/**
 * 
 * @param mrb
 * @param self
 * @return 
 */
static mrb_value
initialize(mrb_state *mrb, mrb_value self) {
    mrb_value mrbrect;
    mrgss_viewport *viewport;
    DATA_TYPE(self) = &mrbal_viewport_data_type;
    DATA_PTR(self) = NULL;
    mrb_get_args(mrb, "o", &mrbrect);
    viewport = mrb_malloc(mrb, sizeof (mrgss_viewport));
    viewport->rect = DATA_PTR(mrbrect);
    viewport->sorted = TRUE;
    viewport->visible = TRUE;
    viewport->z = 0;
    mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "children"), mrb_ary_new(mrb));
    mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@rect"), mrbrect);
    DATA_PTR(self) = viewport;
    return self;
}

static mrb_value get_rect(mrb_state *mrb, mrb_value self) {
    return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@rect"));
}

static mrb_value set_rect(mrb_state *mrb, mrb_value self) {
    mrb_value nrect;
    mrgss_viewport *viewport = DATA_PTR(self);
    mrb_get_args(mrb, "o", &nrect);
    mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@rect"), nrect);
    viewport->rect = DATA_PTR(nrect);
    return nrect;
}

static mrb_value get_visible(mrb_state *mrb, mrb_value self) {
    mrgss_viewport *viewport = DATA_PTR(self);
    return mrb_bool_value(viewport->visible);
}

static mrb_value set_visible(mrb_state *mrb, mrb_value self) {
    mrb_bool nvisible;
    mrgss_viewport *viewport = DATA_PTR(self);
    mrb_get_args(mrb, "b", &nvisible);
    viewport->visible = nvisible;
    return mrb_bool_value(nvisible);
}

static mrb_value get_z(mrb_state *mrb, mrb_value self) {
    mrgss_viewport *viewport = DATA_PTR(self);
    return mrb_fixnum_value(viewport->z);
}

static mrb_value set_z(mrb_state *mrb, mrb_value self) {
    mrb_int nz;
    mrgss_viewport *viewport = DATA_PTR(self);
    mrb_get_args(mrb, "i", &nz);
    viewport->z = nz;
    return mrb_fixnum_value(nz);
}

/**
 * Ruby Type Initializer
 */
void mrgss_viewport_init(mrb_state *mrb) {
    struct RClass *viewport = mrb_define_class_under(mrb, mrgss_module(), "Viewport", mrb->object_class);
    mrb_define_method(mrb, viewport, "initialize", initialize, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, viewport, "rect", get_rect, MRB_ARGS_NONE());
    mrb_define_method(mrb, viewport, "rect=", set_rect, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, viewport, "visible", get_visible, MRB_ARGS_NONE());
    mrb_define_method(mrb, viewport, "visible=", set_visible, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, viewport, "z", get_z, MRB_ARGS_NONE());
    mrb_define_method(mrb, viewport, "z=", set_z, MRB_ARGS_REQ(1));
    MRB_SET_INSTANCE_TT(viewport, MRB_TT_DATA);
}

/**
 * @param mrb
 * @param viewport
 * @param child
 */
void viewport_add_children(mrb_state *mrb, mrb_value viewport, mrb_value child) {
    mrgss_viewport *viewp = DATA_PTR(viewport);
    int ai = mrb_gc_arena_save(mrb);
    mrb_value children = mrb_iv_get(mrb, viewport, mrb_intern_lit(mrb, "children"));
    mrb_ary_push(mrb, children, child);
    mrb_gc_arena_restore(mrb, ai);
    viewp->sorted = FALSE;
}

void viewport_remove_children(mrb_state *mrb, mrb_value viewport, mrb_value child) {
    mrb_value children = mrb_iv_get(mrb, viewport, mrb_intern_lit(mrb, "children"));
    mrb_int size = mrb_ary_len(mrb, children);
    for (int i = size - 1; i >= 0; --i) {
        mrb_value drawable = mrb_ary_entry(children, i);
        if (mrb_obj_equal(mrb, drawable, child)) {
            drawable = mrb_nil_value();
        }
    }
}

/**
 * Sort sprites by z
 * @param first
 * @param second
 * @return 
 */
//static int zcompare(const void * first, const void * second) {
//    mrgss_sprite* a = DATA_PTR(*(mrb_value*) first);
//    mrgss_sprite* b = DATA_PTR(*(mrb_value*) second);
//    if (a->z > b->z) {
//        return 1;
//    } else if (a->z < b->z) {
//        return -1;
//    } else {
//        return 0;
//    }
//}

/**
 * 
 * @param matrices
 * @param rect
 */
void create_matrices(kmMat4 matrices[], SDL_Rect* rect) {
    kmMat4Identity(&matrices[0]);
    kmMat4Identity(&matrices[1]);
    kmMat4OrthographicProjection(&matrices[2], 0.0f, rect->w, rect->h, 0.0f, 0.0f, 1.0f);
}

/**
 *
 */
void mrgss_viewport_draw(mrb_state *mrb, mrb_value viewport) {
    mrb_value mrbchildren = mrb_iv_get(mrb, viewport, mrb_intern_lit(mrb, "children"));
    mrgss_viewport *viewp = DATA_PTR(viewport);
    int i = 0;
    SDL_Rect *rect = viewp->rect;
    if (viewp->visible) {
        if (!viewp->sorted) {
//            struct RArray* children = DATA_PTR(mrbchildren);
            //SDL_qsort(children->ptr, children->len, sizeof (mrb_value), zcompare);
            viewp->sorted = TRUE;
        }
        create_matrices(matrices, rect);
        for (i = 0; i < mrb_ary_len (mrb, mrbchildren); i++) {
            draw_sprite(mrb, mrb_ary_entry(mrbchildren, i), matrices);
        }
    }
}