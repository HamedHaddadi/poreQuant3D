
# include "../include/maxball3d.h"

bool MaxBall3D::fullyIncludedIn(const MaxBall3D & other) const {
    return (::sqrt(::pow(std::get<0>(coordinate_) - std::get<0>(other.coordinate_), 2.0) +
     ::pow(std::get<1>(coordinate_) - std::get<1>(other.coordinate_), 2.0) +
      ::pow(std::get<2>(coordinate_) - std::get<2>(other.coordinate_), 2.0)) <= other.radius_);
}

bool MaxBall3D::overlapsWith(const MaxBall3D & other) const {

    bool overlap_cond, threshold_cond;
    double radiusDiff = ::sqrt(::pow(std::get<0>(coordinate_) - std::get<0>(other.coordinate_), 2.0) + 
        ::pow(std::get<1>(coordinate_) - std::get<1>(other.coordinate_), 2.0) +
            ::pow(std::get<2>(coordinate_) - std::get<2>(other.coordinate_), 2.0));
    overlap_cond = (radiusDiff <= (radius_ + other.radius_)) && (radiusDiff > std::abs(radius_ - other.radius_));
    threshold_cond = true;
    if ((threshold_ != 0.0) && (radiusDiff > radius_) && (other.radius_ >= threshold_*radius_))   
        threshold_cond = false; 
    return (overlap_cond && threshold_cond);        
}

void MaxBall3D::addToParents(const MaxBall3D & larger) {
    if (larger.rank_ == 0)
        parents_.insert(larger.id_);
    else
        parents_.insert(larger.parents_.begin(), larger.parents_.end());    
}

constexpr bool operator==(const MaxBall3D & ball1, const MaxBall3D & ball2) {
    return (ball1.radius_ == ball2.radius_);
}

constexpr bool operator!=(const MaxBall3D & ball1, const MaxBall3D & ball2) {
    return (ball1.radius_ != ball2.radius_);
}

constexpr bool operator>=(const MaxBall3D & ball1, const MaxBall3D & ball2) {
    return (ball1.radius_ >= ball2.radius_);
}

constexpr bool operator<(const MaxBall3D & ball1, const MaxBall3D & ball2) {
    return (ball1.radius_ < ball2.radius_);
}

std::ofstream& operator<<(std::ofstream & out_stream, const MaxBall3D & ball) {

    out_stream<<std::get<0>(ball.coordinate_)<<","<<std::get<1>(ball.coordinate_)<<","
        <<std::get<2>(ball.coordinate_)<<","<<ball.radius_<<","<<ball.rank_;
    return out_stream;

}