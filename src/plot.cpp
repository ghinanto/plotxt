// This macro can be used directly with ROOT interpreter or compiled with:
// `root-config --cflags --libs` ROOT application is required to make use of
// graphics

#include "TGraph.h"
//#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// namespace po = boost::program_options;

// Returns the column names line, i.e. the last line of the header.
// After calling this method the stream is ready to read data.
std::string read_header(std::istream& file_in, int header_lines = 1);
// Returns the column names line, i.e. the last line of the header.
std::string read_header(std::string const& file_name, int header_lines = 1);

// Returns a vector containing the elements separated by 'sep' in 'line'
std::vector<std::string> split(std::string const& line, char const sep = ' ');

// Returns the value of the 'index' element in a vector of strings representing
// numbers
// This is where conversion from string to value happens.
int get_line_element(std::vector<std::string> const& line_vec, int index);

// Returns a vector containg values read from the 'index' column of
// 'file_in_name'
template<class T>
std::vector<T> get_column(std::string const& file_in_name, int index);
template<class T>
std::vector<T> get_column(std::string const& file_in_name,
                          std::string const& name);

// Plots column 'x_index' and 'y_index' as x and y axis.
void plot(std::string const& data_file_in_name, int x_index, int y_index,
          Option_t* draw_options = "AL")
{
  std::vector<int> x_axis = get_column<int>(data_file_in_name, x_index);
  std::vector<int> y_axis = get_column<int>(data_file_in_name, y_index);

  auto gr = new TGraph(x_axis.size(), x_axis.data(), y_axis.data());
  gr->Draw(draw_options);
}

void plot(std::string const& data_file_in_name, std::string const& x_name,
          std::string const& y_name, Option_t* draw_options = "AL")
{
  std::vector<int> x_axis = get_column<int>(data_file_in_name, x_name);
  std::vector<int> y_axis = get_column<int>(data_file_in_name, y_name);

  auto gr = new TGraph(x_axis.size(), x_axis.data(), y_axis.data());
  gr->Draw(draw_options);
}

std::string read_header(std::istream& file_in, int header_lines)
{
  std::string line_str;
  // Label line is the last line of the header
  do
    std::getline(file_in, line_str);
  while (header_lines > 1);
  return line_str;
}

std::string read_header(std::string const& file_name, int header_lines)
{
  std::ifstream file_in(file_name);
  return read_header(file_in, header_lines);
}

std::vector<std::string> split(std::string const& line, char const sep)
{
  std::istringstream line_in(line);
  std::vector<std::string> line_vector{};
  std::string line_element{};

  while (std::getline(line_in, line_element, sep))
    line_vector.push_back(line_element);
  return line_vector;
}

// This is where conversion from string to value happens.
int get_line_element(std::vector<std::string> const& line_vec, int index)
{
  return std::stoi(line_vec.at(index));
}

template<class T>
std::vector<T> get_column(std::string const& file_in_name, int index)
{
  std::ifstream file_in(file_in_name);
  read_header(file_in);

  std::vector<T> column{};
  std::string line_str;
  while (std::getline(file_in, line_str)) {
    T val = get_line_element(split(line_str), index);
    column.push_back(val);
  }
  return column;
}

template<class T>
std::vector<T> get_column(std::string const& file_in_name,
                          std::string const& name)
{
  auto labels   = split(read_header(file_in_name));
  auto label_it = std::find(labels.begin(), labels.end(), name);
  if (label_it == labels.end())
    throw std::invalid_argument("Column name not found in file" + file_in_name);

  int index = std::distance(labels.begin(), label_it);
  // auto column = get_column<T>(file_in_name, index);

  return get_column<T>(file_in_name, index);
}

// Required to compile with g++ and `root-config --cflags --libs` option.
#ifndef __CINT__
#  include "TApplication.h"
#  include <algorithm>
#  include <iomanip>
std::string usage =
    // clang-format off
      static_cast<std::string>("Usage:") // Cast needed to use the operator+
      + "\n  plot_data -h/--help" + "\n  plot_data <data_file> -l/--list-column-names"
      + "\n  plot_data <data_file> X_COLUMN_INDEX Y_COLUMN_INDEX [DRAW_OPTIONS] [-f/--write-to-file FILE_NAME]"
      + "\n  plot_data <data_file> X_COLUMN_NAME Y_COLUMN_NAME [DRAW_OPTIONS] [-f/--write-to-file FILE_NAME]";
// clang-format on
std::string options =
    // clang-format off
      static_cast<std::string>("Options:")
      + "\n  <data_file>                     The name of file containing X and Y data arranged in columns. Include its path if necessary."
      + "\n  X_COLUMN_INDEX, Y_COLUMN_INDEX  The indexes of columns in <data_file> corresponding to x and y axes."
      + "\n  X_COLUMN_NAME, Y_COLUMN_NAME    The names of columns in <data_file> corresponding to x and y axes. The line of column names must immediately preceed the actual data."
      + "\n  DRAW_OPTIONS                    Options to be used by ROOT Draw function called by the plot. Check the ROOT website for documentation."
      + "\n  -h                              See this message."
      + "\n  -l                              List the names of columns of <data_file>. The line of column names must immediately preceed the actual data."
      + "\n  -f FILE_NAME                    Write axes data to plain text file arranged in column. Can also act as flag and a default file name will be used.";
// clang-format on

void exit_usage(std::ostream& out = std::cout)
{
  out << usage << std::endl;
  std::exit(-1);
}

void exit_help(std::ostream& out = std::cout)
{
  out << usage << "\n\n" << options << std::endl;
  std::exit(-1);
}

void StandaloneApplication(int argc, char** argv)
{
  // std::cout << argc;
  if (argc == 1 || argc > 5)
    exit_usage();
  // std::cout << argv[0] << " " << argv[1];

  std::string first_arg = argv[1];
  if (first_arg == "-h" || first_arg == "--help")
    exit_help();

  // argv[1] is <data_file>
  if (argc == 2)
    exit_usage();

  std::string second_arg = argv[2];
  if (second_arg == "-l" || second_arg == "--list-column-names") {
    auto label_vec = split(read_header(argv[1]));
    std::ostringstream labels;

    std::cout << "\nColumn: ";
    int column_index{0};
    std::for_each(label_vec.begin(), label_vec.end(),
                  [&column_index, &labels](std::string const& label) {
                    labels << label << ' ';
                    std::cout << std::setw(label.size() + 1) << column_index++;
                  });

    std::cout << "\nName: " << labels.str() << '\n';
    std::exit(EXIT_SUCCESS);
  }

  // argv[2] and argv[3] are x, y indexes or x, y names
  if (argc < 4)
    exit_usage;

  // If present, argv[4] is DRAW_OPTIONS
  Option_t* draw_options = "AL";
  if (argc == 5)
    draw_options = argv[4];

  // Try to interpret strings as numbers, i.e. column indexes.
  // If it fails, the user passed column names.
  try {
    plot(first_arg, std::stoi(second_arg),
         std::stoi(static_cast<std::string>(argv[3])), draw_options);
  } catch (std::invalid_argument& ia) {
    plot(first_arg, second_arg, static_cast<std::string>(argv[3]),
         draw_options);
  } catch (...) {
    std::cerr << "\nSomething went wrong during plot" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

// This is the standard "main" of C++ starting
// a ROOT application
int main(int argc, char** argv)
{
  TApplication app("ROOT Application", 0,
                   {}); // Do not let ROOT receive command line arguments.
  StandaloneApplication(argc, argv);
  app.Run();
  return 0;
}
#endif