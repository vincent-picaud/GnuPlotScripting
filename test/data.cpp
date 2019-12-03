#include "GnuPlotScripting/data.hpp"

#include <gtest/gtest.h>

using namespace GnuPlotScripting;

TEST(Data, uuid) { ASSERT_FALSE(Data_Uuid().as_string_view() == Data_Uuid().as_string_view()); }
