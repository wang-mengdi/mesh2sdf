#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/OBJ_reader.h>
#include <CGAL/compute_signed_distance_3.h>
#include <CGAL/transform.h>
#include <CGAL/Polyhedron_traits_3.h>
#include <CGAL/Point_3.h>
#include <iostream>
#include <vector>
#include <fstream>

// 定义CGAL的内核类型
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K> Polyhedron;
typedef K::Point_3 Point_3;
typedef K::Vector_3 Vector_3;

void load_mesh(const std::string& mesh_file, Polyhedron& P) {
    std::ifstream input(mesh_file);
    if (!input || !(input >> P)) {
        std::cerr << "Error: cannot read mesh from " << mesh_file << std::endl;
        exit(1);
    }
    std::cout << "Mesh loaded successfully!" << std::endl;
}

void rescale_and_translate_mesh(Polyhedron& P, const Vector_3& scale, const Point_3& target_center) {
    // 创建缩放和移动矩阵
    CGAL::Aff_transformation_3<K> transform = CGAL::Aff_transformation_3<K>::scale(scale);
    // 应用变换
    for (auto v = P.vertices_begin(); v != P.vertices_end(); ++v) {
        v->point() = transform(v->point());
    }
    std::cout << "Mesh scaled and translated." << std::endl;
}

void compute_signed_distance(const Polyhedron& P, const std::vector<Point_3>& query_points, std::vector<double>& distances) {
    for (const auto& point : query_points) {
        double distance = CGAL::compute_signed_distance_3(P, point);
        distances.push_back(distance);
    }
    std::cout << "Signed distances computed." << std::endl;
}

int main() {
    std::string mesh_file = "path/to/your/mesh.obj";  // 替换为你实际的文件路径
    Polyhedron P;
    
    // 加载网格
    load_mesh(mesh_file, P);
    
    // 缩放和移动网格
    Vector_3 scale(1.0, 1.0, 1.0);  // 可以根据需要调整缩放比例
    Point_3 target_center(0.0, 0.0, 0.0);  // 设置目标中心
    rescale_and_translate_mesh(P, scale, target_center);
    
    // 计算有符号距离
    std::vector<Point_3> query_points = { Point_3(0.0, 0.0, 0.0), Point_3(1.0, 1.0, 1.0) };  // 示例查询点
    std::vector<double> distances;
    compute_signed_distance(P, query_points, distances);
    
    // 打印计算结果
    for (size_t i = 0; i < distances.size(); ++i) {
        std::cout << "Distance to point " << i << ": " << distances[i] << std::endl;
    }

    return 0;
}
