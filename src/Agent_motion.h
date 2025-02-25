#ifndef BDM_AGENTMOTION_H_
#define BDM_AGENTMOTION_H_

#include "biodynamo.h"
#include "core/behavior/behavior.h"
#include "Agents.h"
#include "core/agent/cell.h"
#include "core/util/math.h"
#include <unordered_set>





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

struct BrownianMotion : public Behavior {
    BDM_BEHAVIOR_HEADER(BrownianMotion, Behavior, 1);

    using PositionSet = std::unordered_set<Real3, MathArrayHash>;

    // Use `extern` to declare static variables here
    static PositionSet* occupied_positions;
    static std::mutex position_mutex;

    BrownianMotion() {}
    virtual ~BrownianMotion() {}

    void Run(Agent* cell) override;

    // Cleanup function to free memory
    static void Cleanup();
};

}  // namespace bdm


#endif  // BDM_AGENTMOTION_H_
