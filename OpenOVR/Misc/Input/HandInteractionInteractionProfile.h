//
// XR_EXT_hand_interaction: hands tracked by the runtime, presented as a pair of controllers with grip, aim, pinch,
// poke, aim-activate and grasp inputs. Runtimes such as Monado offer their hand-tracking devices only under this
// profile, so without it there is no grip pose for a tracked hand.
//

#pragma once

#include "InteractionProfile.h"

class HandInteractionInteractionProfile : public InteractionProfile {
public:
	HandInteractionInteractionProfile();

	const std::string& GetPath() const override;
	std::optional<const char*> GetLeftHandRenderModelName() const override;
	std::optional<const char*> GetRightHandRenderModelName() const override;
	std::optional<const char*> GetOpenVRName() const override;
	std::optional<vr::EVRSkeletalTrackingLevel> GetOpenVRTrackinglevel() const override;

protected:
	const LegacyBindings* GetLegacyBindings(const std::string& handPath) const override;
};
