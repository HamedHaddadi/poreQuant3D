
# include "maxball.h"

MaxBall::MaxBall(MaxBall && other) noexcept {
    std::swap(id_, other.id_);
    std::swap(rank_,other.rank_);
    std::swap(radius_, other.radius_);
    std::swap(coordinate_, other.coordinate_);
    std::swap(included_, other.included_);
    std::swap(parents_, other.parents_);
    std::swap(children_, other.children_);
    std::swap(siblings_, other.siblings_);
}

MaxBall& MaxBall::operator=(MaxBall&& other) noexcept {
    std::swap(id_, other.id_);
    std::swap(rank_,other.rank_);
    std::swap(radius_, other.radius_);
    std::swap(coordinate_, other.coordinate_);
    std::swap(included_, other.included_);
    std::swap(parents_, other.parents_);
    std::swap(children_, other.children_);
    std::swap(siblings_, other.siblings_);
    return *this;  
}

bool MaxBall::fullyIncludedIn(const MaxBall & other) const {
    return (::sqrt(::pow(std::get<0>(coordinate_) - std::get<0>(other.coordinate_), 2.0) +
         ::pow(std::get<1>(coordinate_) - std::get<1>(other.coordinate_), 2.0)) <= other.radius_ - radius_);
}

bool MaxBall::overlapsWith(const MaxBall & other) const {
    double radiusDiff = ::sqrt(::pow(std::get<0>(coordinate_) - std::get<0>(other.coordinate_), 2.0) +
     ::pow(std::get<1>(coordinate_) - std::get<1>(other.coordinate_), 2.0));
    return ((radiusDiff <= (radius_ + other.radius_)) && (radiusDiff > std::abs(radius_ - other.radius_)));
}

void MaxBall::addToParents(const MaxBall & larger) {

    if (larger.rank_ == 0)
        parents_.insert(larger.rank_);
    else
        parents_.insert(larger.parents_.begin(), larger.parents_.end());
}

void MaxBall::addToChildren(int smaller_id) {
    children_.insert(smaller_id);
}

void MaxBall::addToSiblings(std::set<int> & siblings) {
    siblings_.insert(siblings.begin(), siblings.end());
}

constexpr bool operator==(const MaxBall & ball1, const MaxBall & ball2) {
    return (ball1.radius_ == ball2.radius_);
}

constexpr bool operator!=(const MaxBall & ball1, const MaxBall & ball2) {
    return (ball1.radius_ != ball2.radius_);
}

constexpr bool operator>=(const MaxBall & ball1, const MaxBall & ball2) {
    return (ball1.radius_ >= ball2.radius_);
}

constexpr bool operator<(const MaxBall & ball1, const MaxBall & ball2) {
    return (ball1.radius_ < ball2.radius_);
}

std::ofstream& operator<<(std::ofstream & out_stream, const MaxBall & ball){

    out_stream<<std::get<0>(ball.coordinate_)<<","
            <<std::get<1>(ball.coordinate_)<<","
                <<ball.radius_<<","<<ball.rank_;

    return out_stream;
}
