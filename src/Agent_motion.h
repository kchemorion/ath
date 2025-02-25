#ifndef BDM_AGENTMOTION_H_
#define BDM_AGENTMOTION_H_

#include "biodynamo.h"
#include "core/behavior/behavior.h"
#include "Agents.h"
#include "core/agent/cell.h"
#include "core/util/math.h"
#include <unordered_set>
#include <memory>

namespace bdm {

struct MathArrayHash {
    size_t operator()(const bdm::Real3& arr) const {
        std::size_t seed = 0;
        for (double val : arr) {
            seed ^= std::hash<double>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

struct Real3Eq {
    bool operator()(const bdm::Real3& a, const bdm::Real3& b) const {
        return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
    }
};

// Position tracker class to manage occupied positions - singleton pattern
class PositionTracker {
public:
    using PositionSet = std::unordered_set<Real3, MathArrayHash, Real3Eq>;
    
    static PositionTracker* GetInstance() {
        static std::mutex init_mutex;
        if (!instance_) {
            std::lock_guard<std::mutex> lock(init_mutex);
            if (!instance_) {
                instance_ = new PositionTracker();
            }
        }
        return instance_;
    }
    
    // Cleanup function to be called at program exit
    static void Cleanup() {
        if (instance_) {
            delete instance_;
            instance_ = nullptr;
            std::cout << "Position tracker cleanup completed.\n";
        }
    }
    
    bool IsPositionOccupied(const Real3& position) {
        std::lock_guard<std::mutex> lock(position_mutex_);
        return occupied_positions_.count(position) > 0;
    }
    
    void OccupyPosition(const Real3& position) {
        std::lock_guard<std::mutex> lock(position_mutex_);
        occupied_positions_.insert(position);
    }
    
    void FreePosition(const Real3& position) {
        std::lock_guard<std::mutex> lock(position_mutex_);
        occupied_positions_.erase(position);
    }
    
private:
    PositionTracker() = default;
    ~PositionTracker() = default;
    
    // Non-copyable, non-movable
    PositionTracker(const PositionTracker&) = delete;
    PositionTracker& operator=(const PositionTracker&) = delete;
    PositionTracker(PositionTracker&&) = delete;
    PositionTracker& operator=(PositionTracker&&) = delete;
    
    static PositionTracker* instance_;
    PositionSet occupied_positions_;
    std::mutex position_mutex_;
};

struct BrownianMotion : public Behavior {
    BDM_BEHAVIOR_HEADER(BrownianMotion, Behavior, 1);

    BrownianMotion() = default;
    virtual ~BrownianMotion() = default;

    void Run(Agent* cell) override;
};

}  // namespace bdm

#endif  // BDM_AGENTMOTION_H_