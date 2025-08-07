#ifndef KINEMATICS_VECTORS_H
#define KINEMATICS_VECTORS_H

#include <vector>

class KVector{
public:
    KVector(size_t columns, size_t rows = 1) : m_vectors(columns, std::vector<float>(rows)) {}

    KVector(KVector& copy) : m_vectors{}{ *this = copy;};

    KVector(std::vector<std::vector<float>> input) : m_vectors {}{
        m_vectors = input;
    }

    void operator=(const std::vector<std::vector<float>> input);
    void operator=(const KVector& v);
    void operator+=(const KVector& v);
    void operator-=(const KVector& v);
    void operator*=(const KVector& v);
    void operator/=(const KVector& v);
    KVector operator+(const KVector& v);
    KVector operator-(const KVector& v);
    KVector operator*(const KVector& v);
    KVector operator/(const KVector& v);

    KVector operator+(const std::vector<float>& v);
    KVector operator-(const std::vector<float>& v);
    KVector operator*(const std::vector<float>& v);
    KVector operator/(const std::vector<float>& v);

    KVector operator+(double add);
    KVector operator-(double sub);
    KVector operator*(double scale);
    KVector operator/(double dev);

    KVector setConstant(double value);
    KVector setConstant(std::vector<double>& vector);

    const double magnitude(int index);
    const double maxMagnitude();
    const double avgMagnitude();

    const std::vector<float> getRow(int i) const {return m_vectors[i];};
    constexpr int getRows() const { return m_vectors.size();};
    constexpr int getColumns() const { return m_vectors[0].size();};

    std::vector<std::vector<float>> getVector() {return m_vectors;};

private:
    template <typename Op>
    void applyKVectorOperation(const std::vector<std::vector<float>>& v, Op op);

    template <typename Op>
    void applyVectorOperation(const std::vector<float>& v, Op op);

    template <typename T, typename Op>
    void applyScalarOperation(const T num, Op op);

    std::vector<std::vector<float>> m_vectors;
};

#endif // KINEMATICS_VECTORS_H
