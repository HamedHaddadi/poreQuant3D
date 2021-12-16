
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
