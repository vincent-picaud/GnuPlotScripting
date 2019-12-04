test_array = [
  ['data_test','data_exe','data.cpp'],
  ['data_vector_test','data_vector_exe','data_vector.cpp'],
  ['export_as_test','export_as_exe','export_as.cpp'],
]

foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
		  test.get(2),
		  dependencies
 		  : [ GnuPlotScripting_dep, gtest_dep ]))
endforeach
