MRuby::Build.new do |conf|
  toolchain :gcc
  conf.gembox 'default'
  conf.gem :github => 'mrgss/module-core'
  conf.gem :github => 'mrgss/module-types'
  conf.gem '../module-viewport'

end
