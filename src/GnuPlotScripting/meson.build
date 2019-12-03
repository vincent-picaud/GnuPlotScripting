GnuPlotScripting_headers = [
  'hello.hpp',
  'script.hpp',
  'data.hpp',
  'detection_idiom.hpp',
  'data_std_vector.hpp',
]
GnuPlotScripting_sources = [
  'hello.cpp',
  'script.cpp',
  'data.cpp',
]

GnuPlotScripting_lib = library('GnuPlotScripting',
			       include_directories : inc,
			       dependencies : [fmt_dep],
			       install : true,
			       sources: [GnuPlotScripting_headers,GnuPlotScripting_sources])

GnuPlotScripting_dep = declare_dependency(include_directories : inc,
					  dependencies : [fmt_dep],
					  link_with : GnuPlotScripting_lib)

install_headers(GnuPlotScripting_headers,
		subdir : 'GnuPlotScripting')

