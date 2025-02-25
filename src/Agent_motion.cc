#include "Agent_motion.h"

namespace bdm {

// Initialize the static instance
PositionTracker* PositionTracker::instance_ = nullptr;

void BrownianMotion::Run(Agent* cell) {
    auto* random = Simulation::GetActive()->GetRandom();
    auto* tracker = PositionTracker::GetInstance();

    Real3 former_position = cell->GetPosition();

    // Remove the agent's old position
    tracker->FreePosition(former_position);

    Real3 new_position;
    int max_attempts = 100;
    int attempt = 0;

    do {
        Real3 displacement = {random->Uniform(-0.5, 0.5),
                              random->Uniform(-0.5, 0.5),
                              random->Uniform(-0.5, 0.5)};
        new_position = former_position + displacement;
        attempt++;

        if (!tracker->IsPositionOccupied(new_position)) {
            break;
        }
    } while (attempt < max_attempts);

    if (attempt >= max_attempts) {
        new_position = former_position;
    }

    cell->SetPosition(new_position);
    tracker->OccupyPosition(new_position);
}

}  // namespace bdm