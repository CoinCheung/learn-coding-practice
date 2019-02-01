#include<iostream>
#include<Eigen/Dense>
#include<Eigen/Core>


using std::cout;
using std::endl;


void try_eigen();


int main() {
    try_eigen();
    return 0;
}


void try_eigen() {
    using namespace Eigen;

    MatrixXf mat(5,5);
    cout << mat;
    mat = MatrixXf::Random(30, 30);
    cout << mat(3,3) << endl;
    mat = MatrixXf::Random(3, 3);
    mat.transposeInPlace();
    cout << mat << endl;
    cout << "==" << endl;
    cout << mat.transpose() << endl;
    cout << "==" << endl;
    auto res = mat.transpose() * mat;
    cout << res << endl;

    MatrixXi m(3,3);
    m = MatrixXi::Random(3,3);
    cout << m << endl;
    cout << "==" << endl;
    // m.noalias() = m.cwiseQuotient(m);
    m = m.cwiseQuotient(m);
    cout << m << endl;

    cout << "==" << endl;
    m.setRandom();
    cout << m << endl;
    cout << "==" << endl;
    int buf[9];
    for (int i{0}; i < 9; ++i) {
        buf[i] = i;
    }
    m = Map<MatrixXi>(buf, 3,3);
    cout << m << endl;
    cout << "==" << endl;

    // m.noalias() = m * m.transpose();
    cout << m * m.transpose() << endl;
    // cout << m * m << endl;
    cout << "==" << endl;

    VectorXi m2 = m.colwise().mean();
    // VectorXi m2 = Map<VectorXi>(m.colwise().mean().data(), m.cols());
    cout << m << endl;
    cout << m2 << endl;
    // m.rowwise() -=  m2.transpose();
    m.colwise() -=  m2;
    cout << m << endl;
    // VectorXi m2 = Map<VectorXi>(m.colwise().mean().data(), mean.cols());
    // cout << m2 << endl;
    // cout << "==" << endl;
    // cout << m << endl;
    // cout << "==" << endl;
    // // m.rowwise() -= m2;
    // // m.colwise() -= m2;
    // cout << m << endl;
    // cout << m.rowwise() - m2 << endl;
    // cout << m.data()[3] << endl;
    // // cout << "==" << endl;

}
