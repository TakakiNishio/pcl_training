#include <pcl/io/pcd_io.h>
#include <pcl/features/normal_3d.h>
#include <pcl/common/centroid.h>
#include <pcl/features/crh.h>

// A handy typedef.
typedef pcl::Histogram<90> CRH90;

int
main(int argc, char** argv)
{
	// Cloud for storing the object.
	pcl::PointCloud<pcl::PointXYZ>::Ptr object(new pcl::PointCloud<pcl::PointXYZ>);
	// Object for storing the normals.
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	// Object for storing the CRH.
	pcl::PointCloud<CRH90>::Ptr histogram(new pcl::PointCloud<CRH90>);

	// Note: this cloud file should contain a snapshot of the object. Remember
	// that you need to compute a CRH for every VFH or CVFH descriptor that you
	// are going to have (that is, one for every snapshot).

	// Read a PCD file from disk.
	if (pcl::io::loadPCDFile<pcl::PointXYZ>(argv[1], *object) != 0)
	{
		return -1;
	}

	// Estimate the normals.
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> normalEstimation;
	normalEstimation.setInputCloud(object);
	normalEstimation.setRadiusSearch(0.03);
	pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree(new pcl::search::KdTree<pcl::PointXYZ>);
	normalEstimation.setSearchMethod(kdtree);
	normalEstimation.compute(*normals);

	// CRH estimation object.
	pcl::CRHEstimation<pcl::PointXYZ, pcl::Normal, CRH90> crh;
	crh.setInputCloud(object);
	crh.setInputNormals(normals);
	Eigen::Vector4f centroid;
	pcl::compute3DCentroid(*object, centroid);
	crh.setCentroid(centroid);

	// Compute the CRH.
	crh.compute(*histogram);
}
