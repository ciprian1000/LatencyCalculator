Latency Calculator

The project was created using cmake, for multiplatform distribution.

How to create VS solution:
1) Create a build directory:

mkdir build

2) Navigate to the build directory:

cd build

3) Invoke cmake:

cmake -G "Visual Studio 16 2019" ..

4) Open Project.sln in Visual Studio 2019
5) Manually set LatencyCalculator as the startup project

In Solution Explorer right click on the LatencyCalculator project and select "Set as Startup project"

6) Build and run the project.

Technologies used:
 - C++ 17 with standard libraries.
 - rapidjson for json parsing.
 - cmake as the build system.
 - googletest and googlemock are added to the project, but not completely setup and no test have been implemented due to the lack of time.
 
Basic architecture:
 - expertake::LatencyCalculator is the brain of the project and owns all the components needed to make it work. It does most of the work on a separated thread with the use of an async function.
 - util.h and util.cpp are files containing free functions used for conversion and validation of data.
 - expertake::InterfaceController is a class responsible for the printing and option selection of the menu.
 - expertake::DataLoader is a utility class used to open files and read their content. No data parsing happens in this class.
 - expertake::DailyData is a data class corresponding to one day of requests. It is given the contents of a .json file and it uses rapidjson to parse and interpret the contents before populating it's fields.
 - expertake::ServiceData is a data class containing the acumulated data for a service.
 
Potential improvements:
 - Split expertake::LatencyCalculator into several smaller and more focused classes.
 - A better interface for selecting start and end dates.
 - More data validation, including for the data in the .json files.
 - Write unit tests.
 - Add documentation.
 
