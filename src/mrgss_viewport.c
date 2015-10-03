#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/variable.h>
#include <mruby/value.h>
#include <mrgss.h>
#include <mrgss/mrgss-types.h>

/**
 * Viewport Object Constructor
 * @param mrb 
 * @param self
 * @return 
 */
static mrb_value
initialize(mrb_state *mrb, mrb_value self) {
    mrb_value rect;
    mrb_get_args(mrb, "o", &rect);
	if(mrgss_object_is_a(mrb, rect, "Rect")){
		mrgss_iv_create(mrb, self, "@rect", rect);
		mrgss_iv_create(mrb, self, "@children", mrb_ary_new (mrb));
		mrgss_iv_create(mrb, self, "@visible", mrb_true_value ());
		mrgss_iv_create (mrb, self,"@z", mrb_fixnum_value (0));
	}
	else{
		mrgss_raise(mrb, E_ARGUMENT_ERROR, "Expecting a MRGSS::Rect");
		return mrb_nil_value();
	}
	
    return self;
}

/**
 * z getter
 * @param mrb
 * @param self
 * @return 
 */
static mrb_value get_z(mrb_state *mrb, mrb_value self) {
    return mrgss_iv_get(mrb, self, "@z");
}

/**
 * visible getter
 * @param mrb
 * @param self
 * @return 
 */
static mrb_value get_visible(mrb_state *mrb, mrb_value self) {
    return mrgss_iv_get(mrb, self, "@visible");
}

/**
 * sorted getter
 * @param mrb
 * @param self
 * @return 
 */
static mrb_value get_sorted(mrb_state *mrb, mrb_value self) {
    return mrgss_iv_get(mrb, self, "@sorted");
}

/**
 * rect getter
 * @param mrb
 * @param self
 * @return 
 */
static mrb_value get_rect(mrb_state *mrb, mrb_value self) {
    return mrgss_iv_get(mrb, self, "@rect");
}


/**
 * z setter
 * @param mrb
 * @param self
 * @return 
 */
static mrb_value set_z(mrb_state *mrb, mrb_value self) {
    mrb_int val;
    mrb_get_args(mrb, "i", &val);
    mrgss_iv_create(mrb, self, "@z", mrb_fixnum_value(val));
    return self;
}



/**
 * visible setter
 * @param mrb
 * @param self
 * @return 
 */
static mrb_value set_visible(mrb_state *mrb, mrb_value self) {
    mrb_bool val;
    mrb_get_args(mrb, "b", &val);
    mrgss_iv_create(mrb, self, "@visible", mrb_bool_value(val));
    return self;
}

/**
 * sorted setter
 * @param mrb
 * @param self
 * @return 
 */
static mrb_value set_sorted(mrb_state *mrb, mrb_value self) {
    mrb_bool val;
    mrb_get_args(mrb, "b", &val);
    mrgss_iv_create(mrb, self, "@sorted", mrb_bool_value(val));
    return self;
}

/**
 * rect setter
 * @param mrb
 * @param self
 * @return 
 */
static mrb_value set_rect(mrb_state *mrb, mrb_value self) {
    mrb_value val;
    mrb_get_args(mrb, "o", &val);
	if(mrgss_object_is_a(mrb, val, "Rect")){
		mrgss_iv_create(mrb, self, "@z", val);
		return self;
	}
	else{
		mrgss_raise(mrb, E_ARGUMENT_ERROR, "Expecting a MRGSS::Rect");
		return mrb_nil_value();
	}

}

/**
 * Type initializer
 * @param mrb
 */
void mrgss_init_viewport(mrb_state *mrb) {
    struct RClass *type = mrgss_create_class(mrb, "Viewport");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "z", get_z, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "z=", set_z, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, type, "visible", get_visible, MRB_ARGS_NONE());
	mrb_define_method(mrb, type, "visible=", set_visible, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, type, "sorted", get_sorted, MRB_ARGS_NONE());
	mrb_define_method(mrb, type, "sorted=", set_sorted, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, type, "rect", get_rect, MRB_ARGS_NONE());
	mrb_define_method(mrb, type, "rect=", set_rect, MRB_ARGS_REQ(1));
}