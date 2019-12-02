GnuPlotScripting_headers = ['hello.hpp']
GnuPlotScripting_sources = ['hello.cpp']

GnuPlotScripting_lib = library('GnuPlotScripting',
				include_directories : inc,
				install : true,
				sources: [GnuPlotScripting_headers,GnuPlotScripting_sources])

GnuPlotScripting_dep = declare_dependency(include_directories : inc,
					   link_with : GnuPlotScripting_lib)

install_headers(GnuPlotScripting_headers,
		 subdir : 'GnuPlotScripting')

