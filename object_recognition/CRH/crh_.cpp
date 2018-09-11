#include <pcl/io/pcd_io.h>
#include <pcl/common/centroid.h>
#include <pcl/features/crh.h>
#include <pcl/recognition/crh_alignment.h>

#include <iostream>
#include <vector>

// A handy typedef.
typedef pcl::Histogram<90> CRH90;

int
main(int argc, char** argv)
{
  // Clouds for storing the object's cluster and view.
  pcl::PointCloud<pcl::PointXYZ>::Ptr viewCloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr clusterCloud(new pcl::PointCloud<pcl::PointXYZ>);
  // Objects for storing the CRHs of both.
  pcl::PointCloud<CRH90>::Ptr viewCRH(new pcl::PointCloud<CRH90>);
  pcl::PointCloud<CRH90>::Ptr clusterCRH(new pcl::PointCloud<CRH90>);
  // Objects for storing the centroids.
  Eigen::Vector4f viewCentroid;
  Eigen::Vector4f clusterCentroid;

  // Read the trained view and the scene cluster from disk.
  if (pcl::io::loadPCDFile<pcl::PointXYZ>(argv[1], *viewCloud) != 0)
  {
    return -1;
  }
  if (pcl::io::loadPCDFile<pcl::PointXYZ>(argv[2], *clusterCloud) != 0)
  {
    return -1;
  }

  std::cout << "aaaaaaaaaaaaaa " << std::endl;
  

  // Note: here you would compute the CRHs and centroids of both clusters.
  // It has been omitted here for simplicity.

  // CRH alignment object.
  pcl::CRHAlignment<pcl::PointXYZ, 90> alignment;
  alignment.setInputAndTargetView(clusterCloud, viewCloud);
  // CRHAlignment works with Vector3f, not Vector4f.
  Eigen::Vector3f viewCentroid3f(viewCentroid[0], viewCentroid[1], viewCentroid[2]);
  Eigen::Vector3f clusterCentroid3f(clusterCentroid[0], clusterCentroid[1], clusterCentroid[2]);
  alignment.setInputAndTargetCentroids(clusterCentroid3f, viewCentroid3f);

  std::cout << "bbbbbbbbbbbbbbbbbbbbbbbb" << std::endl;

  // Compute the roll angle(s).
  // std::vector<float> angles;
  // alignment.computeRollAngle(*clusterCRH, *viewCRH, angles);
  
  // std::cout << "ccccccccccccccccccccccccccccccccccccccc" << std::endl;


  // if (angles.size() > 0)
  // {
  //   std::cout << "List of angles where the histograms correlate:" << std::endl;

  //   for (int i = 0; i < angles.size(); i++)
  //   {
  //     std::cout << "\t" << angles.at(i) << " degrees." << std::endl;
  //   }
  // }
}
