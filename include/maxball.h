# if !defined(MAXBALL_H)
# define MAXBALL_H
# include "../include/header.h"

class MaxBall {

    private:
        std::tuple<double, double> coordinate_;

    protected:
        int id_;
        int rank_{0};
        double radius_;
        double threshold_{0.0};
        std::set<int> parents_;
        std::set<int> children_;
        std::set<int> siblings_;
        bool included_ = false;

    public:
        MaxBall() = default;
        MaxBall(std::tuple<double, double> coordinate, int id, double radius, double threshold):coordinate_{std::move(coordinate)},
        id_{id},
        radius_{radius}, threshold_{threshold} { siblings_.insert(id);}
        MaxBall(const MaxBall &) = default;
        MaxBall& operator=(const MaxBall &) = default;
        MaxBall(MaxBall && other) noexcept;
        MaxBall& operator=(MaxBall && other) noexcept;
        virtual ~MaxBall() = default;
        // class interface
        int getID() const {return id_;}
        int getRank() const {return rank_;}
        double getRadius() const {return radius_;}
        std::tuple<double, double> getCoordinates() {return coordinate_;}
        std::set<int> getParents() const {return parents_;}
        std::set<int> getChildren() const {return children_;}
        std::set<int> getSiblings() const {return siblings_;}
        bool isIncluded() const {return included_;}
        void makeIncluded() {included_ = true;}
        bool isParent() {return ((rank_ == 0) && (parents_.empty()) && (!children_.empty())); }
        void raiseRank() { rank_ += 1;}
        void setID(int id) {id_ = id;}
        void addToChildren(int smaller_id);
        void addToSiblings(std::set<int> &);
        // all non virtual
        void addToParents(const MaxBall &);
        bool fullyIncludedIn(const MaxBall &) const;
        bool overlapsWith(const MaxBall &) const;
        // comparison operators
        friend constexpr bool operator!=(const MaxBall &, const MaxBall &);
        friend constexpr bool operator==(const MaxBall &, const MaxBall &);
        friend constexpr bool operator>=(const MaxBall &, const MaxBall &);
        friend constexpr bool operator<(const MaxBall &, const MaxBall &);
        // overloaded output operators
        friend std::ofstream& operator<<(std::ofstream& ,const MaxBall&);
};

# endif