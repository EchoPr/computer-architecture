#include <iostream>
#include <sstream>
#include <exception>
#include <vector>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Window.h>
#include <Graph_lib/Simple_window.h>

#include "logic.h"
#include "logic_shapes.h"


int main ()
try
{
  int win_w = 1000;
  int win_h = 800;
  Graph_lib::Point lt{ Graph_lib::x_max()/2 - win_w/2, Graph_lib::y_max()/2 - win_h/2 };
  Simple_window win{ lt, win_w, win_h, "Scheme of Logic Elements" };
  //win.wait_for_button();

  using namespace Logic;

  Source src11;
  Source src12;
  Source src13;
  Source src14;
  Source src21;
  Source src22;
  Source src23;
  Source src24;

  Xor xor1{ Out_state::inverted };
  Xor xor2{ Out_state::inverted };
  Xor xor3{ Out_state::inverted };
  Xor xor4{ Out_state::inverted };

  And res;


        
  src11 >> xor1;
  src21 >> xor1;
  src12 >> xor2;
  src22 >> xor2;
  src13 >> xor3;
  src23 >> xor3;
  src14 >> xor4;
  src24 >> xor4;

  xor1 >> res;
  xor2 >> res;
  xor3 >> res;
  xor4 >> res;

  //
  SchemeShape scheme{ Graph_lib::Point{5, 5}, win_w - 80, win_h - 10 };

  win.attach(scheme);

  auto column_x = [] (double c) -> int
  {
    return int(40 + 100 * c);
  };

  auto line_y = [] (double l) -> int
  {
    return int(30 + 50 * l);
  };

  SourceShape src_shape11{ scheme, src11, "src11", Graph_lib::Point{ column_x(0), line_y(0) } };
  SourceShape src_shape12{ scheme, src12, "src12", Graph_lib::Point{ column_x(0), line_y(1) } };
  SourceShape src_shape13{ scheme, src13, "src13", Graph_lib::Point{ column_x(0), line_y(2) } };
  SourceShape src_shape14{ scheme, src14, "src14", Graph_lib::Point{ column_x(0), line_y(3) } };
  SourceShape src_shape21{ scheme, src21, "src21", Graph_lib::Point{ column_x(0), line_y(4) } };
  SourceShape src_shape22{ scheme, src22, "src22", Graph_lib::Point{ column_x(0), line_y(5) } };
  SourceShape src_shape23{ scheme, src23, "src23", Graph_lib::Point{ column_x(0), line_y(6) } };
  SourceShape src_shape24{ scheme, src24, "src24", Graph_lib::Point{ column_x(0), line_y(7) } };

  XorShape xor_shape1{ scheme, xor1, "xor1", Graph_lib::Point{ column_x(2), line_y(0) + 10 } };
  XorShape xor_shape2{ scheme, xor2, "xor2", Graph_lib::Point{ column_x(2), line_y(2) + 10 } };
  XorShape xor_shape3{ scheme, xor3, "xor3", Graph_lib::Point{ column_x(2), line_y(4) + 10 } };
  XorShape xor_shape4{ scheme, xor4, "xor4", Graph_lib::Point{ column_x(2), line_y(6) + 10 } };

  AndShape and_shape{ scheme, res, "res", Graph_lib::Point{ column_x(4), line_y(3) } };

  scheme.update_connections();

  std::cout << "\nEnter a two 4 source signals in two rows\n";

  
  int data[8];
  for (int i = 0; i < 8; i++)
    std::cin >> data[i];

  src11 = data[0];
  src12 = data[1];
  src13 = data[2];
  src14 = data[3];
  src21 = data[4];
  src22 = data[5];
  src23 = data[6];
  src24 = data[7];

  std::cout << "Result is " << bool(res) << std::endl;


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
