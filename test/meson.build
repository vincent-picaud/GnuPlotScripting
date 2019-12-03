test_array = [
  ['data_test','data_exe','data.cpp'],
]

foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
		  test.get(2),
		  dependencies
 		  : [ GnuPlotScripting_dep, gtest_dep ]))
endforeach
