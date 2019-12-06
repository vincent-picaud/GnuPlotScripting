GnuPlotScripting_headers = [
  'hello.hpp',
  'script.hpp',
  'data.hpp',
  'detection_idiom.hpp',
  'data_vector.hpp',
  'data_ascii.hpp',
  'export_as.hpp',
  'global_config.hpp',
  'GnuPlotScripting.hpp',
  'script_file_mode_enum.hpp',
  'script_pipe_mode_enum.hpp',
]
GnuPlotScripting_sources = [
  'hello.cpp',
  'script.cpp',
  'data.cpp',
  'export_as.cpp',
  'global_config.cpp',
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

