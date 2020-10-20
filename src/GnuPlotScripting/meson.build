GnuPlotScripting_headers = [
  'GnuPlotScripting.hpp',
  'array_2.hpp',
  'data.hpp',
  'data_ascii.hpp',
  'data_array_2.hpp',
  'data_supervised.hpp',
  'data_vector.hpp',
  'detection_idiom.hpp',
  'export_as.hpp',
  'global_config.hpp',
  'script.hpp',
  'script_file_mode_enum.hpp',
  'script_pipe_mode_enum.hpp',
]
GnuPlotScripting_sources = [
  'data.cpp',
  'data_array_2.cpp',
  'export_as.cpp',
  'global_config.cpp',
  'script.cpp',
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

