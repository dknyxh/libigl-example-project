#include <igl/opengl/glfw/Viewer.h>
#include <triangle.h>
#include <boost_include.h>
#include <iostream>

Eigen::MatrixXd B;
Eigen::MatrixXi F;
Eigen::MatrixXd A; 
bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier)
{
  viewer.selected_data_index = 0;
  if (key == 'W')
  {
    B.col(0) = B.col(0).array() + 0.01;
  }
  else if (key == 'S')
  {
    B.col(0) = B.col(0).array() - 0.01;

  }
  else if (key == 'A')
  {
    B.col(1) = B.col(1).array() + 0.01;

  }
  else if (key == 'D')
  {
    B.col(1) = B.col(1).array() - 0.01;

  }
    else if (key == 'Q')
  {
    B.col(2) = B.col(2).array() + 0.01;

  }
    else if (key == 'E')
  {
    B.col(2) = B.col(2).array() - 0.01;

  }
  viewer.data().set_vertices(B);

  using namespace igl::bol;
  auto Ar = A.cast<rat>();
  auto Br = B.cast<rat>();
  std::vector<RowVector3r> seg_list = t2t_intersect(Ar,Br);

  viewer.selected_data_index = 2;
  viewer.data().clear();
  for (int i = 0; i < seg_list.size(); i++){
    // std::cout << i <<std::endl;
    // std::cout << i+1 << std::endl;
    Eigen::MatrixXd p1 = rat_to_double(seg_list[i]); 
    
    // viewer.data().add_edges(p1,p2,Eigen::RowVector3d(1,0,0));
    
    viewer.data().add_points(p1,Eigen::RowVector3d(1,0,0));
   

  }

  return false;
}



int main(int argc, char *argv[])
{
  // Inline mesh of a cube
  A= (Eigen::MatrixXd(3,3)<<
    0.0,0.0,0.0,
    0.0,1.0,0.0,
    1.0,0.0,0.0).finished();
  F = (Eigen::MatrixXi(1,3)<<
    0,1,2).finished().array();

  B = (Eigen::MatrixXd(3,3)<<
    0.0,0.0,0.0,
    0.0,1,0.0,
    1.0,0,0).finished();

  // Plot the mesh
  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(B, F);
  
  viewer.append_mesh();
  viewer.data().set_mesh(A, F);

  viewer.append_mesh();
  
  viewer.callback_key_down = &key_down;
  viewer.launch();
}
