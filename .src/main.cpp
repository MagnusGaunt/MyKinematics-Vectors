#include "kinematicsVectors.h"
#include <vector>
#include <cmath>

namespace {
    auto add_op = [](double& a, double b) { a += b; };
    auto sub_op = [](double& a, double b) { a -= b; };
    auto mult_op = [](double& a, double b) { a *= b; };
    auto dev_op = [](double& a, double b) {a /= b; };
    auto set_op = [](double& a, double b) { a = b; };
}

template <typename Op>
void KVector::applyKVectorOperation(const std::vector<std::vector<float>>& v, Op op){
    for (int i = 0; i < m_vectors.size() && i < v.size(); ++i){
        for (int j = 0; j < m_vectors[0].size() && j < v[0].size(); ++j){
            op(m_vectors[i][j], v[i][j]);
        }
    }
}

template <typename Op>
void KVector::applyVectorOperation(const std::vector<float>& v, Op op){
    for (int i = 0; i < m_vectors.size(); ++i){
        for (int j = 0; j < m_vectors[0].size() && j < v.size(); ++j){
            op(m_vectors[i][j], v[j]);
        }
    }
}

template <typename T, typename Op>
void KVector::applyScalarOperation(const T num, Op op){
    for (int i = 0; i < m_vectors.size(); ++i){
        for (int j = 0; j < m_vectors[0].size() ++j){
            op(m_vectors[i][j], num);
        }
    }
}

//////////////////////////////////////////////////////////

void KVector::operator=(const std::vector<std::vector<float>> input){
    m_vectors.resize(input.size());
    m_vectors[0].resize(input[0].size());
    applyKVectorOperation(input, add_op);
}

//////////////////////////////////////////////////////////

void KVector::operator=(const KVector& v) {
    m_vectors.resize(v.m_vectors.size());
    m_vectors[0].resize(v.m_vectors[0].size());
    applyKVectorOperation(v.m_vectors, add_op);
}

void KVector::operator+=(const KVector& v) {
    applyKVectorOperation(v.m_vectors, add_op);
}

void KVector::operator-=(const KVector& v) {
    applyKVectorOperation(v.m_vectors, sub_op);
}

void KVector::operator*=(const KVector& v) {
    applyKVectorOperation(v.m_vectors, mult_op);
}

void KVector::operator/=(const KVector& v) {
    applyKVectorOperation(v.m_vectors, dev_op);
}

//////////////////////////////////////////////////////////

KVector KVector::operator+(const KVector& v) {
    KVector temp {*this};
    temp.applyKVectorOperation(v.m_vectors, add_op);
    return temp;
}

KVector KVector::operator-(const KVector& v) {
    KVector temp {*this};
    temp.applyKVectorOperation(v.m_vectors, sub_op);
    return temp;
}

KVector KVector::operator*(const KVector& v) {
    KVector temp {*this};
    temp.applyKVectorOperation(v.m_vectors, mult_op);
    return temp;
}

KVector KVector::operator/(const KVector& v) {
    KVector temp {*this};
    temp.applyKVectorOperation(v.m_vectors, dev_op);
    return temp;
}

//////////////////////////////////////////////////////////

KVector KVector::operator+(const std::vector<float>& v){
    KVector temp {*this};
    temp.applyVectorOperation(v, add_op);
    return temp;
}

KVector KVector::operator-(const std::vector<float>& v){
    KVector temp {*this};
    temp.applyVectorOperation(v, sub_op);
    return temp;
}

KVector KVector::operator*(const std::vector<float>& v){
    KVector temp {*this};
    temp.applyVectorOperation(v, mult_op);
    return temp;
}

KVector KVector::operator/(const std::vector<float>& v){
    KVector temp {*this};
    temp.applyVectorOperation(v, dev_op);
    return temp;
}

//////////////////////////////////////////////////////////

KVector KVector::operator+(double add){
    KVector temp {*this};
    temp.applyScalarOperation(add, mult_op);
    return temp;
}

KVector KVector::operator-(double sub){
    KVector temp {*this};
    temp.applyScalarOperation(sub, mult_op);
    return temp;
}

KVector KVector::operator*(double scale){
    KVector temp {*this};
    temp.applyScalarOperation(scale, mult_op);
    return temp;
}

KVector KVector::operator/(double dev){
    KVector temp {*this};
    temp.applyScalarOperation(dev, mult_op);
    return temp;
}

//////////////////////////////////////////////////////////

KVector KVector::setConstant(double value){
    applyScalarOperation(0, set_op);
    applyScalarOperation(value, add_op);
    return *this;
}

KVector KVector::setConstant(std::vector<double>& vector){
    applyScalarOperation(0, set_op);
    applyScalarOperation(vector, add_op);
    return *this;
}
const double KVector::magnitude(int index){
    if (index < 0 || index >= m_vectors.size()) {
        return -1;
    }
    double sum = 0;
    for (int i = 0; i < m_vectors.size(); ++i) {
        sum += m_vectors[index][i] * m_vectors[index][i];
    }
    return std::sqrt(sum);

}

const double KVector::maxMagnitude(){
    double max {};
    for (int i = 0; i < m_vectors.size(); ++i){
       max = std::max(max, magnitude(i));
    }
    return max;
}

const double KVector::avgMagnitude(){
    double max {};
    for (int i = 0; i < m_vectors.size(); ++i){
       max = std::max(max, magnitude(i));
    }
    return max/m_vectors.size();

}
