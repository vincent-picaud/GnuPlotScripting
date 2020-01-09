test_array = [
  ['data_test','data_exe','data.cpp'],
  ['data_vector_test','data_vector_exe','data_vector.cpp'],
  ['export_as_test','export_as_exe','export_as.cpp'],
  ['global_config_test','global_config_exe','global_config.cpp'],
  ['data_supervised_test','data_supervised_exe','data_supervised.cpp'],
]

foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
		  test.get(2),
		  dependencies
 		  : [ GnuPlotScripting_dep, gtest_dep ]))
endforeach
