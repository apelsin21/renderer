#include <algorithm>
#include <string>
#include <iostream>

#include "glcontextparamtest.hpp"

using namespace std;

SCENARIO("GLContextParams can be sorted", "[GLContextParam]") {
	GIVEN("An unsorted vector") {
    vector<GLContextParam> unsorted = get_unsorted_context_vector();

		WHEN("we don't sort the vector using STL sort") {
			THEN("the unsorted vector isn't equal to a sorted vector") {
				REQUIRE(unsorted != get_sorted_context_vector());
			}
    }
		WHEN("we sort the vector using STL stable_sort") {
      stable_sort(unsorted.begin(), unsorted.end());

			THEN("the previously unsorted vector is equal to a hand-sorted vector") {
        vector<GLContextParam> sorted = get_sorted_context_vector();
				REQUIRE(unsorted == sorted);
			}
    }
  }
}

SCENARIO("GLContextParams can be compared", "[GLContextParam]") {
	GIVEN("An OpenGL 4.1 context param") {
  	GLContextParam param("test", 4, 1, false, false);

		WHEN("we compare it with a default-constructed param") {
      GLContextParam defaultConstructedParam;

			THEN("the OpenGL 4.1 context isn't equal to the default constructed context") {
				REQUIRE(param != defaultConstructedParam);
			}
			THEN("the OpenGL 4.1 context isn't less than the default constructed context") {
        const bool isLessThan = param < defaultConstructedParam;
				REQUIRE(isLessThan == false);
			}
			THEN("the OpenGL 4.1 context is greater than the default constructed context") {
				REQUIRE(param > defaultConstructedParam);
			}
		}
		WHEN("we compare it with an equal context param") {
      GLContextParam equalParam("test", param.major, param.minor, param.core, param.gles);

			THEN("the contexts are equal") {
				REQUIRE(param == equalParam);
			}
			THEN("no context is less") {
        const bool isLessThan = param < equalParam;
				REQUIRE(isLessThan == false);
			}
			THEN("no context is greater") {
        const bool isGreaterThan = param > equalParam;
				REQUIRE(isGreaterThan == false);
			}
		}
	}
}

SCENARIO("GLContextParams can be stringified", "[GLContextParam]") {

	GIVEN("An OpenGL 4.5 core profile context param") {
  	const GLContextParam param("test", 4, 5, true, false);

		WHEN("we turn it into a string") {
			const string paramAsString = param.to_string();

			THEN("the string contains the correct data") {
				REQUIRE(paramAsString == "OpenGL 4.5 core, 24 depth bits, double buffered, 800x600");
			}
		}
	}
	GIVEN("An OpenGL 3.0 compat profile context param") {
  	const GLContextParam param("test", 3, 0, false, false);

		WHEN("we turn it into a string") {
			const string paramAsString = param.to_string();

			THEN("the string contains the correct data") {
				REQUIRE(paramAsString == "OpenGL 3.0 compat, 24 depth bits, double buffered, 800x600");
			}
		}
	}
	GIVEN("An OpenGL ES 3.1 compat profile context param") {
  	const GLContextParam param("test", 3, 1, false, true);

		WHEN("we turn it into a string") {
			const string paramAsString = param.to_string();

			THEN("the string contains the correct data") {
				REQUIRE(paramAsString == "OpenGL 3.1 ES compat, 24 depth bits, double buffered, 800x600");
			}
		}
	}

	GIVEN("An OpenGL ES 2.1 core profile context param") {
  	const GLContextParam param("test", 2, 1, true, true);

		WHEN("we turn it into a string") {
			const string paramAsString = param.to_string();

			THEN("the string contains the correct data") {
				REQUIRE(paramAsString == "OpenGL 2.1 ES core, 24 depth bits, double buffered, 800x600");
			}
		}
	}
}
