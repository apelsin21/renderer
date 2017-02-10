#include <algorithm>
#include <string>
#include <iostream>

#include "glcontextparamtest.hpp"

using namespace std;

SCENARIO("GLContextParams can be sorted", "[GLContextParam]") {
	GIVEN("An unsorted vector") {
    vector<GLContextParam> unsorted = GetUnsortedContextVector();

		WHEN("we don't sort the vector using STL sort") {
      sort(unsorted.begin(), unsorted.end());

			THEN("the unsorted vector isn't equal to a sorted vector") {
        vector<GLContextParam> sorted = GetSortedContextVector();
				REQUIRE(unsorted != sorted);
			}
    }
		WHEN("we sort the vector using STL stable_sort") {
      stable_sort(unsorted.begin(), unsorted.end());

			THEN("the previously unsorted vector is equal to a hand-sorted vector") {
        vector<GLContextParam> sorted = GetSortedContextVector();
				REQUIRE(unsorted == sorted);
			}
    }
  }
}

SCENARIO("GLContextParams can be compared", "[GLContextParam]") {
	GIVEN("An OpenGL 2.1 context param") {
		const int major = 2, minor = 1, depth = 24;
		const bool core = false, gles = false, doubleBuffered = true;
  	GLContextParam param(major, minor, depth, core, gles, doubleBuffered);

		WHEN("we compare it with a default-constructed param") {
      const GLContextParam defaultConstructedParam;

			THEN("the OpenGL 2.1 context isn't equal to the default constructed context") {
				REQUIRE(param != defaultConstructedParam);
			}
			THEN("the OpenGL 2.1 context isn't less than the default constructed context") {
        const bool isLessThan = param < defaultConstructedParam;
				REQUIRE(isLessThan == false);
			}
			THEN("the OpenGL 2.1 context is greater than the default constructed context") {
				REQUIRE(param > defaultConstructedParam);
			}
		}
		WHEN("we compare it with an equal context param") {
      const GLContextParam equalParam(major, minor, depth, core, gles, doubleBuffered);

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
		const int major = 4, minor = 5, depth = 24;
		const bool core = true, gles = false, doubleBuffered = true;
  	GLContextParam param(major, minor, depth, core, gles, doubleBuffered);

		WHEN("we turn it into a string") {
			const string paramAsString = param.ToString();

			THEN("the string contains the correct data") {
				REQUIRE(paramAsString == "OpenGL 4.5 core, 24 depth bits, double buffered");
			}
		}
	}
	GIVEN("An OpenGL 3.0 compat profile context param") {
		const int major = 3, minor = 0, depth = 24;
		const bool core = false, gles = false, doubleBuffered = true;
  	GLContextParam param(major, minor, depth, core, gles, doubleBuffered);

		WHEN("we turn it into a string") {
			const string paramAsString = param.ToString();

			THEN("the string contains the correct data") {
				REQUIRE(paramAsString == "OpenGL 3.0 compat, 24 depth bits, double buffered");
			}
		}
	}
	GIVEN("An OpenGL ES 3.1 compat profile context param") {
		const int major = 3, minor = 1, depth = 24;
		const bool core = false, gles = true, doubleBuffered = true;
  	GLContextParam param(major, minor, depth, core, gles, doubleBuffered);

		WHEN("we turn it into a string") {
			const string paramAsString = param.ToString();

			THEN("the string contains the correct data") {
				REQUIRE(paramAsString == "OpenGL 3.1 ES compat, 24 depth bits, double buffered");
			}
		}
	}

	GIVEN("An OpenGL ES 2.1 core profile context param") {
		const int major = 2, minor = 1, depth = 24;
		const bool core = true, gles = true, doubleBuffered = true;
  	GLContextParam param(major, minor, depth, core, gles, doubleBuffered);

		WHEN("we turn it into a string") {
			const string paramAsString = param.ToString();

			THEN("the string contains the correct data") {
				REQUIRE(paramAsString == "OpenGL 2.1 ES core, 24 depth bits, double buffered");
			}
		}
	}
}
