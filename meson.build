project('GnuPlotScripting', 'cpp',
	version : '0.0.1',
	default_options : ['cpp_std=c++17'])

add_project_link_arguments(['-lstdc++fs'], language : 'cpp')

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_main_dep')

fmt_proj = subproject('fmt')
fmt_dep = fmt_proj.get_variable('fmt_dep')

subdir('src')
subdir('test')
subdir('examples')
