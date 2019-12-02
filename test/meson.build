test_array = [['hello_test','hello_exe','hello.cpp']]

foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
		  test.get(2),
		  dependencies
 		  : [ GnuPlotScripting_dep, gtest_dep ]))
endforeach
