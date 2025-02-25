#include "Agent_motion.h"

namespace bdm {

// Define the static variables once in the source file
BrownianMotion::PositionSet* BrownianMotion::occupied_positions = nullptr;
std::mutex BrownianMotion::position_mutex;

void BrownianMotion::Run(Agent* cell) {
    auto* random = Simulation::GetActive()->GetRandom();

    // Thread-safe initialization of the static member
    if (!occupied_positions) {
        std::lock_guard<std::mutex> lock(position_mutex);
        if (!occupied_positions) {
            occupied_positions = new PositionSet();
        }
    }

    Real3 former_position = cell->GetPosition();

    // Remove the agent's old position
    {
        std::lock_guard<std::mutex> lock(position_mutex);
        occupied_positions->erase(former_position);
    }

    Real3 new_position;
    int max_attempts = 100;
    int attempt = 0;

    do {
        Real3 displacement = {random->Uniform(-0.5, 0.5),
                              random->Uniform(-0.5, 0.5),
                              random->Uniform(-0.5, 0.5)};
        new_position = former_position + displacement;
        attempt++;

        std::lock_guard<std::mutex> lock(position_mutex);
        if (occupied_positions->count(new_position) == 0) {
            break;
        }
    } while (attempt < max_attempts);

    if (attempt >= max_attempts) {
        new_position = former_position;
    }

    cell->SetPosition(new_position);

    {
        std::lock_guard<std::mutex> lock(position_mutex);
        occupied_positions->insert(new_position);
    }
}

void BrownianMotion::Cleanup() {
    std::lock_guard<std::mutex> lock(position_mutex);
    delete occupied_positions;
    occupied_positions = nullptr;
    std::cout << "Cleanup completed.\n";
}

}  // namespace bdm

