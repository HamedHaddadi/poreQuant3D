
# include "pore.h"

Pore::Pore(Pore && other) noexcept {
    std::swap(id_, other.id_);
    std::swap(coordinates_, other.coordinates_);
    std::swap(radius_, other.radius_);
    std::swap(connections_, other.connections_);
    std::swap(pore_family_, other.pore_family_);
}

Pore& Pore::operator=(Pore && other) noexcept {
    std::swap(id_, other.id_);
    std::swap(coordinates_, other.coordinates_);
    std::swap(radius_, other.radius_);
    std::swap(connections_, other.connections_);
    std::swap(pore_family_, other.pore_family_);
    return *this;
}

std::ofstream& operator<<(std::ofstream & out_stream, const Pore & pore) {
    out_stream<<pore.id_<<","<<std::get<0>(pore.coordinates_)<<","
        <<std::get<1>(pore.coordinates_)<<","<<pore.radius_;
    
    return out_stream;

}

