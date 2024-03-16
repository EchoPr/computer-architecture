#include <iostream>
#include <sstream>
#include <exception>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Window.h>
#include <Graph_lib/Simple_window.h>

#include "logic.h"
#include "logic_shapes.h"


int main ()
try
{
  int win_w = 600;
  int win_h = 400;
  Graph_lib::Point lt{ Graph_lib::x_max()/2 - win_w/2, Graph_lib::y_max()/2 - win_h/2 };
  Simple_window win{ lt, win_w, win_h, "Scheme of Logic Elements" };
  //win.wait_for_button();

  using namespace Logic;

  Source src1;
  Source src2;
  Source src3;
  Source src4;

  Xor xor_lhs{ Out_state::inverted };
  Xor xor_rhs{ Out_state::inverted };
  Xor xor_res{ Out_state::inverted };


  src1 >> xor_lhs;
  src2 >> xor_lhs;
  src3 >> xor_rhs;
  src4 >> xor_rhs;

  xor_lhs >> xor_res;
  xor_rhs >> xor_res;


  //
  SchemeShape scheme{ Graph_lib::Point{5, 5}, win_w - 80, win_h - 10 };

  win.attach(scheme);

  auto column_x = [] (double c) -> int
  {
    return int(40 + 100 * c);
  };

  auto line_y = [] (double l) -> int
  {
    return int(30 + 100 * l);
  };

  SourceShape src_shape1{ scheme, src1, "src1", Graph_lib::Point{ column_x(0), line_y(0) } };
  SourceShape src_shape2{ scheme, src2, "src2", Graph_lib::Point{ column_x(0), line_y(1) } };
  SourceShape src_shape3{ scheme, src3, "src3", Graph_lib::Point{ column_x(0), line_y(2) } };
  SourceShape src_shape4{ scheme, src4, "src4", Graph_lib::Point{ column_x(0), line_y(3) } };

  XorShape xor_shape1{ scheme, xor_lhs, "xor1", Graph_lib::Point{ column_x(2), line_y(0) + 50 } };
  XorShape xor_shape2{ scheme, xor_rhs, "xor2", Graph_lib::Point{ column_x(2), line_y(2) + 50 } };

  XorShape xor_shape3{ scheme, xor_res, "xor3", Graph_lib::Point{ column_x(4), line_y(1) + 50 } };

  scheme.update_connections();

  std::cout << "\nEnter a 4 source signals in one row (for example >> 1 0 1 1)\n>> ";
  
  int data[4];
  for (int i = 0; i < 4; i++)
    std::cin >> data[i];

  src1 = data[0];
  src2 = data[1];
  src3 = data[2];
  src4 = data[3];

  std::cout << "Result is " << bool(xor_res) << std::endl;

  win.wait_for_button();

}
catch (std::exception& e)
{
  std::cerr << e.what() << std::endl;
  return 1;
}
catch (...)
{
  std::cerr <<"Oops, something went wrong..."<< std::endl;
  return 2;
}
