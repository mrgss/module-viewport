#assert('C and Ruby Extension Example 1') do
#  CRubyExtension.respond_to? :c_method
#end
#
#assert('C and Ruby Extension Example 2') do
#  CRubyExtension.respond_to? :ruby_method
#end

assert("Viewport initialize") do
	viewp = MRGSS::Viewport.new(MRGSS::Rect.new(0,0,25,25))
    viewp.nil?
end
